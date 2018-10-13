#include <QWheelEvent>
#include <QDebug>

#include "slicewidget.h"
#include "globals.h"
#include "model/sliceitem.h"
#include "model/markitem.h"

SliceWidget::SliceWidget(QWidget *parent) :QGraphicsView(parent),
m_scaleFactor(0.5),
m_currentPaintingSlice(nullptr),
m_paint(false),
m_selection(false),
m_pen(QPen(Qt::black, 5, Qt::SolidLine)),
m_slice(nullptr),
m_paintingItem(nullptr),
m_state(0),
m_anchorItem(nullptr),
m_paintNavigationView(false)
{
	setScene(new QGraphicsScene(this));
	scale(m_scaleFactor, m_scaleFactor);
	connect(scene(), &QGraphicsScene::selectionChanged, this, &SliceWidget::selectionChanged);
	setTransformationAnchor(QGraphicsView::NoAnchor);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setDragMode(QGraphicsView::RubberBandDrag);
	setOperation(Operation::Move);
	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	m_anchorItem = new QGraphicsPixmapItem(createAnchorItemPixmap());
	m_anchorItem->setVisible(false);
	setStyleSheet(QStringLiteral("border:0px solid white"));
}

void SliceWidget::setMarks(const QList<QGraphicsItem*>& items)
{
	set_mark_helper_(items);
}
void SliceWidget::wheelEvent(QWheelEvent *event) {
	//const auto numDegrees = -event->delta() / 8.0;
	//const auto numSteps = numDegrees / 15.0;
	//const auto factor = std::pow(1.125, numSteps);
	//scale(factor, factor);
	//event->accept();
	//QGraphicsView::wheelEvent(event);
	qDebug() << "wheelEvent in SliceWidget";
	//event->accept();
}
void SliceWidget::focusInEvent(QFocusEvent* event)
{
	Q_UNUSED(event);
	setStyleSheet(QStringLiteral("border:1px solid red"));
	emit sliceSelected();
}

void SliceWidget::focusOutEvent(QFocusEvent* event)
{
	Q_UNUSED(event);
	setStyleSheet(QStringLiteral("border:0px solid white"));
}

void SliceWidget::paintEvent(QPaintEvent* event)
{
	QGraphicsView::paintEvent(event);

	if (m_paintNavigationView == false)
		return;

	const auto & sliceRectInScene = m_slice->mapRectToScene(m_slice->boundingRect());
	const auto & viewRectInScene = mapToScene(rect()).boundingRect();
	if (viewRectInScene.contains(sliceRectInScene))
		return;
	//const auto & scRect = sceneRect();
	const auto & scRect = m_slice->mapRectToScene(m_slice->boundingRect());
	QImage thumbnail(QSize(200, 200), QImage::Format_RGB32);
	QPainter p0(&thumbnail);
	render(&p0, thumbnail.rect(), mapFromScene(scRect).boundingRect());		//rendering the scene image
	p0.end();
	const auto & navigationRect = thumbnail.rect();
	const double f1 = navigationRect.width() / scRect.width(), f2 = navigationRect.height() / scRect.height();
	QPainter p(&thumbnail);
	p.setPen(QPen(Qt::red, 2));
	p.drawRect(QRect(
		f1 * (viewRectInScene.x() - scRect.x()),			//transform from view rectangle to thumbnail rectangle
		f2 * (viewRectInScene.y() - scRect.y()),
		f1 * viewRectInScene.width(),
		f2 * viewRectInScene.height()));			//draw the zoom rectangle onto the thumbnail

	p.drawRect(thumbnail.rect());
	p.end();
	QPainter p2(this->viewport());//draw the zoom image
	const auto s = size();
	p2.drawPixmap(thumbnailRect(sliceRectInScene, viewRectInScene), QPixmap::fromImage(thumbnail));
	p2.end();
}

