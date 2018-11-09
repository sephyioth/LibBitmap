//
// Created by 凌志 on 2018/11/8.
//
/**   
*    
* 项目名称：LibBitmap      
* 类描述：   
* 创建人：genesis   
* 创建时间：2018/11/8 5:25 PM   
* 修改人：genesis  
* 修改时间：2018/11/8 5:25 PM   
* 修改备注：   
* @version    
*    
*/

#include <cstdlib>
#include "BitmapUtills.h"


uint8_t* argb2gray(argb* bdata, int width, int height)
{
    if (bdata == NULL)
    {
        return NULL;
    }
    uint8_t* gray = (uint8_t*) malloc(sizeof(uint8_t) * width * height);
    int      w = width;
    int      h = height;
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int R     = bdata[x + y * w].red;
            int G     = bdata[x + y * w].green;
            int B     = bdata[x + y * w].blue;
            int A     = bdata[x + y * w].alpha;
            int Value = ((30 * R + 59 * G + 11 * B) / 100);
            gray[x + y * w] = Value;
        }
    }
    return gray;
}


uint8_t* transColors(GNBitmap* bitmap)
{
    if (bitmap == NULL)
    {
        return NULL;
    }
    uint8_t* data;
    if (bitmap->chennel == ANDROID_BITMAP_FORMAT_RGBA_8888)
    {
        data = argb2gray((argb*) bitmap->bitmapData, bitmap->width, bitmap->height);
    } else if (bitmap->chennel == ANDROID_BITMAP_FORMAT_A_8)
    {
        data = (uint8_t*) bitmap->bitmapData;
    }
    return data;
}


int convolution(uint8_t* data, double* model, uint8_t* dst, int w, int h, int col, int row)
{
    if (data == NULL || model == NULL || dst == NULL || w < 0 || h < 0 || col < 0 || row < 0)
    {
        return -1;
    }
    int      count = 0;
    for (int i     = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            double   sum   = 0;
            int      value = 0;
            for (int co    = 0; co < col; ++co)
            {
                for (int ro = 0; ro < row; ro++)
                {
                    int    c     = (i + co) > h ? h : i + co;
                    int    l     = (j + ro) > w ? w : j + ro;
                    double value = data[c * w + l];
                    sum += value * model[co * col + ro];
                }
            }
            value          = abs(sum);
            if (value > 255)
                value      = 255;
            if (value < 0)
                value      = 0;
            dst[i * w + j] = value;
            if (i > w / 2 && j > h / 2 && count < 20)
            {
                LOGI("value : %d", value);
                count++;
            }
        }
    }
    return 1;
}


int average(uint8_t* src1, uint8_t* src2, uint8_t* dst, int w, int h)
{
    if (src1 == NULL || src2 == NULL || dst == NULL || w < 0 || h < 0)
    {
        return -1;
    }
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            dst[i * w + j] = ((int) src1[i * w + j] + src2[i * w + j]) / 2;
        }
    }
    return 1;
}

