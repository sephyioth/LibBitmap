//
// Created by 凌志 on 2018/11/8.
//
/**   
*    
* 项目名称：LibBitmap      
* 类描述：   
* 创建人：genesis   
* 创建时间：2018/11/8 3:58 PM   
* 修改人：genesis  
* 修改时间：2018/11/8 3:58 PM   
* 修改备注：   
* @version    
*    
*/
#include <memory.h>
#include <android/bitmap.h>
#include "GNBitmap.h"
#include "../GNBitmapContast.h"
#include "../BitmapUtills/BitmapUtills.h"


GNBitmap::GNBitmap()
{

}


GNBitmap::GNBitmap(int w, int h, int format, int flag, int stride)
{
    this->width      = w;
    this->height     = h;
    this->type       = format;
    this->flag       = flag;
    this->stride     = stride;
    this->bitmapData = malloc(sizeof(uint8_t) * w * h * getBitmapChannelSize());
}


GNBitmap::~GNBitmap()
{
    free(bitmapData);
}


int GNBitmap::recycle()
{
    free(bitmapData);
    return 1;
}


int GNBitmap::copyData(void* data, int btype)
{
    if (data == NULL)
    {
        return -1;
    }
    int size = width * height * getBitmapChannelSize();
    if (type == btype)
    {
        uint8_t* sdata = (uint8_t*) bitmapData;
        uint8_t* ddata = (uint8_t*) data;
        for (int i = 0; i < size; i++)
        {
            sdata[i] = ddata[i];
        }
    } else if (type == ANDROID_BITMAP_FORMAT_RGBA_8888 && btype == ANDROID_BITMAP_FORMAT_A_8)
    {
        LOGI("changed");
        argb   * tdata = (argb*) bitmapData;
        uint8_t* ddata = (uint8_t*) data;
        for (int i = 0; i < width * height; ++i)
        {
            tdata[i].blue  = ddata[i];
            tdata[i].green = ddata[i];
            tdata[i].red   = ddata[i];
        }

    } else if (type == ANDROID_BITMAP_FORMAT_A_8 && btype == ANDROID_BITMAP_FORMAT_RGBA_8888)
    {
        uint8_t* sdata = (uint8_t*) bitmapData;
        uint8_t* ddata = (uint8_t*) argb2gray((argb*) data, width, height);
        for (int i = 0; i < size; i++)
        {
            sdata[i] = ddata[i];
        }
    }
    return 1;
}


GNBitmap* GNBitmap::cloneBitmap()
{
    GNBitmap* bitmap = createBitmap(width, height, type);
    bitmap->copyData(bitmapData, type);
    return bitmap;

}


GNBitmap* GNBitmap::createBitmap()
{
    return createBitmap(width, height, type);
}


GNBitmap* GNBitmap::createBitmap(int w, int h, int format)
{
    GNBitmap* bitmap = new GNBitmap(w, h, format, 0, 0);
    return bitmap;
}


int GNBitmap::getBitmapChannelSize()
{
    switch (type)
    {
        case ANDROID_BITMAP_FORMAT_RGBA_4444:
            return 2;
        case ANDROID_BITMAP_FORMAT_RGB_565:
            return 2;
        case ANDROID_BITMAP_FORMAT_A_8:
            return 1;
        case ANDROID_BITMAP_FORMAT_RGBA_8888:
            return 4;
        default:
            return 0;
    }
}


int GNBitmap::zeroBitmap()
{
    int size = sizeof(uint8_t) * width * height * getBitmapChannelSize();
    memset((uint8_t*) bitmapData, 0, size);
    return 1;
}


int GNBitmap::invertBitmap()
{
    if (bitmapData == NULL || width < 0 || height < 0)
    {
        return 0;
    }
    int size = width * height * getBitmapChannelSize();

    uint8_t* data = (uint8_t*) bitmapData;
    for (int i = 0; i < size; ++i)
    {
        data[i] = 0xff - data[i];
    }
    return 1;
}