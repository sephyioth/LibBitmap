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
#ifndef LIBBITMAP_FILTER_H
#define LIBBITMAP_FILTER_H


#include "../GNBitmapContast.h"

/**
 * 老照片
 */
int oldPhoto(argb* src, argb*&dst, int w, int h);

int oldPaint(argb* src, argb*&dst, int w, int h,int brushSize,int coarseness);
/**
 * 雕像
 */
int relief(argb* src, argb*&dst, int w, int h);

int lomo(argb* src, argb*&dst, int w, int h, int depth);

int negative(argb* src, argb*&dst, int w, int h);

int mmirror(argb* src, argb*&dst, int width, int height);


#endif //LIBBITMAP_FILTER_H
