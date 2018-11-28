//
// Created by 凌志 on 2018/11/8.
//
/**   
*    
* 项目名称：LibBitmap      
* 类描述：   
* 创建人：genesis   
* 创建时间：2018/11/8 5:53 PM   
* 修改人：genesis  
* 修改时间：2018/11/8 5:53 PM   
* 修改备注：   
* @version    
*    
*/
#ifndef LIBBITMAP_GNCORE_H
#define LIBBITMAP_GNCORE_H

#include "GNBitmap/GNBitmap.h"
#include "GNBitmapContast.h"

int gnDealEdge(GNBitmap* bitmap, int type);

int gnGaussBlur(GNBitmap* gbitmap1, GNBitmap* gbitmap2, int radium, int type);

int gnMedianBlur(GNBitmap* src, GNBitmap* mask, jint blurw, jint blurh, jint btype);

int gnFilter(GNBitmap* src, int* parames, int size);

int gnNoise(GNBitmap* src, float k1, float k2);

int gncvAffineTransfrom(GNBitmap* src, IplImage*&dst, point2D* points, int length);

int gncvWarpPerspective(GNBitmap* src, IplImage*&dst, point2D* points, int length);

int gnnativeWarpPerspective(GNBitmap* src, point2D* points, int length);


#endif //LIBBITMAP_GNCORE_H
