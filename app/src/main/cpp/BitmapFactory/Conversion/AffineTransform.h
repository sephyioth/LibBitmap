//
// Created by 凌志 on 2018/11/15.
//
/**   
*    
* 项目名称：LibBitmap      
* 类描述：   
* 创建人：genesis   
* 创建时间：2018/11/15 4:48 PM   
* 修改人：genesis  
* 修改时间：2018/11/15 4:48 PM   
* 修改备注：   
* @version    
*    
*/
#ifndef LIBBITMAP_AFFINETRANSFORM_H
#define LIBBITMAP_AFFINETRANSFORM_H

#include "../GNBitmapContast.h"

class AffineTrans
{
public:
    int cAffineTrans(IplImage* src, IplImage*& dst, point2D* points, int length);

};


#endif //LIBBITMAP_AFFINETRANSFORM_H
