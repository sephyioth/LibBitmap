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

double* getPerspectiveTransform(point2D* srcTri, point2D* dstTri, Matrix*&warp_mat);

int warpPerspective(argb* src, argb* dst, Matrix* matrix);

#endif //LIBBITMAP_PERSPECTIVETRANSFORM_H
