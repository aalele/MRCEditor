#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "mrcdatamodel.h"
QT_BEGIN_NAMESPACE
class QTableView;
class QStandardItemModel;
class QAbstractTableModel;
class QAction;
class QSettings;
QT_END_NAMESPACE
class ImageCanvas;
class MarkModel;
class ProfileView;
class MRC;
class MarkTreeView;
class MarkInfoWidget;
class RenderParameterWidget;
class TF1DEditor;
class VolumeWidget;
class ImageViewControlPanel;
class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
protected:
	void closeEvent(QCloseEvent* event)Q_DECL_OVERRIDE;
private:
	void createWidget();
	void createMenu();
	void createActions();
	void createStatusBar();
	void createMarkTreeView();
	void open();
	bool saveMark();
	void openMark();
	void saveAs();
	void writeSettingsForDockWidget(QDockWidget *dock, QSettings* settings);
	void readSettingsForDockWidget(QDockWidget * dock, QSettings* settings);
	void writeSettingsForImageView(ImageCanvas * view, QSettings * settings);
	void readSettingsForImageView(ImageCanvas * view, QSettings * settings);
	void readSettings();
	void writeSettings();
	void setDefaultLayout();

	AbstractSliceDataModel * replaceSliceModel(AbstractSliceDataModel* model);
	MarkModel * replaceMarkModel(MarkModel * model);
	QAbstractTableModel * replaceProfileModel(QAbstractTableModel * model);
	QAbstractTableModel * setupProfileModel(const MRC & mrc);

	//Widgets
	QDockWidget * m_volumeViewDockWidget;
	VolumeWidget * m_volumeView;

	QDockWidget * m_renderParameterDockWidget;
	RenderParameterWidget * m_renderParameterWidget;

	QDockWidget * m_imageViewDockWidget;
	ImageCanvas * m_imageView;

	QDockWidget * m_imageViewControlPanelDockWidget;
	ImageViewControlPanel * m_imageViewControlPanel;

	QDockWidget * m_profileViewDockWidget;
	ProfileView * m_profileView;

	QDockWidget * m_treeViewDockWidget;
	MarkTreeView * m_treeView;

	QDockWidget * m_markInfoDOckWidget;
	MarkInfoWidget * m_markInfoWidget;

	QDockWidget *m_tfEditorDockWidget;
	TF1DEditor * m_tfEditorWidget;
	//Menu
	QMenu * m_fileMenu;
	QMenu * m_viewMenu;
	//Status bar
	QStatusBar * m_statusBar;
	//Actions
	QAction * m_openAction;
	QAction * m_saveAction;
	QAction * m_openMarkAction;
	QAction * m_setDefaultLayoutAction;
};

#endif // MAINWINDOW_H
