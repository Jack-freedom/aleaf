#include "imagedata.h"
#include <QDebug>
ImageData::ImageData()
{

}

//将图像信息写入图像数据的类中
void ImageData::Write_ImageData()
{
    if(ImageData::img.depth()==8)
    {
        ImageDepth=ImageData::img.depth();
        ImageWidth=ImageData::img.width();
        ImageHeight=ImageData::img.height();
        PixelWidth=((ImageWidth+3)/4)*4;//每行像素个数与图像宽度的转换
        PixelHeight=ImageHeight;
        for(int i=0;i!=PixelHeight;++i)
        {
            uchar *linehead=ImageData::img.scanLine(i);//获得指向每行第一个像素的指针
            for(int j=0;j!=PixelWidth;++j,++linehead)//将该行像素的信息写入
                Each_Pixel.push_back(linehead);
        }
        for(auto beg=Each_Pixel.begin();beg!=Each_Pixel.end();++beg)//获得灰度值数组
        {
            int temp=int(**beg);
            ++Graylevel[temp];
        }
        for(int i=0;i!=256;++i)//获得像元数最大的灰度值的像元数
            if(Graylevel[i]>Max_Ingraylevel)
                Max_Ingraylevel=Graylevel[i];
    }
    else if(ImageData::img.depth()==32)
    {
        ImageDepth=ImageData::img.depth();
        ImageWidth=ImageData::img.width();
        ImageHeight=ImageData::img.height();
        PixelWidth=ImageWidth*4;
        PixelHeight=ImageHeight;
        for(int i=0;i!=PixelHeight;++i)
        {
            uchar *linehead=ImageData::img.scanLine(i);//获得指向每行第一个像素的指针
            for(int j=0;j!=PixelWidth;++j,++linehead)//将该行像素的信息写入
            {
                if(j%4==0)
                    Each_Pixel_Blue.push_back(linehead);
                else if(j%4==1)
                    Each_Pixel_Green.push_back(linehead);
                else if(j%4==2)
                    Each_Pixel_Red.push_back(linehead);
                else if(j%4==3)
                    Each_Pixel_Alpha.push_back(linehead);
            }
        }
        for(auto beg=Each_Pixel_Blue.begin();beg!=Each_Pixel_Blue.end();++beg)//获得Blue数组
        {
            int temp=int(**beg);
            ++Blue[temp];
        }
        for(auto beg=Each_Pixel_Green.begin();beg!=Each_Pixel_Green.end();++beg)//获得Green数组
        {
            int temp=int(**beg);
            ++Green[temp];
        }
        for(auto beg=Each_Pixel_Red.begin();beg!=Each_Pixel_Red.end();++beg)//获得Red数组
        {
            int temp=int(**beg);
            ++Red[temp];
        }
        for(auto beg=Each_Pixel_Alpha.begin();beg!=Each_Pixel_Alpha.end();++beg)//获得透明度数组
        {
            int temp=int(**beg);
            ++Alpha[temp];
        }
        for(int i=0;i!=256;++i)//获得Blue数组中像元数的最大值
            if(Blue[i]>Max_InBlue)
                Max_InBlue=Blue[i];
        for(int i=0;i!=256;++i)//获得Green数组中像元数的最大值
            if(Green[i]>Max_InGreen)
                Max_InGreen=Green[i];
        for(int i=0;i!=256;++i)//获得Red数组中像元数的最大值
            if(Red[i]>Max_InRed)
                Max_InRed=Red[i];
    }
}

//图像的接口
QImage &ImageData::Get_Image()
{
    return this->img;
}

//图像深度的接口
int ImageData::Get_Depth()
{
    return ImageDepth;
}

//像元数总数的接口
long long ImageData::Get_Pixelnumber()
{
    return PixelWidth*PixelHeight;
}

//灰度值数组的接口
long long *ImageData::Get_Graylevel()
{
    return Graylevel;
}

//像元数最大的灰度值的像元数的接口
long long ImageData::Get_Max_Ingraylevel()
{
    return Max_Ingraylevel;
}

//Blue数组的接口
long long *ImageData::Get_Blue()
{
    return Blue;
}

//Green数组的接口
long long *ImageData::Get_Green()
{
    return Green;
}

//Red数组的接口
long long *ImageData::Get_Red()
{
    return Red;
}

//Alpha数组的接口
long long *ImageData::Get_Alpha()
{
    return Alpha;
}

//Blue数组中像元数的最大值接口
long long ImageData::Get_Max_InBlue()
{
    return Max_InBlue;
}

//Green数组中像元数的最大值接口
long long ImageData::Get_Max_InGreen()
{
    return Max_InGreen;
}

//Red数组中像元数的最大值接口
long long ImageData::Get_Max_InRed()
{
    return Max_InRed;
}

