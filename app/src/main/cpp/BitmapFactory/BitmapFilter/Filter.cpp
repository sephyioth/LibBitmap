//
// Created by 凌志 on 2018/11/13.
//
/**   
*    
* 项目名称：LibBitmap      
* 类描述：   
* 创建人：genesis   
* 创建时间：2018/11/13 10:27 AM   
* 修改人：genesis  
* 修改时间：2018/11/13 10:27 AM   
* 修改备注：   
* @version    
*    
*/
#include "Filter.h"
#include "../GNBitmapContast.h"
#include "../BitmapUtills/BitmapUtills.h"

#define  RELIEF_LEVEL  3

#define step(shift) \
   if((0x40000000l >> shift) + root <= value) {        \
      value -= (0x40000000l >> shift) + root;          \
      root = (root >> 1) | (0x40000000l >> shift);     \
   }                                                   \
   else {                                              \
      root = root >> 1;                                \
   }


int gnSqrt(int value, int depth)
{
    int      root = 0;
    for (int i    = 0; i < depth; ++i)
    {
        step(i * 2);
    }
    // round to the nearest integer, cuts tt_max error in half
    if (root < value)
        ++root;
    return root;
}


int oldPhoto(argb* src, argb*&dst, int w, int h)
{
    if (src == NULL || w < 0 || h < 0)
    {
        return 0;
    }
    dst        = (argb*) malloc(sizeof(argb) * w * h);
    for (int y = 1; y <= h - 1; y++)
    {
        for (int x = 1; x < w - 1; x++)
        {

            float B    = (float) src[x + y * w].blue;
            float G    = (float) src[x + y * w].green;
            float R    = (float) src[x + y * w].red;
            float newB = (27.2 * R + 53.4 * G + 13.1 * B) / 100;
            float newG = (34.9 * R + 68.6 * G + 16.8 * B) / 100;
            float newR = (39.3 * R + 76.9 * G + 18.9 * B) / 100;
            newR = checkChannelValue(newR);
            newG = checkChannelValue(newG);
            newB = checkChannelValue(newB);
            dst[x + y * w].red   = newR;
            dst[x + y * w].green = newG;
            dst[x + y * w].blue  = newB;
            dst[x + y * w].alpha = src[x + y * w].alpha;
        }
    }
    return 1;
}


int relief(argb* src, argb*&dst, int w, int h)
{
    if (src == NULL || w < 0 || h < 0)
    {
        return 0;
    }
    dst        = (argb*) malloc(sizeof(argb) * w * h);
    for (int y = 1; y <= h - 1; y++)
    {
        for (int x = 1; x < w - 1; x++)
        {
            float B    = (float) src[x + y * w].blue;
            float G    = (float) src[x + y * w].green;
            float R    = (float) src[x + y * w].red;
            float nB   = (float) src[x + 1 + y * w].blue;
            float nG   = (float) src[x + 1 + y * w].green;
            float nR   = (float) src[x + 1 + y * w].red;
            float newB = (B - nB) * RELIEF_LEVEL + 128;
            float newG = (G - nG) * RELIEF_LEVEL + 128;
            float newR = (R - nR) * RELIEF_LEVEL + 128;
            newR       = checkChannelValue(newR);
            newG       = checkChannelValue(newG);
            newB       = checkChannelValue(newB);
            float value = 255 - ((30 * newR + 59 * newG + 11 * newB) / 100);
            dst[x + y * w].red   = value;
            dst[x + y * w].green = value;
            dst[x + y * w].blue  = value;
            dst[x + y * w].alpha = src[x + y * w].alpha;
        }
    }

    return 1;
}


int lomo(argb* src, argb*&dst, int w, int h, int depth)
{
    int table[256] = {0};
    int maxR;
    dst   = (argb*) malloc(sizeof(argb) * w * h);
    depth = depth < 5 ? 5 : depth;
    depth = depth > 24 ? 24 : depth;
    for (int i = 0; i < 256; i++)
    {
        table[i] = MAX(0, MIN(255, (int) ((((i - 128) * 256) >> 7) + 192)));
    }
    maxR = gnSqrt((w * w + h * h), depth) / 2;
    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            argb argb1 = src[x + y * w];
            int  r     = gnSqrt((x - w >> 1) * (x - w >> 1) + (y - h >> 1) * (y - h >> 1), depth);
            int  c     = 255 - 165 * r / maxR;
            int  temp  = argb1.red * c / 255;
            dst[x + y * w].red = table[temp];
            temp = argb1.green * c / 255;
            dst[x + y * w].green = table[temp];
            temp = argb1.blue * c / 255;
            dst[x + y * w].blue  = table[temp];
            dst[x + y * w].alpha = src[x + y * w].alpha;
        }
    }
    return 1;
}


