#ifndef GRADATION_HISTOGRAM_H
#define GRADATION_HISTOGRAM_H

#include "imagedata.h"
#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QPointF>
#include <QString>
#include <QMouseEvent>
#include <QStatusBar>
#include <QDebug>

namespace Ui {
class Gradation_Histogram;
}

class Gradation_Histogram : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gradation_Histogram(QWidget *parent = nullptr);
    explicit Gradation_Histogram(ImageData* id):data(id)
    {
        QStatusBar *statusbar=new QStatusBar;
        this->show();//显示窗口
        this->setFixedSize(800,600);//固定窗口大小
        this->setWindowTitle("灰度直方图");//设置窗口标题
        this->setMouseTracking(true);//开启鼠标跟踪
    };
    ~Gradation_Histogram();
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);

private:
    Ui::Gradation_Histogram *ui;
    ImageData *data;//储存图像数据的类
    bool paint_line_or_bar=true;//控制绘制折线图或柱状图
};

#endif // GRADATION_HISTOGRAM_H
