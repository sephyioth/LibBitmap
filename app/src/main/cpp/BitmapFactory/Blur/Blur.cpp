//
// Created by 凌志 on 2018/11/9.
//
/**   
*    
* 项目名称：LibBitmap      
* 类描述：   
* 创建人：genesis   
* 创建时间：2018/11/9 3:09 PM   
* 修改人：genesis  
* 修改时间：2018/11/9 3:09 PM   
* 修改备注：   
* @version    
*    
*/
#include <cmath>
#include <cstdlib>
#include "Blur.h"
#include "../GNBitmapContast.h"


double* buildGaussKern2D(double sigma)
{
    //确保sigma为正数
    sigma = sigma > 0 ? sigma : 0;
    //高斯核矩阵的大小为(6*sigma+1)*(6*sigma+1)
    //ksize为奇数
    int ksize = round(sigma * 3) * 2 + 1;
    if (ksize == 1)
    {
        return NULL;
    }
    //计算高斯核矩阵
    double* kernel = new double[ksize * ksize];
    double   scale = -0.5 / (sigma * sigma);
    double   cons  = -scale / PI;
    double   sum   = 0;
    for (int i     = 0; i < ksize; i++)
    {
        for (int j = 0; j < ksize; j++)
        {
            int x = i - (ksize - 1) / 2;
            int y = j - (ksize - 1) / 2;
            kernel[i * ksize + j] = cons * exp(scale * (x * x + y * y));
            sum += kernel[i * ksize + j];
        }
    }
    //归一化
    for (int i     = ksize * ksize - 1; i >= 0; i--)
    {
        *(kernel + i) /= sum;
    }
    return kernel;
}


double* buildGaussKern1d(long radius)
{
    radius = radius > 0 ? radius : 0;
    int ksize = round(radius * 3) * 2 + 1;
    if (ksize == 1)
    {
        return NULL;
    }
    //计算高斯核矩阵
    double* kernel = new double[ksize * ksize];
    static const double SQRT2PI = sqrt(2.0 * PI);
    double              sigma   = (double) radius / 3.0;
    double              sigma2  = 2.0 * sigma * sigma;
    double              sigmap  = sigma * SQRT2PI;
    double              sum     = 0;
    for (long           n       = 0, i = -radius; i <= radius; ++i, ++n)
    {
        kernel[n] = exp(-(double) (i * i) / sigma2) / sigmap;
        sum += kernel[n];
    }
    for (long           n       = 0, i = -radius; i <= radius; ++i, ++n)
    {
        kernel[n] /= sum;
    }
    return kernel;
}


