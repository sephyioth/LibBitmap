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
#ifndef LIBBITMAP_BITMAPUTILLS_H
#define LIBBITMAP_BITMAPUTILLS_H

#include <stdint.h>
#include "../GNBitmapContast.h"
#include "../GNBitmap/GNBitmap.h"

#define ABS(a) ((a)<(0)?(-a):(a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

argb* hsv2argb(hsv* input, int w, int h);

hsv* argb2hsv(argb* input, int w, int h);

uint8_t* rgb5652argb(uint8_t* data, int width, int height);

uint8_t* argb2gray(argb* bdata, int width, int height);

/**
 * 色彩转换
 */
uint8_t* transColorsA8(GNBitmap* bitmap);

/**
 * 卷积
 */
int convolution(uint8_t* data, double* model, uint8_t* dst, int w, int h, int col, int row);

/**两幅图求平均
 */
int average(uint8_t* src1, uint8_t* src2, uint8_t*&dst, int w, int h);

/**
 * 平均值
 */
uint8_t average(uint8_t* data, int blurw, int blurh);

int inRangeS(uint8_t* src, uint8_t*&dst, int w, int h, int upper, int lower);

/**
 * 边角检测
 */
int gnEdge(int x, int w);

/**
 * 检测是否超边界
 */
uint8_t checkChannelValue(float value);

/**
 * 加噪声
 */
int noise(argb* src, argb*&dst, int width, int height, float k1, float k2);

/**
 * 取反
 */
argb negativePixelVal(argb value);


int filterBorder(argb*&src, int width, int height);


bool isInRect(int x, int y, int width, int height);

float diameter(float x, float y, float tox, float toy);

#endif //LIBBITMAP_BITMAPUTILLS_H
