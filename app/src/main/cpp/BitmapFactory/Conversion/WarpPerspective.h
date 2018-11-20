//
// Created by 凌志 on 2018/11/20.
//
/**   
*    
* 项目名称：LibBitmap      
* 类描述：   
* 创建人：genesis   
* 创建时间：2018/11/20 1:52 PM   
* 修改人：genesis  
* 修改时间：2018/11/20 1:52 PM   
* 修改备注：   
* @version    
*    
*/
#ifndef LIBBITMAP_WARPPERSPECTIVE_H
#define LIBBITMAP_WARPPERSPECTIVE_H

#include "../GNBitmapContast.h"

class WarpPerspective
{

public:
    int cWarpPerspective(IplImage* src, IplImage*& dst, point2D* points, int length);

};


#endif //LIBBITMAP_WARPPERSPECTIVE_H
