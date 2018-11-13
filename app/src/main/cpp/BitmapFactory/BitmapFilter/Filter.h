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

int filter(argb* src, argb*&dst, int w, int h);

int relief(argb* src, argb*&dst, int w, int h);

int lomo(argb* src, argb*&dst, int w, int h, int depth);


#endif //LIBBITMAP_FILTER_H
