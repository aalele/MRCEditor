#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "testinfodialog.h"


QSize imageSize(500,500);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _init();
    m_hist = new Histogram(this);
    ui->leftVLayout->addWidget(m_hist);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    if(m_currentContext != -1){
        QMessageBox::critical(this,"Error",
                              tr("Multi files aren't supported now\n"),
                              QMessageBox::Yes,QMessageBox::Yes);
        return;
    }
    QString fileName =QFileDialog::getOpenFileName(this,tr("OpenFile"),tr("/Users/Ysl/Downloads/ETdataSegmentation"),tr("Image Files(*.mrc)"));
    if(fileName == ""){
        return;
    }
   // ui->comboBox->addItem(fileName);
    //m_mrcs.push_back(MRC(fileName));
    MRC mrc(fileName);
    QString name = fileName.mid(fileName.lastIndexOf('/')+1);
    if(mrc.isOpened() == false){
        QMessageBox::critical(NULL, "Error", tr("Can't open this file.\n%1").arg(fileName),
                              QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }else{
        QString headerInfo = mrc.getMRCInfo();
        //ui->textEdit->setText(headerInfo);
        //APPENDINFO(headerInfo)
        //m_mrcs.push_back(std::move(mrc));
        _createMRCContext(std::move(mrc));
        _setMRCContext(m_mrcs.size()-1);
        _displayImage(imageSize);
        m_currentContext = m_mrcs.size() - 1;
        //ui->mrcFileCBox->insertItem(0,QIcon(),);
        ui->mrcFileCBox->addItem(name,m_currentContext);
        //m_imageView->setPixmap(QPixmap::fromImage(m_mrcs.back().getSlice(0)));
    }

}


void MainWindow::_createMRCContext(const MRC &mrc)
{
    MRCContext mrcContext;
    mrcContext.currentMaxGray=255;
    mrcContext.currentMinGray = 0;
    mrcContext.minSlice = 0;
    mrcContext.maxSlice=mrc.getSliceCount()-1;


    mrcContext.currentSlice = 0;
    mrcContext.currentScale =1.0f;

    mrcContext.mrcFile = mrc;
    int imageCount = mrcContext.maxSlice;
    for(int i=0;i<imageCount;i++){
        mrcContext.images.push_back(QPixmap::fromImage(mrcContext.mrcFile.getSlice(i)));
    }
    m_mrcs.push_back(mrcContext);
}

void MainWindow::_createMRCContext(MRC && mrc)
{
    MRCContext mrcContext;
    mrcContext.currentMaxGray=255;
    mrcContext.currentMinGray = 0;
    mrcContext.minSlice = 0;
    mrcContext.maxSlice=mrc.getSliceCount()-1;
    mrcContext.currentSlice = 0;
    mrcContext.currentScale =1.0f;
    mrcContext.mrcFile = std::move(mrc);
    int imageCount = mrcContext.maxSlice;
    for(int i=0;i<imageCount;i++){
        mrcContext.images.push_back(QPixmap::fromImage(mrcContext.mrcFile.getSlice(i)));
    }
    m_mrcs.push_back(mrcContext);
}

void MainWindow::_setMRCContext(int index)
{

    ui->sliceSlider->setEnabled(true);
    ui->scaleSpinBox->setEnabled(true);
    ui->minGraySlider->setEnabled(true);
    ui->minGraySpinBox->setEnabled(true);
    ui->maxGraySlider->setEnabled(true);
    ui->maxGraySpinBox->setEnabled(true);
    ui->scaleSlider->setEnabled(true);
    ui->scaleSpinBox->setEnabled(true);

    const MRCContext CTX = m_mrcs[index];

    //other settings
    //ui->horizontalSlider->setMaximum(m_mrcs[index].maxSlice);
    /*Min Gray Slider and SpinBox*/
    ui->sliceSlider->setMaximum(CTX.maxSlice);
    ui->sliceSlider->setMinimum(CTX.minSlice);
    ui->sliceSlider->setValue(CTX.currentSlice);

    ui->sliceSpinBox->setMaximum(CTX.maxSlice);
    ui->sliceSpinBox->setMinimum(CTX.minSlice);
    ui->sliceSpinBox->setValue(CTX.currentSlice);

    /*Max Gray Slider and SpinBox*/
    ui->minGraySlider->setMinimum(0);
    ui->minGraySlider->setMaximum(255);
    ui->minGraySlider->setValue(CTX.currentMinGray);
    ui->minGraySpinBox->setMinimum(0);
    ui->minGraySpinBox->setMaximum(255);
    ui->minGraySpinBox->setValue(CTX.currentMinGray);

    /*Min Gray Slider and SpinBox*/
    ui->maxGraySlider->setMinimum(0);
    ui->maxGraySlider->setMaximum(255);
    ui->maxGraySlider->setValue(CTX.currentMaxGray);
    ui->maxGraySpinBox->setMinimum(0);
    ui->maxGraySpinBox->setMaximum(255);
    ui->maxGraySpinBox->setValue(CTX.currentMaxGray);

    /*Scale Slider and SpinBox*/
    ui->scaleSlider->setValue(CTX.currentScale);
    ui->scaleSlider->setMinimum(0);

    /*Histogram*/
    m_hist->setImage(CTX.mrcFile.getSlice(CTX.currentSlice));

    m_currentContext = index;

}

