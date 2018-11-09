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

uint8_t* argb2gray(argb* bdata, int width, int height);

uint8_t* transColors(GNBitmap* bitmap);

int convolution(uint8_t* data, double* model, uint8_t* dst, int w, int h, int col, int row);

int average(uint8_t* src1, uint8_t* src2, uint8_t* dst, int w, int h);

#endif //LIBBITMAP_BITMAPUTILLS_H
