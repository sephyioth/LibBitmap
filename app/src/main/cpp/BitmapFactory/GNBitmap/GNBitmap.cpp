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


GNBitmap::GNBitmap()
{

}


GNBitmap::GNBitmap(int w, int h, int format, int flag, int stride)
{

}


GNBitmap::~GNBitmap()
{

}


int GNBitmap::recycle()
{
    free(bitmapData);
    return 1;
}


int GNBitmap::copyData(uint8_t* data, int btype)
{
    if (data == NULL)
    {
        return -1;
    }
    if (chennel == btype)
    {
        uint8_t* tdata = (uint8_t*) bitmapData;
        for (int i = 0; i < height * width; ++i)
        {
            tdata[i] = data[i];
        }
    } else if (chennel== ANDROID_BITMAP_FORMAT_RGBA_8888 && btype == ANDROID_BITMAP_FORMAT_A_8)
    {
        argb* tdata = (argb*) bitmapData;
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                tdata[i * width + j].blue  = data[i * width + j];
                tdata[i * width + j].green = data[i * width + j];
                tdata[i * width + j].red   = data[i * width + j];
            }
        }

    } else if (chennel == ANDROID_BITMAP_FORMAT_A_8 && btype == ANDROID_BITMAP_FORMAT_RGBA_8888)
    {

    }
    return 1;
}