#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <QImage>
#include <QVector>
class ImageData
{
public:
    ImageData();
    ImageData(QImage & pic):img(pic){}
    void Write_ImageData();

    //接口函数
    QImage &Get_Image();
    int Get_Depth();
    long long Get_Pixelnumber();
    long long *Get_Graylevel();
    long long Get_Max_Ingraylevel();
    long long *Get_Blue();
    long long *Get_Green();
    long long *Get_Red();
    long long *Get_Alpha();
    long long Get_Max_InBlue();
    long long Get_Max_InGreen();
    long long Get_Max_InRed();

    void Image_Mirror_X();
    void Image_Mirror_Y();
    void Image_Mirror_Centre();
    void Image_Negative();
    void Image_Binaryzation();

private:
    QImage img;//储存图像
    int ImageDepth;//图像深度
    int ImageWidth;//图像宽度
    int ImageHeight;//图像高度
    int PixelWidth;//每行像素个数，即bytesPerLine()
    int PixelHeight;//像素的行数

    //8为灰度图像信息
    QVector<uchar*> Each_Pixel;//灰度图像中每个像素（字节）中储存的信息
    long long Graylevel[256]={};//灰度值
    long long Max_Ingraylevel=0;
    int threshold=128;//二值化阈值

    //32位彩色图像信息
    QVector<uchar*> Each_Pixel_Blue;
    QVector<uchar*> Each_Pixel_Green;
    QVector<uchar*> Each_Pixel_Red;
    QVector<uchar*> Each_Pixel_Alpha;
    long long Blue[256]={};
    long long Green[256]={};
    long long Red[256]={};
    long long Alpha[256]={};
    long long Max_InBlue=0;
    long long Max_InGreen=0;
    long long Max_InRed=0;

};

#endif // IMAGEDATA_H