void MainWindow::_saveMRCContext()
{
    MRCContext & CTX = m_mrcs[m_currentContext];
    CTX.currentSlice = ui->sliceSlider->value();
    CTX.currentMinGray = ui->minGraySlider->value();
    CTX.currentMaxGray = ui->maxGraySlider->value();
    //CTX.currentScale = ui->scaleSlider->value();

}

void MainWindow::_updateGrayThreshold(int minGray, int maxGray)
{
    size_t width = m_mrcs[m_currentContext].mrcFile.getWidth();
    size_t height = m_mrcs[m_currentContext].mrcFile.getHeight();
    size_t length = width*height;
    qDebug()<<"W & H of the image:"<<width<<" "<<height;
    unsigned char *image = m_mrcs[m_currentContext].mrcFile.getSlice(ui->sliceSlider->value()).bits();


    //QPixmap pix = QPixmap::fromImage(m_mrcs[m_currentContext].mrcFile.getSlice(ui->sliceSlider->value()));
    m_mask = QBitmap(width,height);
    QPainter painter(&m_mask);
    for(int j=0;j<height;j++){
        for(int i=0;i<width;i++){
            int index = i+j*width;
            if(image[index]>=minGray && image[index]<=maxGray){
                painter.setPen(Qt::color1);
                painter.drawPoint(QPoint(i,j));

            }else{
                painter.setPen(Qt::color0);
                painter.drawPoint(QPoint(i,j));
            }
        }
    }
    //qDebug()<<m_mask;
    //img.setMask(QBitmap());
    //m_mrcs[m_currentContext].images[ui->sliceSlider->value()]=pix;
    m_mrcs[m_currentContext].images[ui->sliceSlider->value()].setMask(m_mask);
    //m_imageLabel->setPixmap(m_mrcs[m_currentContext].images[ui->sliceSlider->value()]);
}

void MainWindow::_displayImage(QSize size)
{
    int index = ui->sliceSlider->value();
    m_image = m_mrcs[m_currentContext].images[index].scaled(size,Qt::IgnoreAspectRatio);
    m_imageLabel->setPixmap(m_image);
}

void MainWindow::_init()
{
    m_imageLabel =  new QLabel(this);
    m_imageLabel->setScaledContents(true);
    QHBoxLayout * layout = new QHBoxLayout(this);

    layout->addWidget(m_imageLabel);
    ui->leftGroupBox->setLayout(layout);
    m_currentContext = -1;

    ui->sliceSlider->setEnabled(false);
    ui->scaleSpinBox->setEnabled(false);
    ui->minGraySlider->setEnabled(false);
    ui->minGraySpinBox->setEnabled(false);
    ui->maxGraySlider->setEnabled(false);
    ui->maxGraySpinBox->setEnabled(false);
    ui->scaleSlider->setEnabled(false);
    ui->scaleSpinBox->setEnabled(false);
}

void MainWindow::on_sliceSlider_sliderMoved(int position)
{
    //qDebug()<<"Slider moved:"<<position<<" "<<ui->sliceSlider->maximum();
    //on_sliceSlider_valueChanged(position);
    //m_imageLabel->setPixmap(m_mrcs[m_currentContext].images[position]);
}

void MainWindow::on_maxGraySlider_sliderMoved(int position)
{
    if(position < ui->minGraySlider->value()){
        ui->minGraySlider->setValue(position);
        ui->minGraySpinBox->setValue(position);
    }
    ui->maxGraySlider->setValue(position);
    ui->maxGraySpinBox->setValue(position);
    _updateGrayThreshold(ui->minGraySlider->value(),ui->maxGraySlider->value());
    _displayImage(imageSize);
}

void MainWindow::on_minGraySlider_sliderMoved(int position)
{
    if(position > ui->maxGraySlider->value()){
        ui->maxGraySlider->setValue(position);
        ui->maxGraySpinBox->setValue(position);
    }
    ui->minGraySlider->setValue(position);
    ui->minGraySpinBox->setValue(position);

    _updateGrayThreshold(ui->minGraySlider->value(),ui->maxGraySlider->value());
    _displayImage(imageSize);
}

void MainWindow::on_sliceSlider_valueChanged(int value)
{
    if(value>= ui->sliceSlider->maximum())
        return;
    ui->sliceSlider->setValue(value);
    ui->sliceSpinBox->setValue(value);
    _displayImage(imageSize);
    m_hist->setImage(m_mrcs[m_currentContext].mrcFile.getSlice(value));
}
