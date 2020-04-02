#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "gray_histogram.h"
#include "imagedata.h"
#include <QAction>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QPainter>
#include <QDebug>
#include <QImage>
#include <QMouseEvent>
#include <QCursor>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    QImage& Get_Image();
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent (QMouseEvent *ev);
    void mouseRealseEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);
    void Set_showImage();

private slots:
    void OpenImage();
    void ReOpenImage();
    void ShowGray_Histogram();
    void Mirror_X();
    void Mirror_Y();
    void Mirror_Centre();
    void Negative();
    void Binaryzation();

private:
    Ui::MainWindow *ui;
    QImage img;//储存图像
    QString path;//储存图像路径
    ImageData ID;//储存图像数据的类
    ImageData Original_ID;//储存初始图像数据的类，用于重读图像
    bool paintEventflag=false;//控制图像显示
    double left=0;//图像左上点横坐标
    double top=0;//图像左上点纵坐标
    double show_width=0;//显示的图像宽度
    double show_height=0;//显示的图像高度
    bool mouse_pressed=false;//鼠标是否按下
    QPointF mouse_pressed_pos;//鼠标按下时的坐标
    double size_change=1.5;//图像放大缩小的倍率

};
#endif // MAINWINDOW_H
