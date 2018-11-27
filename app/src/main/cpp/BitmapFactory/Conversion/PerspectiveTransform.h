//
// Created by 凌志 on 2018/11/15.
//
/**   
*    
* 项目名称：LibBitmap      
* 类描述：   
* 创建人：genesis   
* 创建时间：2018/11/15 4:49 PM   
* 修改人：genesis  
* 修改时间：2018/11/15 4:49 PM   
* 修改备注：   
* @version    
*    
*/
#ifndef LIBBITMAP_PERSPECTIVETRANSFORM_H
#define LIBBITMAP_PERSPECTIVETRANSFORM_H

#include "../GNBitmapContast.h"
#include "../BitmapUtills/Matrix.h"

using namespace gnImage;

double* nativeGetPerspectiveTransform(point2D* src, point2D* dst, Matrix*&warp_mat);

int nativeWarpPerspective(argb* src, argb* dst, Matrix* matrix);

#endif //LIBBITMAP_PERSPECTIVETRANSFORM_H
