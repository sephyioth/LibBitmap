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
#include "WarpPerspective.h"
#include "../BitmapUtills/BitmapUtills.h"


int WarpPerspective::cWarpPerspective(IplImage* src, IplImage*&dst, point2D* points, int length)
{
    if (src == NULL)
    {
        return 0;
    }
    CvPoint2D32f* srcTri;
    CvPoint2D32f* dstTri;
    dstTri = (CvPoint2D32f*) malloc(sizeof(CvPoint2D32f) * length);
    srcTri = (CvPoint2D32f*) malloc(sizeof(CvPoint2D32f) * length);
    CvMat* rot_mat  = cvCreateMat(3, 3, CV_32FC1);
    CvMat* warp_mat = cvCreateMat(3, 3, CV_32FC1);
    dst = cvCloneImage(src);
    dst->origin = src->origin;
    cvSetZero(dst);
    srcTri[0] = cvPoint2D32f(0, 0);
    srcTri[1] = cvPoint2D32f(src->width - 1, 0);
    srcTri[2] = cvPoint2D32f(0, src->height - 1);
    srcTri[3] = cvPoint2D32f(src->width - 1, src->height - 1);
    for (int i = 0; i < length; ++i)
    {
        dstTri[i] = cvPoint2D32f(points[i].x, points[i].y);
    }
    cvGetPerspectiveTransform(srcTri, dstTri, warp_mat);
    cvWarpPerspective(src, dst, warp_mat);
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
    free(srcTri);
    free(dstTri);
    return 1;
}


int
WarpPerspective::nativeWarpPerspective(argb* src, argb*&dst, int width, int height, point2D* points,
                                       int length)
{
    point2D* srcPoints = (point2D*) malloc(4 * sizeof(point2D));
    srcPoints[0].x          = 0;
    srcPoints[0].y          = 0;
    srcPoints[1].x          = width - 1;
    srcPoints[1].y          = 0;
    srcPoints[2].x          = 0;
    srcPoints[2].y          = height - 1;
    srcPoints[3].x          = width - 1;
    srcPoints[3].y          = height - 1;
    gnImage::Matrix* matrix1;
    double         * matrix = nativeGetPerspectiveTransform(srcPoints, points, matrix1);
    nativeWarpPerspective(src, dst, width, height, matrix);
    return 1;
}


int
WarpPerspective::nativeWarpPerspective(argb* src, argb*&dst, int width, int height, Matrix matrix)
{
    double* map = (double*) malloc(sizeof(double) * 9);
    for (int i = 0, n = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++, n++)
        {
            map[i + j * 3] = get_matrix(matrix, n % 8, 0);
        }
    }
    map[8]     = 1.0f;
    nativeWarpPerspective(src, dst, width, height, map);
    free(map);
    return 1;
}


int
WarpPerspective::nativeWarpPerspective(argb* src, argb*&dst, int width, int height, double* matrix)
{
    if (src == NULL || width < 0 || height < 0 || matrix == NULL)
    {
        LOGE("nativeWarpPerspective parames error ");
        return -1;
    }
    dst = (argb*) malloc(sizeof(argb) * width * height);
    memset(dst, 0, sizeof(argb) * width * height);
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            double div   = (matrix[2] * x + matrix[5] * y + matrix[8]);
            double src_x = (matrix[0] * x + matrix[3] * y + matrix[6]) / div;
            double src_y = (matrix[1] * x + matrix[4] * y + matrix[7]) / div;
            int    ux    = gnEdge(src_x, width);
            int    uy    = gnEdge(src_y, height);
            dst[ux + uy * width] = src[x + y * width];
        }
    }
    return 1;
}


/* Calculates coefficients of perspective transformation
 * which maps (xi,yi) to (ui,vi), (i=1,2,3,4):
 *
 *      c00*xi + c01*yi + c02
 * ui = ---------------------
 *      c20*xi + c21*yi + c22
 *
 *      c10*xi + c11*yi + c12
 * vi = ---------------------
 *      c20*xi + c21*yi + c22
 *
 * Coefficients are calculated by solving linear system:
 * / x0 y0  1  0  0  0 -x0*u0 -y0*u0 \ /c00\ /u0\
 * | x1 y1  1  0  0  0 -x1*u1 -y1*u1 | |c01| |u1|
 * | x2 y2  1  0  0  0 -x2*u2 -y2*u2 | |c02| |u2|
 * | x3 y3  1  0  0  0 -x3*u3 -y3*u3 |.|c10|=|u3|,
 * |  0  0  0 x0 y0  1 -x0*v0 -y0*v0 | |c11| |v0|
 * |  0  0  0 x1 y1  1 -x1*v1 -y1*v1 | |c12| |v1|
 * |  0  0  0 x2 y2  1 -x2*v2 -y2*v2 | |c20| |v2|
 * \  0  0  0 x3 y3  1 -x3*v3 -y3*v3 / \c21/ \v3/
 *
 * where:
 *   cij - matrix coefficients, c22 = 1
 * input:
 * 4 point
 */
double* WarpPerspective::nativeGetPerspectiveTransform(point2D* src, point2D* dst, Matrix*&warp_mat)
{
    if (src == NULL)
    {
        LOGE("nativeGetPerspectiveTransform points error SRC");
        return NULL;
    }
    if (dst == NULL)
    {
        LOGE("nativeGetPerspectiveTransform points error dst");
        return NULL;
    }
    double* matrix = (double*) malloc(sizeof(double) * 9);
    double a[8][8] = {0};
    double b[8];
    memset(matrix, 0, sizeof(double) * 9);

#ifdef  GNDEBUG
    cout << "src dex" << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << "(" << src[i].x << " , " << src[i].y << " )";
    }
    cout << "dst dex" << endl;
    for (int i   = 0; i < 4; i++)
    {
        cout << "(" << dst[i].x << " , " << dst[i].y << " )";
    }
#endif
    for (int i   = 0; i < 4; ++i)
    {
        a[i][0]     = a[i + 4][3] = src[i].x;
        a[i][1]     = a[i + 4][4] = src[i].y;
        a[i][2]     = a[i + 4][5] = 1;
        a[i][3]     = a[i][4]     = a[i][5] =
        a[i + 4][0] = a[i + 4][1] = a[i + 4][2] = 0;
        a[i][6]     = -src[i].x * dst[i].x;
        a[i][7]     = -src[i].y * dst[i].x;
        a[i + 4][6] = -src[i].x * dst[i].y;
        a[i + 4][7] = -src[i].y * dst[i].y;
        b[i]        = dst[i].x;
        b[i + 4]    = dst[i].y;
    }
    Matrix   mA  = alloc_matrix(8, 8);
    Matrix   inB = alloc_matrix(8, 1);
    for (int i   = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            set_matrix(mA, j, i, a[j][i]);
        }
    }
    for (int j   = 0; j < 8; j++)
    {
        set_matrix(inB, j, 0, b[j]);
    }
    Matrix   mX  = alloc_matrix(8, 1);
    matrixSolve(mA, inB, mX);
    for (int i = 0, n = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++, n++)
        {
            matrix[i + j * 3] = get_matrix(mX, n % 8, 0);
        }
    }
    matrix[8]  = 1.0f;
    free_matrix(mA);
    free_matrix(inB);
    free_matrix(mX);
#ifdef GNDEBUG
    print_matrix(mX);
#endif
    return matrix;
}
