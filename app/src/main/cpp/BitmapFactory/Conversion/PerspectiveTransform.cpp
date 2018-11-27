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
#include "PerspectiveTransform.h"
#include "iostream"

using namespace std;


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
double* nativeGetPerspectiveTransform(point2D* src, point2D* dst, Matrix*&warp_mat)
{
    assert(src == NULL || dst == NULL);
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
#ifdef GNDEBUG
    print_matrix(mX);
#endif
    return matrix;
}


int nativeWarpPerspective(argb* src, argb* dst, Matrix* matrix)
{
    return 1;
}