void gaussblur2d(argb* pix, int w, int h, int radius, uint8_t* mask)
{
    if (pix == NULL || w < 0 || h < 0 || radius < 0)
    {
        return;
    }
    double* kernel = buildGaussKern1d(radius);
    argb  * outW   = (argb*) malloc(sizeof(argb) * w * h);
    argb  * outH   = (argb*) malloc(sizeof(argb) * w * h);
    memset(outW, 0, sizeof(argb) * w * h);
    memset(outH, 0, sizeof(argb) * w * h);
    int    kradius = radius;
    double sumR    = 0, sumG = 0, sumB = 0;

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            sumB = sumG = sumR = 0;
            if (y == 0 || y == h - 1)
            {
                continue;
            } else if (x == 0 || x == w - 1)
            {
                continue;
            }
            for (long n = 0, i = -kradius; i <= kradius; ++i, ++n)
            {
                long i_k = x + i < w ? x + i : w;
                i_k = x + i > 0 ? x + i : 0;
                int inx_k = i_k + y * w;
                sumR += pix[inx_k].red * kernel[n];
                sumG += pix[inx_k].green * kernel[n];
                sumB += pix[inx_k].blue * kernel[n];
            }
            sumR        = (uint8_t) sumR > 0xff ? 0xff : sumR;
            sumG        = (uint8_t) sumG > 0xff ? 0xff : sumG;
            sumB        = (uint8_t) sumB > 0xff ? 0xff : sumB;
            argb argb1;
            argb1.blue  = sumB;
            argb1.red   = sumR;
            argb1.green = sumG;
            argb1.alpha = pix[x + y * w].alpha;
            outW[x + y * w] = argb1;
        }
    }
    for (int x = 0; x < w; ++x)
    {
        for (int y = 0; y < h; ++y)
        {
            if (y == 0 || y == h - 1)
            {
                continue;
            }
            if (x == 0 || x == w - 1)
            {
                continue;
            }
            sumB = sumG = sumR = 0;
            for (long n = 0, i = -kradius; i <= kradius; ++i, ++n)
            {
                long i_k = y + i < h ? y + i : h;
                i_k      = y + i > 0 ? y + i : 0;
                long inx_k = x + i_k * w;
                sumR += pix[inx_k].red * kernel[n];
                sumG += pix[inx_k].green * kernel[n];
                sumB += pix[inx_k].blue * kernel[n];
            }
            sumR        = (uint8_t) sumR > 0xff ? 0xff : sumR;
            sumG        = (uint8_t) sumG > 0xff ? 0xff : sumG;
            sumB        = (uint8_t) sumB > 0xff ? 0xff : sumB;
            argb argb1 = outW[x + y * w];
            argb1.blue  = (sumB + argb1.blue) / 2;
            argb1.red   = (sumR + argb1.red) / 2;
            argb1.green = (sumG + argb1.green) / 2;
            argb1.alpha = pix[x + y * w].alpha;
            outH[x + y * w] = argb1;
        }
    }
    for (int i = 1; i < h - 1; ++i)
    {
        for (int j = 1; j < w - 1; ++j)
        {
            if (mask != NULL)
            {
                if (mask[i * w + j] == 0x00)
                {
                    pix[j + i * w].red=pix[j + i * w].red*0.8f;
                    pix[j + i * w].green=pix[j + i * w].green*0.8f;
                    pix[j + i * w].blue=pix[j + i * w].blue*0.8f;
                    continue;
                }
            }
            pix[j + i * w] = outH[j + i * w];
        }
    }
    delete (outW);
    delete (outH);
}


void gaussBlurSouce(argb* pix, int w, int h, int radius, uint8_t* mask)
{
    if (pix == NULL || w < 0 || h < 0 || radius < 0)
    {
        return;
    }
    int ksize = round(radius * 3) * 2 + 1;
    double* kernel = buildGaussKern2D(radius);
    double sumR = 0, sumG = 0, sumB = 0;
    argb* out = (argb*) malloc(sizeof(argb) * w * h);
    int      kradius = ksize / 2;
    for (int y       = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            sumR = sumG = sumB = 0;
            if (y == 0 || y == h - 1)
            {
                sumR = sumG = sumB = 0;
            } else if (x == 0 || x == w - 1)
            {
                sumR = sumG = sumB = 0;
            } else
            {
                for (int i = -kradius; i < kradius; ++i)
                {
                    long i_k = y + i < h ? y + i : h;
                    i_k = y + i > 0 ? y + i : 0;
                    for (int j = -kradius; j < kradius; ++j)
                    {
                        long j_k = x + i < w ? x + i : w;
                        j_k      = x + i > 0 ? x + i : 0;
                        long inx_k  = i_k * w + j_k;
                        int  valueR = (pix[inx_k]).red;
                        int  valueG = (pix[inx_k]).green;
                        int  valueB = (pix[inx_k]).blue;
                        sumR += kernel[(i + kradius) * kradius + j + kradius] * valueR;
                        sumG += kernel[(i + kradius) * kradius + j + kradius] * valueG;
                        sumB += kernel[(i + kradius) * kradius + j + kradius] * valueB;
                    }
                }
                sumR       = (int) abs(sumR);
                sumG       = (int) abs(sumG);
                sumB       = (int) abs(sumB);
            }
            sumR = (uint8_t) sumR > 0xff ? 0xff : sumR;
            sumG = (uint8_t) sumG > 0xff ? 0xff : sumG;
            sumB = (uint8_t) sumB > 0xff ? 0xff : sumB;
            argb argb1;
            argb1.blue  = sumB;
            argb1.red   = sumR;
            argb1.green = sumG;
            argb1.alpha = pix[x + y * w].alpha;
            out[x + y * w] = argb1;
        }
    }
    for (int i       = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            if (mask != NULL)
            {
                if (mask[i * w + j] != 0x00)
                {
                    continue;
                }
            }
            pix[j + i * w] = out[j + i * w];
        }
    }
    free(out);
}