void SliceWidget::mousePressEvent(QMouseEvent *event)
{
	//if (event->isAccepted())
	//	return;

	const auto button = event->button();
	const auto viewPos = event->pos();
	const auto scenePos = mapToScene(viewPos);

	m_prevViewPoint = viewPos;

	auto items = scene()->items(scenePos);

	if (button == Qt::RightButton) {
		event->accept();
		return;
	}

	for (const auto & item : items) {
		auto * itm = qgraphicsitem_cast<SliceItem*>(item);
		if (itm == m_slice) {	 // Operations must perform on slice item.

			if(button == Qt::RightButton) {			// ignore right button event
				event->accept();
				return;
			}

			const auto itemPoint = m_slice->mapFromScene(scenePos);

			emit sliceSelected(itemPoint.toPoint());

			if (m_state == Operation::Paint) {

				m_currentPaintingSlice = m_slice;

				m_paintingItem = new StrokeMarkItem(m_currentPaintingSlice);

				m_paintingItem->setFlags(QGraphicsItem::ItemIsSelectable);
				m_paintingItem->setPen(m_pen);
				m_paintingItem->appendPoint(itemPoint);

				event->accept();
				return;
			}
			else if (m_state == Operation::Selection) { 

				// Selecting items automatically by calling default event handler of the QGraphicsView
				return QGraphicsView::mousePressEvent(event);
			}
			else if (m_state == Operation::Move) {

				// Do nothing
				event->accept();
				return;
			}
			else if (m_state == Operation::None) {

				// Set Anchor
				m_anchorItem->setPos(itemPoint);
				m_anchorItem->setVisible(true);
				event->accept();
				return;
			}

		}
	}

	//QGraphicsView::mousePressEvent(event);
	event->accept();
	return;
}

void SliceWidget::mouseMoveEvent(QMouseEvent *event)
{
	// Note that the returned value for event->button() is always Qt::NoButton for mouse move events.

	if (m_state == None)
		return;

	if(event->button() == Qt::RightButton) {
		event->accept();
		return;
	}

	if (m_state == Operation::Paint)		// on drawing a mark
	{
		if (m_currentPaintingSlice != nullptr)
		{
			const auto viewPos = event->pos();
			m_paintingItem->appendPoint(m_currentPaintingSlice->mapFromScene(mapToScene(viewPos)));
			m_paintViewPointsBuffer << viewPos;
			event->accept();
			return;
		}
	}
	else if (m_state == Operation::Move)	//move the slice
	{
		qDebug() << "Slice Moved";
		const auto currentScenePoint = event->pos();
		const auto delta = currentScenePoint - m_prevViewPoint;
		m_prevViewPoint = currentScenePoint;
		//resetTransform();
		//translate(1,1);
		translate(delta.x(), delta.y());
		//translate(delta);

		emit viewMoved(delta);
		//qDebug() << delta << " " << sceneRect() << " " << rect();
		//auto items = scene()->items();
		//for (const auto & item : items)
		//{
		//	SliceItem * sliceItem = qgraphicsitem_cast<SliceItem*>(item);
		//	if (sliceItem == m_slice)
		//	{
		//		//Moving range need to be restrict in sceneRect so as to prevent the change of the scene bounding rect.
		//		auto rect = sliceItem->mapRectToScene(sliceItem->boundingRect());
		//		rect.translate(delta.x(), delta.y());	
		//		if (sceneRect().contains(rect) == false)
		//			return;
		//		sliceItem->setPos(sliceItem->pos() + delta);
		//		emit sliceMoved(delta);
		//		return;
		//	}
		//}
		//return QGraphicsView::mouseMoveEvent(event);
	}
	else if (m_state == Operation::Selection)
	{
		return QGraphicsView::mouseMoveEvent(event);
	}

	QGraphicsView::mouseMoveEvent(event);
}

void SliceWidget::mouseReleaseEvent(QMouseEvent *event)
{

	if (m_state == None)
		return;

	if(event->button() == Qt::RightButton) {
		event->accept();
		return;
	}

	Qt::MouseButton button = event->button();
	if (m_state == Operation::Paint)			//create a mark
	{
		//Q_ASSERT_X(m_currentPaintingSlice,"SliceView::mouseReleaseEvent", "null pointer");
		if(m_currentPaintingSlice == nullptr) {
			event->accept();
			return;
		}
		m_paintingItem->appendPoint(m_currentPaintingSlice->mapFromScene(mapToScene(event->pos())));
		if (m_currentPaintingSlice == m_slice)
			emit markAdded(m_paintingItem);
		m_currentPaintingSlice = nullptr;

		event->accept();
		return;
	}

	QGraphicsView::mouseReleaseEvent(event);
}


