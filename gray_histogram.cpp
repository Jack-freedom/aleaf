#include "gray_histogram.h"

Gradation_Histogram::Gradation_Histogram(QWidget *parent) :
    QMainWindow(parent){}

Gradation_Histogram::~Gradation_Histogram()
{
    delete this;
}

//绘制灰度直方图
void Gradation_Histogram::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int Window_Width=this->width();//窗口宽度
    int Window_Height=this->height();//窗口高度
    QPointF x_axis_start_point(0,0.9*Window_Height);//X轴起点
    QPointF x_axis_end_point(Window_Width,0.9*Window_Height);//X轴终点
    QPointF y_axis_start_point(0.1*Window_Width,0);//Y轴起点
    QPointF y_axis_end_point(0.1*Window_Width,0.95*Window_Height);//Y轴终点
    QPointF origin(0.1*Window_Width,0.9*Window_Height);//原点坐标
    qreal x_per_unit_length=0.8*Window_Width/255;//X轴单位长度
    painter.drawLine(x_axis_start_point,x_axis_end_point);//画X轴（灰度值）
    painter.drawLine(y_axis_start_point,y_axis_end_point);//画Y轴（像元数）
    painter.drawText(QPointF(0.08*Window_Width,0.93*Window_Height),"0");//显示X轴上0点
    painter.drawText(QPointF(0.1*Window_Width+(255*x_per_unit_length),0.93*Window_Height),"255");//显示X轴上255点
    for(int i=20;i<256;i+=20)//每隔20个单位长度（即灰度值每增加20）显示灰度值，即X轴坐标
    {
        QPointF point1(0.1*Window_Width+i*x_per_unit_length,0.9*Window_Height);
        QPointF point2(0.1*Window_Width+i*x_per_unit_length,0.895*Window_Height);
        painter.drawLine(point1,point2);
        painter.drawText(QPointF(0.1*Window_Width+(i*x_per_unit_length),0.93*Window_Height),QString::number(i));
    }
    if(data->Get_Depth()==8)
    {
        qreal y_per_unit_length=0.8*Window_Height/data->Get_Max_Ingraylevel();//Y轴单位长度
        painter.drawText(QPointF(0.025*Window_Width,0.9*Window_Height-data->Get_Max_Ingraylevel()*y_per_unit_length),QString::number(data->Get_Max_Ingraylevel()));//显示Y轴上最大的像元数
        for(int i=data->Get_Max_Ingraylevel()/16;i<data->Get_Max_Ingraylevel()*15/16;i+=data->Get_Max_Ingraylevel()/16)//每隔一定单位长度显示像元数，即Y轴坐标
        {
            QPointF point1(0.1*Window_Width,0.9*Window_Height-i*y_per_unit_length);
            QPointF point2(0.105*Window_Width,0.9*Window_Height-i*y_per_unit_length);
            painter.drawLine(point1,point2);
            painter.drawText(QPointF(0.025*Window_Width,0.9*Window_Height-i*y_per_unit_length),QString::number(i));

        }
        if(paint_line_or_bar==true)
        {
            long long *head_of_graylevel=data->Get_Graylevel();//获得灰度值数组
            for(int i=0;i!=255;)//绘制灰度直方图——折线图
            {
                QPointF point1(0.1*Window_Width+i*x_per_unit_length,0.9*Window_Height-(*head_of_graylevel)*y_per_unit_length);
                QPointF point2(0.1*Window_Width+(++i*x_per_unit_length),0.9*Window_Height-(*++head_of_graylevel)*y_per_unit_length);
                painter.drawLine(point1,point2);
            }
        }
        else
        {
            long long *head_of_graylevel=data->Get_Graylevel();//获得灰度值数组
            for(int i=0;i!=256;++i,++head_of_graylevel)//绘制灰度直方图——柱状图
            {
                QPointF point1(0.1*Window_Width+i*x_per_unit_length,0.9*Window_Height);
                QPointF point2(0.1*Window_Width+i*x_per_unit_length,0.9*Window_Height-(*head_of_graylevel)*y_per_unit_length);
                QPen pen;
                pen.setWidthF(x_per_unit_length);
                painter.setPen(pen);
                painter.drawLine(point1,point2);
            }
        }

    }
    else if(data->Get_Depth()==32)
    {
        long long Max_Inall=(data->Get_Max_InBlue()>data->Get_Max_InGreen()?data->Get_Max_InBlue():data->Get_Max_InGreen())>data->Get_Max_InRed()?(data->Get_Max_InBlue()>data->Get_Max_InGreen()?data->Get_Max_InBlue():data->Get_Max_InGreen()):data->Get_Max_InRed();
        qreal y_per_unit_length=0.8*Window_Height/Max_Inall;//Y轴单位长度
        painter.drawText(QPointF(0.025*Window_Width,0.9*Window_Height-Max_Inall*y_per_unit_length),QString::number(Max_Inall));//显示Y轴上最大的像元数
        long long *head_of_Blue=data->Get_Blue();//获得Blue数组
        long long *head_of_Green=data->Get_Green();//获得Green数组
        long long *head_of_Red=data->Get_Red();//获得Red数组
        for(int i=Max_Inall/16;i<Max_Inall*15/16;i+=Max_Inall/16)//每隔一定单位长度显示像元数，即Y轴坐标
        {
            QPointF point1(0.1*Window_Width,0.9*Window_Height-i*y_per_unit_length);
            QPointF point2(0.105*Window_Width,0.9*Window_Height-i*y_per_unit_length);
            painter.drawLine(point1,point2);
            painter.drawText(QPointF(0.025*Window_Width,0.9*Window_Height-i*y_per_unit_length),QString::number(i));

        }
        for(int i=0;i!=255;)//绘制Blue直方图——折线图
        {
            QPen pen(QColor(0,0,255,255));
            painter.setPen(pen);
            QPointF point1(0.1*Window_Width+i*x_per_unit_length,0.9*Window_Height-(*head_of_Blue)*y_per_unit_length);
            QPointF point2(0.1*Window_Width+(++i*x_per_unit_length),0.9*Window_Height-(*++head_of_Blue)*y_per_unit_length);
            painter.drawLine(point1,point2);
        }
        for(int i=0;i!=255;)//绘制Green直方图——折线图
        {
            QPen pen(QColor(0,255,0,255));
            painter.setPen(pen);
            QPointF point1(0.1*Window_Width+i*x_per_unit_length,0.9*Window_Height-(*head_of_Green)*y_per_unit_length);
            QPointF point2(0.1*Window_Width+(++i*x_per_unit_length),0.9*Window_Height-(*++head_of_Green)*y_per_unit_length);
            painter.drawLine(point1,point2);
        }
        for(int i=0;i!=255;)//绘制Red直方图——折线图
        {
            QPen pen(QColor(255,0,0,255));
            painter.setPen(pen);
            QPointF point1(0.1*Window_Width+i*x_per_unit_length,0.9*Window_Height-(*head_of_Red)*y_per_unit_length);
            QPointF point2(0.1*Window_Width+(++i*x_per_unit_length),0.9*Window_Height-(*++head_of_Red)*y_per_unit_length);
            painter.drawLine(point1,point2);
        }
    }

}

