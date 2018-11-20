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
#include "AffineTransform.h"


int AffineTrans::cAffineTrans(IplImage* src, IplImage*&dst, point2D* points, int length)
{
    if (src == NULL)
    {
        return 0;
    }
    CvPoint2D32f* srcTri;
    CvPoint2D32f* dstTri;
    dstTri = (CvPoint2D32f*) malloc(sizeof(CvPoint2D32f) * length);
    srcTri = (CvPoint2D32f*) malloc(sizeof(CvPoint2D32f) * length);
    CvMat* rot_mat  = cvCreateMat(2, 3, CV_32FC1);
    CvMat* warp_mat = cvCreateMat(2, 3, CV_32FC1);
    dst = cvCloneImage(src);
    dst->origin = src->origin;
    cvSetZero(dst);
    srcTri[0] = cvPoint2D32f(0, 0);
    srcTri[1] = cvPoint2D32f(src->width - 1, 0);
    srcTri[2] = cvPoint2D32f(0, src->height - 1);
    for (int i = 0; i < length; ++i)
    {
        dstTri[i] = cvPoint2D32f(points[i].x, points[i].y);
    }
    cvGetAffineTransform(srcTri, dstTri, warp_mat);
    cvWarpAffine(src, dst, warp_mat);

    free(warp_mat);
    free(srcTri);
    free(dstTri);
#ifdef  DEBUG
    CvFont font;
    cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 0.5, 0.5, 1, 2, 8);
    CvPoint pt = CvPoint(x1,y1);
    cvPutText(dst, " 1", cvPoint(x1-20, y1-20),&font, CV_RGB(0xff, 0x00, 0x00));
    cvCircle(dst, pt,10, CV_RGB(0xff, 0x00, 0x00));

    pt = CvPoint(x2,y2);
    cvPutText(dst, "point 2", cvPoint(x2, y2),&font, CV_RGB(0xff, 0x00, 0x00));
    cvCircle(dst, pt,10, CV_RGB(0xff, 0x00, 0x00));

    pt = CvPoint(x3,y3);
    cvPutText(dst, "point 3", cvPoint(x3, y3), &font, CV_RGB(0xff, 0x00, 0x00));
    cvCircle(dst, pt,10, CV_RGB(0xff, 0x00, 0x00));
#endif
    return 1;
}