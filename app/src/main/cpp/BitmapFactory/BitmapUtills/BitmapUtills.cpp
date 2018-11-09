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
#include "math.h"
#include "BitmapUtills.h"
#include "../GNBitmapContast.h"


argb* hsv2argb(hsv* input, int w, int h)
{
    int size = w * h;
    argb* output = (argb*) malloc(sizeof(argb) * size);
    float    R, G, B;
    int      k;
    float    aa, bb, cc, f;
    for (int i   = 0; i < size; ++i)
    {

        if (input[i].S <= 0.0)
            R = G = B = input[i].V;
        else
        {
            if (input[i].H == 1.0)
                input[i].H = 0.0;
            input[i].H *= 6.0;
            k  = floor(input[i].H);
            f  = input[i].H - k;
            aa = input[i].V * (1.0 - input[i].S);
            bb = input[i].V * (1.0 - input[i].S * f);
            cc = input[i].V * (1.0 - (input[i].S * (1.0 - f)));
            switch (k)
            {
                case 0:
                    R = input[i].V;
                    G = cc;
                    B = aa;
                    break;
                case 1:
                    R = bb;
                    G = input[i].V;
                    B = aa;
                    break;
                case 2:
                    R = aa;
                    G = input[i].V;
                    B = cc;
                    break;
                case 3:
                    R = aa;
                    G = bb;
                    B = input[i].V;
                    break;
                case 4:
                    R = cc;
                    G = aa;
                    B = input[i].V;
                    break;
                case 5:
                    R = input[i].V;
                    G = aa;
                    B = bb;
                    break;
            }
        }
        output[i].red   = R * 255;
        output[i].green = G * 255;
        output[i].blue  = B * 255;
    }
    return output;
}


hsv* argb2hsv(argb* input, int w, int h)
{
    if (input == NULL || w < 0 || h < 0)
    {
        return NULL;
    }
    int size = w * h;
    hsv* output = (hsv*) malloc(sizeof(hsv) * size);
    float r, g, b, minRGB, maxRGB, deltaRGB;
    float temp[3];

    for (int i = 0; i < size; ++i)
    {

        r = input[i].red / 255.0f;
        g = input[i].green / 255.0f;
        b = input[i].blue / 255.0f;

        minRGB   = MIN(r, MIN(g, b));
        maxRGB   = MAX(r, MAX(g, b));
        deltaRGB = maxRGB - minRGB;

        output[i].V     = maxRGB;
        if (maxRGB != 0.0)
            output[i].S = deltaRGB / maxRGB;
        else
            output[i].S = 0.0;
        if (output[i].S <= 0.0)
        {
            output[i].H = -1.0f;
        } else
        {
            if (r == maxRGB)
            {
                output[i].H = (g - b) / deltaRGB;
            } else
            {
                if (g == maxRGB)
                {
                    output[i].H = 2.0 + (b - r) / deltaRGB;
                } else
                {
                    if (b == maxRGB)
                    {
                        output[i].H = 4.0 + (r - g) / deltaRGB;
                    }
                }
            }
            output[i].H = output[i].H * 60.0;
            if (output[i].H < 0.0)
            {
                output[i].H += 360;
            }
            output[i].H /= 360;
        }
    }
    return output;
}


uint8_t* argb2gray(argb* bdata, int width, int height)
{
    if (bdata == NULL || width < 0 || height < 0)
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


uint8_t* rgb5652argb(uint8_t* data, int width, int height)
{
    if (data == NULL || width < 0 || height < 0)
    {
        return NULL;
    }
    argb* dst = (argb*) malloc(sizeof(uint8_t) * width * height);
    int size = width * height;

    for (int i = 0; i < size - 1; i += 2)
    {
        int value = ((int) data[i] << 8) & 0xff00 + data[i + 1] & 0xff;
        dst[i].red   = value >> 11 & 0x1f;
        dst[i].green = value >> 5 & 0x3F;
        dst[i].blue  = value >> 0 & 0x1f;
        dst[i].alpha = 0xff;
    }
    return reinterpret_cast<uint8_t*>(dst);
}


uint8_t* transColors(GNBitmap* bitmap)
{
    if (bitmap == NULL)
    {
        return NULL;
    }
    uint8_t* data;
    if (bitmap->type == ANDROID_BITMAP_FORMAT_RGBA_8888)
    {
        data = argb2gray((argb*) bitmap->bitmapData, bitmap->width, bitmap->height);
    } else if (bitmap->type == ANDROID_BITMAP_FORMAT_A_8)
    {
        data = (uint8_t*) bitmap->bitmapData;
    } else if (bitmap->type == ANDROID_BITMAP_FORMAT_RGB_565)
    {

    } else if (bitmap->type == ANDROID_BITMAP_FORMAT_RGBA_4444)
    {

    }
    return data;
}


int convolution(uint8_t* data, double* model, uint8_t* dst, int w, int h, int col, int row)
{
    if (data == NULL || model == NULL || dst == NULL || w < 0 || h < 0 || col < 0 || row < 0)
    {
        return -1;
    }
    for (int i = 0; i < h; ++i)
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