//鼠标移动时在状态栏显示鼠标所在点表示的灰度值即像元数
void Gradation_Histogram::mouseMoveEvent(QMouseEvent *ev)
{
    if(data->Get_Depth()==8)
    {
        QPointF mouse_pos=ev->localPos();
        int pos_to_garylevel=int((mouse_pos.x()-0.1*this->width())/(0.8*this->width()/255));
        if(pos_to_garylevel>=0&&pos_to_garylevel<=255)
        {
            QString show_in_statusbar{"灰度值: "};
            show_in_statusbar+=QString::number(pos_to_garylevel);
            show_in_statusbar+=" 像元数: ";
            show_in_statusbar+=QString::number(*(data->Get_Graylevel()+pos_to_garylevel));
            show_in_statusbar+=" 像元数总数: ";
            show_in_statusbar+=QString::number(data->Get_Pixelnumber());
            this->statusBar()->showMessage(show_in_statusbar);
        }
    }
    else if(data->Get_Depth()==32)
    {
        QPointF mouse_pos=ev->localPos();
        int pos_to_RGB=int((mouse_pos.x()-0.1*this->width())/(0.8*this->width()/255));
        if(pos_to_RGB>=0&&pos_to_RGB<=255)
        {
            QString show_in_statusbar{"灰度值: "};
            show_in_statusbar+=QString::number(pos_to_RGB);
            show_in_statusbar+=" Red像元数: ";
            show_in_statusbar+=QString::number(*(data->Get_Red()+pos_to_RGB));
            show_in_statusbar+=" Green像元数: ";
            show_in_statusbar+=QString::number(*(data->Get_Green()+pos_to_RGB));
            show_in_statusbar+=" Blue像元数: ";
            show_in_statusbar+=QString::number(*(data->Get_Blue()+pos_to_RGB));
            show_in_statusbar+=" 像元数总数: ";
            show_in_statusbar+=QString::number(data->Get_Pixelnumber());
            this->statusBar()->showMessage(show_in_statusbar);
        }
    }

}

void Gradation_Histogram::mousePressEvent(QMouseEvent *ev)
{
    paint_line_or_bar=!paint_line_or_bar;
    update();
}