//X轴翻折的像素信息处理
void ImageData::Image_Mirror_X()
{
    for(int i=0;i<=PixelHeight/2;++i)
    {
        uchar *eachpixel_1=this->img.scanLine(i);
        uchar *eachpixel_2=this->img.scanLine(this->PixelHeight-1-i);
        for(int j=0;j!=this->PixelWidth;++j)
        {
            uchar temp=*eachpixel_1;
            *eachpixel_1=*eachpixel_2;
            *eachpixel_2=temp;
            ++eachpixel_1;
            ++eachpixel_2;
        }
    }
}
//Y轴翻折的像素信息处理
void ImageData::Image_Mirror_Y()
{
    if(ImageDepth==8)
    {
        for(int i=0;i!=PixelHeight;++i)
        {
            uchar *eachpixel_1=this->img.scanLine(i);
            for(int j=0;j!=PixelWidth;++j)
                ++eachpixel_1;
            uchar *eachpixel_2=eachpixel_1;
            eachpixel_1=this->img.scanLine(i);
            for(int j=0;j<=(PixelWidth-1)/2;++j)
            {
                uchar temp=*eachpixel_1;
                *eachpixel_1=*eachpixel_2;
                *eachpixel_2=temp;
                ++eachpixel_1;
                --eachpixel_2;
            }
        }
    }
    else if(ImageDepth==32)
    {
        for(int i=0;i!=PixelHeight;++i)
        {
            //交换blue的值
            uchar *eachpixel_1=this->img.scanLine(i);
            for(int j=0;j!=PixelWidth-1;++j)
                ++eachpixel_1;
            uchar *eachpixel_2=eachpixel_1-3;
            eachpixel_1=this->img.scanLine(i);
            for(int j=0;j!=(ImageWidth-1)/2;++j)
            {
                uchar temp=*eachpixel_1;
                *eachpixel_1=*eachpixel_2;
                *eachpixel_2=temp;
                eachpixel_1+=4;
                eachpixel_2-=4;
            }
            //交换Green的值
            eachpixel_1=this->img.scanLine(i);
            for(int j=0;j!=PixelWidth-1;++j)
                ++eachpixel_1;
            eachpixel_2=eachpixel_1-2;
            eachpixel_1=this->img.scanLine(i)+1;
            for(int j=0;j!=(ImageWidth-1)/2;++j)
            {
                uchar temp=*eachpixel_1;
                *eachpixel_1=*eachpixel_2;
                *eachpixel_2=temp;
                eachpixel_1+=4;
                eachpixel_2-=4;
            }
            //交换Red的值
            eachpixel_1=this->img.scanLine(i);
            for(int j=0;j!=PixelWidth-1;++j)
                ++eachpixel_1;
            eachpixel_2=eachpixel_1-1;
            eachpixel_1=this->img.scanLine(i)+2;
            for(int j=0;j!=(ImageWidth-1)/2;++j)
            {
                uchar temp=*eachpixel_1;
                *eachpixel_1=*eachpixel_2;
                *eachpixel_2=temp;
                eachpixel_1+=4;
                eachpixel_2-=4;
            }
            //交换Alpha的值
            eachpixel_1=this->img.scanLine(i);
            for(int j=0;j!=PixelWidth-1;++j)
                ++eachpixel_1;
            eachpixel_2=eachpixel_1;
            eachpixel_1=this->img.scanLine(i)+3;
            for(int j=0;j!=(ImageWidth-1)/2;++j)
            {
                uchar temp=*eachpixel_1;
                *eachpixel_1=*eachpixel_2;
                *eachpixel_2=temp;
                eachpixel_1+=4;
                eachpixel_2-=4;
            }
        }
    }
}


//中心镜像的像素信息处理
void ImageData::Image_Mirror_Centre()
{
    //方法一
    //this->Image_Mirror_X();
    //this->Image_Mirror_Y();
    //方法二
    if(ImageDepth==8)
        for(auto p=Each_Pixel.begin(),q=Each_Pixel.end()-1;q-p>0;++p,--q)
        {
            if(p==Each_Pixel.begin())
            {
                qDebug()<<**p<<**q;
            }
            auto temp=**p;
            **p=**q;
            **q=temp;
        }
    //qDebug()<<*img.scanLine(0);
}

//负片的像素信息处理
void ImageData::Image_Negative()
{

    for(int i=0;i!=PixelHeight;++i)
    {
        uchar *eachpixel=this->img.scanLine(i);
        for(int j=0;j!=PixelWidth;++j,++eachpixel)
            *eachpixel=255-*eachpixel;
    }
    if(ImageDepth==8)
    {
        for(int i=0;i!=256;++i)
            Graylevel[i]=0;
        for(auto beg=Each_Pixel.begin();beg!=Each_Pixel.end();++beg)//获得灰度值数组
        {
            int temp=int(**beg);
            ++Graylevel[temp];
        }
        qDebug()<<(void*)img.bits()<<*Each_Pixel.begin();
    }
}

void ImageData::Image_Binaryzation()
{
    if(ImageDepth==8)
    {
        for(int i=0;i!=PixelHeight;++i)
        {
            uchar *eachpixel=this->img.scanLine(i);
            for(int j=0;j!=PixelWidth;++j,++eachpixel)
            {
                if(*eachpixel>threshold)
                    *eachpixel=255;
                else
                    *eachpixel=0;
            }
        }
    }
}
