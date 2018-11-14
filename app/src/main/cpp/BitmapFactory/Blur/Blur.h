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
#ifndef LIBBITMAP_BLUR_H
#define LIBBITMAP_BLUR_H

#include "../GNBitmapContast.h"
#include "../GNBitmap/GNBitmap.h"

int* buildGaussKern2D(int winSize, int sigma);

double* buildGaussKern1d(long radius);

void gaussBlur2d(argb* pix, argb*&dst, int w, int h, int radius, uint8_t* mask);

void gaussBlurSouce(argb* pix, argb*&dst, int w, int h, int radius, uint8_t* mask);

void gaussBlur(argb* pix, argb*&dst, int w, int h, int radium, int type, uint8_t* mask);

uint8_t median(uint8_t* data, int blurw, int blurh);

int
gnMedianBlur(argb* pix, argb*&dst, int w, int h, int blurw, int blurh, int btype, uint8_t* mask);

void gnMedianBlur1(argb* pix, argb*&dst, int w, int h, jint blurw, jint blurh, uint8_t* mask);

void gnMedianBlurAverage(argb* pix, argb*&dst, int w, int h, jint blurw, jint blurh, uint8_t* mask);

int stackBlur(argb* pix, argb*&dst, int w, int h, int radius, uint8_t* mask);


#endif //LIBBITMAP_BLUR_H
