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
#include "ConversionTransForm.h"
#include "WarpPerspective.h"


int cvnAffineTransfrom(IplImage* src, IplImage*&dst, point2D* points, int length)
{
    AffineTrans affineTrans;
    affineTrans.cAffineTrans(src, dst, points, length);
    return 1;
}


int cvnWarpPerspective(IplImage* src, IplImage* &dst, point2D* points, int length)
{
    WarpPerspective warpPerspective1;
    warpPerspective1.cWarpPerspective(src, dst, points, length);
    return 1;
}