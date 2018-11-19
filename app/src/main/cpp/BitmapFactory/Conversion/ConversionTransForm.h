//
// Created by 凌志 on 2018/11/15.
//
/**   
*    
* 项目名称：LibBitmap      
* 类描述：   
* 创建人：genesis   
* 创建时间：2018/11/15 4:44 PM   
* 修改人：genesis  
* 修改时间：2018/11/15 4:44 PM   
* 修改备注：   
* @version    
*    
*/
#ifndef LIBBITMAP_CONVERSIONTRANSFORM_H
#define LIBBITMAP_CONVERSIONTRANSFORM_H


#include "../GNBitmapContast.h"

int affineTransfrom(argb* src, argb* dst, int width, int height, point2D* points, int length);

int warpPerspective(argb* src, argb* dst, int width, int height, point2D* points, int length);

#endif //LIBBITMAP_CONVERSIONTRANSFORM_H
