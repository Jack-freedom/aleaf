#include "mainwindow.h"
#include "imagedata.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMouseTracking(true);
    //菜单——文件
    connect(this->ui->actionOpen,&QAction::triggered,this,&MainWindow::OpenImage);
    connect(this->ui->actionReread_image,&QAction::triggered,this,&MainWindow::ReOpenImage);
    //菜单——基本图像处理
    connect(this->ui->actionGray_Histogram,&QAction::triggered,this,&MainWindow::ShowGray_Histogram);
    connect(this->ui->actionNegative,&QAction::triggered,this,&MainWindow::Negative);
    connect(this->ui->actionBinaryzation,&QAction::triggered,this,&MainWindow::Binaryzation);
    //菜单——几何变换
    connect(this->ui->actionMirror_X,&QAction::triggered,this,&MainWindow::Mirror_X);
    connect(this->ui->actionMirror_Y,&QAction::triggered,this,&MainWindow::Mirror_Y);
    connect(this->ui->actionMirror_Centre,&QAction::triggered,this,&MainWindow::Mirror_Centre);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//打开图像，将图像写入
void MainWindow::OpenImage()
{
    path=QFileDialog::getOpenFileName(this,tr("OpenImage"),"C:\\",tr("Image(*.bmp *.jpg)"));
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this,"error","fail to open the image",QMessageBox::Ok);
        return;
    }
    file.close();
    MainWindow::paintEventflag=this->img.load(path);
    Set_showImage();
    ID=ImageData(MainWindow::img);
    ID.Write_ImageData();
    Original_ID=ID;
    update();
}

//重读图像
void MainWindow::ReOpenImage()
{
    if(img.isNull())
    {
        QMessageBox::warning(this,"error","please open an image",QMessageBox::Ok);
        return;
    }
    ID=Original_ID;
    Set_showImage();
    update();
}
//设置显示图像的左上点（left&&top、宽(show_width)、高(show_height)
void MainWindow::Set_showImage()
{
    if((this->width()/(img.width()*1.0))>(this->height()/(img.height()*1.0)))
    {
        show_width=img.width()*(this->height()/(img.height()*1.0));
        show_height=this->height();
        left=(this->width()-show_width)/2;
        top=0;
    }
    else
    {
        show_height=img.height()*(this->width()/(img.width()*1.0));
        show_width=this->width();
        left=0;
        top=(this->height()-show_height)/2;
    }
}

//显示图像与状态栏
void MainWindow::paintEvent(QPaintEvent *event)
{
    if(paintEventflag)
    {
        this->img=ID.Get_Image();
        QPainter painter(this);
        painter.drawImage(QRectF(left,top,show_width,show_height),this->img);
        this->statusBar()->showMessage(path);
    }
}

//显示灰度直方图
void MainWindow::ShowGray_Histogram()
{
    Gradation_Histogram *GH=new Gradation_Histogram(&ID);
}

//提供图像文件的接口
QImage& MainWindow::Get_Image()
{
    return MainWindow::img;
}

//实现图像的移动
void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    mouse_pressed=true;
    mouse_pressed_pos=ev->localPos();
    QCursor mousecursor(Qt::OpenHandCursor);
    this->setCursor(mousecursor);
}

void MainWindow::mouseMoveEvent (QMouseEvent *ev)
{
    if(mouse_pressed==true)
    {
        left+=ev->localPos().x()-mouse_pressed_pos.x();
        top+=ev->localPos().y()-mouse_pressed_pos.y();
        mouse_pressed_pos=ev->localPos();
        update();
    }
}

void MainWindow::mouseRealseEvent(QMouseEvent *ev)
{
    mouse_pressed=false;
    QCursor mousecursor(Qt::ArrowCursor);
    this->setCursor(mousecursor);
}

//实现图像的放缩
void MainWindow::wheelEvent(QWheelEvent *ev)
{
    if(ev->angleDelta().y()>0)
    {
        show_width*=size_change;
        show_height*=size_change;
        left=ev->position().x()-(ev->position().x()-left)*size_change;
        top=ev->position().y()-(ev->position().y()-top)*size_change;
        update();
    }
    else if(ev->angleDelta().y()<0)
    {
        show_width/=size_change;
        show_height/=size_change;
        left=ev->position().x()-(ev->position().x()-left)/size_change;
        top=ev->position().y()-(ev->position().y()-top)/size_change;
        update();
    }
    update();
}

//实现图像沿X轴的翻转
void MainWindow::Mirror_X()
{
    ID.Image_Mirror_X();
    update();
}

void MainWindow::Mirror_Y()
{
    ID.Image_Mirror_Y();
    update();
}

void MainWindow::Mirror_Centre()
{
    ID.Image_Mirror_Centre();
    update();
}

void MainWindow::Negative()
{
    ID.Image_Negative();
    update();
}

void MainWindow::Binaryzation()
{
    ID.Image_Binaryzation();
    update();
}