int negative(argb* src, argb*&dst, int w, int h)
{
    if (src == NULL || w < 0 || h < 0)
    {
        return 0;
    }
    dst        = (argb*) malloc(sizeof(argb) * w * h);
    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            dst[y * w + x] = negativePixelVal(src[y * w + x]);
        }
    }
    return 1;
}


int mmirror(argb* src, argb*&dst, int width, int height)
{
    if (src == NULL || width < 0 || height < 0)
    {
        return 0;
    }
    dst        = (argb*) malloc(sizeof(argb) * width * height);
    for (int y = 0; y <= (height); y++)
    {
        for (int x = 0; x <= (width + 1) / 2; x++)
        {
            int R = src[x + y * width].red;
            int G = src[x + y * width].green;
            int B = src[x + y * width].blue;
            int A = src[x + y * width].alpha;
            dst[x + y * width].red           = R;
            dst[x + y * width].green         = G;
            dst[x + y * width].blue          = B;
            dst[x + y * width].alpha         = A;
            dst[width - x + y * width].red   = R;
            dst[width - x + y * width].green = G;
            dst[width - x + y * width].blue  = B;
            dst[width - x + y * width].alpha = A;
        }
    }
    return 1;
}


int oldPaint(argb* src, argb*&dst, int width, int height, int brushSize, int coarseness)
{
    brushSize    = gnEdge(brushSize, 8);
    coarseness   = coarseness < 1 ? 1 : coarseness;
    coarseness   = coarseness > 255 ? 255 : coarseness;
    int lenArray = coarseness + 1;
    int    * countIntensity = new int[lenArray];
    uint   * redAverage     = new uint[lenArray];
    uint   * greenAverage   = new uint[lenArray];
    uint   * blueAverage    = new uint[lenArray];
    uint8_t* gray           = argb2gray(src, width, height);
    dst = (argb*) malloc(sizeof(argb) * width * height);
    for (int y = 0; y < height; ++y)
    {
        int      top    = gnEdge(y - brushSize, width);
        int      bottom = gnEdge(y + brushSize + 1, height);
        for (int x      = 0; x < width; ++x)
        {
            int left  = gnEdge(x - brushSize, width);
            int right = gnEdge(x + brushSize + 1, width);
            memset(countIntensity, 0, sizeof(int) * lenArray);
            memset(redAverage, 0, sizeof(uint) * lenArray);
            memset(greenAverage, 0, sizeof(uint) * lenArray);
            memset(blueAverage, 0, sizeof(uint) * lenArray);
            for (int i               = top; i < bottom; ++i)
            {
                for (int j = left; j < right; ++j)
                {
                    uint8_t intensity = static_cast<uint8_t>((float) coarseness *
                                                             gray[i * width + j] /
                                                             255.0);
                    countIntensity[intensity]++;
                    redAverage[intensity] += src[i * width + j].red;
                    greenAverage[intensity] += src[i * width + j].green;
                    blueAverage[intensity] += src[i * width + j].blue;
                }
            }
            uint8_t  chosenIntensity = 0;
            int      maxInstance     = countIntensity[0];
            for (int i               = 0; i < lenArray; ++i)
            {
                if (countIntensity[i] > maxInstance)
                {
                    chosenIntensity = i;
                    maxInstance     = countIntensity[i];
                }
            }
            dst[x + y * width].red   = checkChannelValue(redAverage[chosenIntensity] / maxInstance);
            dst[x + y * width].green = checkChannelValue(
                    greenAverage[chosenIntensity] / maxInstance);
            dst[x + y * width].blue  = checkChannelValue(
                    blueAverage[chosenIntensity] / maxInstance);
            dst[x + y * width].alpha = src[x + y * width].alpha;
        }
    }
    delete[]countIntensity;
    delete[]redAverage;
    delete[]greenAverage;
    delete[]blueAverage;
    free(gray);
    return 1;
}