void SliceWidget::setImageHelper(const QPoint& pos, const QImage& inImage, SliceItem*& sliceItem, QImage * outImage)
{
	if (sliceItem == nullptr)
	{
		sliceItem = new SliceItem(QPixmap::fromImage(inImage));
		(sliceItem)->setFlag(QGraphicsItem::ItemClipsChildrenToShape);
		sliceItem->setPos(pos);
		m_anchorItem->setParentItem(sliceItem);
		scene()->addItem(sliceItem);
		/**
		 *We need to give a exactly scene rect according to the image size for efficiency rendering.
		 *We assumpt that the size of rect of the scene is two times larger than the size of image.
		 */
		QRect rect = inImage.rect();
		//auto rectInView = mapFromScene(rect).boundingRect();
		translate(rect.width() / 2, rect.height() / 2);
		rect.adjust(-rect.width(), -rect.height(), 0, 0);
		scene()->setSceneRect(rect);
	}
	else
	{
		sliceItem->setPixmap(QPixmap::fromImage(inImage));
	}
	QSize size = inImage.size();
	*outImage = inImage;
}

QRect SliceWidget::thumbnailRect(const QRectF & sliceRect, const QRectF & viewRect)
{
	const int w = 0.2*width(), h = 0.2*height();
	const int W = width(), H = height();
	//if(sliceRect.contains(viewRect))
	//{
	//	return QRect(0,0,w,h);
	//}else if(sliceRect.contains(viewRect.topLeft()))
	//{
	//	return QRect(W-w,H-h,w,h);
	//}else if(sliceRect.contains(viewRect.bottomLeft()))
	//{
	//	return QRect(W-w,0,w,h);
	//}else if(sliceRect.contains(viewRect.topRight()))
	//{
	//	
	//}else if(sliceRect.contains(viewRect.bottomRight()))
	//{
	//	return QRect(0, 0, w, h);
	//}
	//return QRect(0,0,w,h);
	return QRect(0, H - h, w, h);
}

QGraphicsItem * SliceWidget::createMarkItem()
{
	return nullptr;
}

QPixmap SliceWidget::createAnchorItemPixmap(const QString & fileName)
{
	int length = 12;
	QRect target(0, 0, length, length);

	QPixmap pixmap(target.size());
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);

	if (fileName.isEmpty() == false)
	{
		QPixmap image(fileName);
		painter.drawPixmap(target, image, image.rect());
	}
	else
	{
		painter.setPen(QPen(Qt::yellow, 2, Qt::SolidLine));
		painter.drawLine(0, length / 2, length, length / 2);
		painter.drawLine(length / 2, 0, length / 2, length);
	}
	return pixmap;
}

inline
void SliceWidget::set_mark_helper_(
	const QList<QGraphicsItem*>& items)
{
	foreach(QGraphicsItem * item, items)
	{
		item->setVisible(item->data(MarkProperty::VisibleState).toBool());
		item->setParentItem(m_slice);
	}

}



inline
void SliceWidget::clear_slice_marks_helper_(SliceItem * slice)
{
	if (slice == nullptr)
	{
		qWarning("Top slice is empty.");
		return;
	}
	auto children = slice->childItems();
	foreach(QGraphicsItem * item, children)
	{
		item->setVisible(false);
	}
}
void SliceWidget::setImage(const QImage& image)
{
	//set_image_helper(image);
	QSize size = image.size();
	QPoint pos = QPoint(-size.width() / 2, -size.height() / 2);
	setImageHelper(pos, image, m_slice, &m_image);
}

void SliceWidget::clearSliceMarks()
{
	clear_slice_marks_helper_(m_slice);
}

QList<QGraphicsItem*> SliceWidget::selectedItems() const
{
	return scene()->selectedItems();
}

int SliceWidget::selectedItemCount() const
{
	return scene()->selectedItems().size();
}

void SliceWidget::moveSlice(const QPointF& dir)
{
	m_slice->moveBy(dir.x(), dir.y());
}

QSize SliceWidget::sizeHint() const
{
	return m_image.size();
}
