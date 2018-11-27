//
//  Matrix.cpp
//  okk
//
//  From : https://www.cnblogs.com/tianzhenyun/p/4527742.html
//  Created by 凌志 on 2018/11/26.
//  Copyright © 2018 凌志. All rights reserved.
//

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Matrix.h"

namespace gnImage
{


/* 为矩阵分配初始空间 */
    Matrix alloc_matrix(int rows, int cols)
    {
        Matrix m;
        int    i;
        int    j;
        m.rows = rows;
        m.cols = cols;
        m.data = (double**) malloc(sizeof(double*) * m.rows);
        for (i = 0; i < m.rows; ++i)
        {
            m.data[i] = (double*) malloc(sizeof(double) * m.cols);
            assert(m.data[i]);
            for (j = 0; j < m.cols; ++j)
            {
                m.data[i][j] = 0.0;
            }
        }
        return m;
    }


/* 释放空间 */
    void free_matrix(Matrix m)
    {
        int i;
        assert(m.data != NULL);
        for (i = 0; i < m.rows; ++i)
        {
            free(m.data[i]);
        }
        free(m.data);
    }


/* 初始化矩阵 */
    void set_matrix(Matrix m, ...)
    {
        va_list ap;
        int     i, j;
        va_start(ap, m);

        for (i = 0; i < m.rows; ++i)
        {
            for (j = 0; j < m.cols; ++j)
            {
                m.data[i][j] = va_arg(ap, double);
            }
        }

        va_end(ap);
    }


    void set_matrix(Matrix m, int rows, int cols, double value)
    {
//    printf("rows: %d, cols : %d",m.rows,m.cols);
        assert(rows >= 0 && cols >= 0 && rows < m.rows && cols < m.cols);
        m.data[rows][cols] = value;
    }


/* 转换为单元矩阵 */
    void set_identity_matrix(Matrix m)
    {
        int i;
        int j;
        assert(m.rows == m.cols);
        for (i = 0; i < m.rows; ++i)
        {
            for (j = 0; j < m.cols; ++j)
            {
                if (i == j)
                {
                    m.data[i][j] = 1.0;
                } else
                {
                    m.data[i][j] = 0.0;
                }
            }
        }
    }


/* 复制矩阵 */
    void copy_matrix(Matrix source, Matrix destination)
    {
        int i;
        int j;
        assert(source.rows == destination.rows);
        assert(source.cols == destination.cols);
        for (i = 0; i < source.rows; ++i)
        {
            for (j = 0; j < source.cols; ++j)
            {
                destination.data[i][j] = source.data[i][j];
            }
        }
    }


/* 打印矩阵 */
    void print_matrix(Matrix m)
    {
        int i;
        int j;
        for (i = 0; i < m.rows; ++i)
        {
            for (j = 0; j < m.cols; ++j)
            {
                if (j > 0)
                {
                    printf(" ");
                }
                printf("%6.2f", m.data[i][j]);
            }
            printf("\n");
        }
    }


/* 矩阵相加 */
    void add_matrix(Matrix a, Matrix b, Matrix c)
    {
        int i;
        int j;
        assert(a.rows == b.rows);
        assert(a.rows == c.rows);
        assert(a.cols == b.cols);
        assert(a.cols == c.cols);
        for (i = 0; i < a.rows; ++i)
        {
            for (j = 0; j < a.cols; ++j)
            {
                c.data[i][j] = a.data[i][j] + b.data[i][j];
            }
        }
    }


/* 矩阵相减 */
    void subtract_matrix(Matrix a, Matrix b, Matrix c)
    {
        int i;
        int j;
        assert(a.rows == b.rows);
        assert(a.rows == c.rows);
        assert(a.cols == b.cols);
        assert(a.cols == c.cols);
        for (i = 0; i < a.rows; ++i)
        {
            for (j = 0; j < a.cols; ++j)
            {
                c.data[i][j] = a.data[i][j] - b.data[i][j];
            }
        }
    }


    double get_matrix(Matrix m, int rows, int cols)
    {
        assert(rows >= 0 && cols >= 0 && rows < m.rows && cols < m.cols);
        double value = 0.0f;
        value = m.data[rows][cols];
        return value;
    }


/* 用单元矩阵减去该矩阵 */
    void subtract_from_identity_matrix(Matrix a)
    {
        int i;
        int j;
        assert(a.rows == a.cols);
        for (i = 0; i < a.rows; ++i)
        {
            for (j = 0; j < a.cols; ++j)
            {
                if (i == j)
                {
                    a.data[i][j] = 1.0 - a.data[i][j];
                } else
                {
                    a.data[i][j] = 0.0 - a.data[i][j];
                }
            }
        }
    }


/* 矩阵相乘 */
    void multiply_matrix(Matrix a, Matrix b, Matrix c)
    {
        int i;
        int j;
        int k;
        assert(a.cols == b.rows);
        assert(a.rows == c.rows);
        assert(b.cols == c.cols);
        for (i = 0; i < c.rows; ++i)
        {
            for (j = 0; j < c.cols; ++j)
            {
                /* Calculate element c.data[i][j] via a dot product of one row of a
                 with one column of b */
                c.data[i][j] = 0.0;
                for (k = 0; k < a.cols; ++k)
                {
                    c.data[i][j] += a.data[i][k] * b.data[k][j];
                }
            }
        }
    }


/* 乘以一个矩阵的转置矩阵. */
    void multiply_by_transpose_matrix(Matrix a, Matrix b, Matrix c)
    {
        int i;
        int j;
        int k;
        assert(a.cols == b.cols);
        assert(a.rows == c.rows);
        assert(b.rows == c.cols);
        for (i = 0; i < c.rows; ++i)
        {
            for (j = 0; j < c.cols; ++j)
            {
                /* Calculate element c.data[i][j] via a dot product of one row of a
                 with one row of b */
                c.data[i][j] = 0.0;
                for (k = 0; k < a.cols; ++k)
                {
                    c.data[i][j] += a.data[i][k] * b.data[j][k];
                }
            }
        }
    }


/* 矩阵转置 */
    void transpose_matrix(Matrix input, Matrix output)
    {
        int i;
        int j;
        //int k;
        assert(input.rows == output.cols);
        assert(input.cols == output.rows);
        for (i = 0; i < input.rows; ++i)
        {
            for (j = 0; j < input.cols; ++j)
            {
                output.data[j][i] = input.data[i][j];
            }
        }
    }


/* 两矩阵是否相等 */
    int equal_matrix(Matrix a, Matrix b, double tolerance)
    {
        int i;
        int j;
        //int k;
        assert(a.rows == b.rows);
        assert(a.cols == b.cols);
        for (i = 0; i < a.rows; ++i)
        {
            for (j = 0; j < a.cols; ++j)
            {
                if (abs(a.data[i][j] - b.data[i][j]) > tolerance)
                {
                    return 0;
                }
            }
        }
        return 1;
    }


/* 矩阵乘以一个系数 */
    void scale_matrix(Matrix m, double scalar)
    {
        int i;
        int j;

        assert(scalar != 0.0);
        for (i = 0; i < m.rows; ++i)
        {
            for (j = 0; j < m.cols; ++j)
            {
                m.data[i][j] *= scalar;
            }
        }
    }


/* 交换矩阵的两行 */
    void swap_rows(Matrix m, int r1, int r2)
    {
        double* tmp;
        assert(r1 != r2);
        tmp = m.data[r1];
        m.data[r1] = m.data[r2];
        m.data[r2] = tmp;
    }


/* 矩阵某行乘以一个系数 */
    void scale_row(Matrix m, int r, double scalar)
    {
        int i;
        assert(scalar != 0.0);
        for (i = 0; i < m.cols; ++i)
        {
            m.data[r][i] *= scalar;
        }
    }


/* Add scalar * row r2 to row r1. */
    void shear_row(Matrix m, int r1, int r2, double scalar)
    {
        int i;
        assert(r1 != r2);
        for (i = 0; i < m.cols; ++i)
        {
            m.data[r1][i] += scalar * m.data[r2][i];
        }
    }

/* 矩阵的求逆(借鉴他人) */
/* Uses Gauss-Jordan elimination.
 
 The elimination procedure works by applying elementary row
 operations to our input matrix until the input matrix is reduced to
 the identity matrix.
 Simultaneously, we apply the same elementary row operations to a
 separate identity matrix to produce the inverse matrix.
 If this makes no sense, read wikipedia on Gauss-Jordan elimination.
 
 This is not the fastest way to invert matrices, so this is quite
 possibly the bottleneck. */
    int destructive_invert_matrix(Matrix input, Matrix output)
    {
        int    i;
        int    j;
        int    r;
        double scalar;
        double shear_needed;
        assert(input.rows == input.cols);
        assert(input.rows == output.rows);
        assert(input.rows == output.cols);

        set_identity_matrix(output);

        /* Convert input to the identity matrix via elementary row operations.
         The ith pass through this loop turns the element at i,i to a 1
         and turns all other elements in column i to a 0. */

        for (i = 0; i < input.rows; ++i)
        {

            if (input.data[i][i] == 0.0)
            {
                /* We must swap rows to get a nonzero diagonal element. */

                for (r = i + 1; r < input.rows; ++r)
                {
                    if (input.data[r][i] != 0.0)
                    {
                        break;
                    }
                }
                if (r == input.rows)
                {
                    /* Every remaining element in this column is zero, so this
                     matrix cannot be inverted. */
                    return 0;
                }
                swap_rows(input, i, r);
                swap_rows(output, i, r);
            }

            /* Scale this row to ensure a 1 along the diagonal.
             We might need to worry about overflow from a huge scalar here. */
            scalar = 1.0 / input.data[i][i];
            scale_row(input, i, scalar);
            scale_row(output, i, scalar);

            /* Zero out the other elements in this column. */
            for (j = 0; j < input.rows; ++j)
            {
                if (i == j)
                {
                    continue;
                }
                shear_needed = -input.data[j][i];
                shear_row(input, j, i, shear_needed);
                shear_row(output, j, i, shear_needed);
            }
        }

        return 1;
    }


/* 卡尔曼预测 */
    void predict(Matrix* x_priori, Matrix* p_priori, Matrix Z, double timeStep)
    {
        Matrix A;
        Matrix H;
        Matrix Q;
        Matrix R;
        Matrix K;
        Matrix x_posteriori;
        Matrix p_posteriori;
        Matrix temp1;
        Matrix temp2;
        Matrix temp3;
        Matrix temp4;
        Matrix temp5;
        Matrix temp6;
        Matrix temp7;
        Matrix temp8;
        Matrix temp9;
        Matrix temp10;
        Matrix temp11;
        Matrix temp12;
        Matrix temp13;
        Matrix temp14;
        Matrix temp15;
        Matrix temp16;
        A            = gnImage::alloc_matrix(3, 3);
        H            = gnImage::alloc_matrix(2, 3);
        Q            = gnImage::alloc_matrix(3, 3);
        R            = gnImage::alloc_matrix(2, 2);
        K            = gnImage::alloc_matrix(3, 2);
        x_posteriori = gnImage::alloc_matrix(3, 1);
        p_posteriori = gnImage::alloc_matrix(3, 3);

        temp1 = gnImage::alloc_matrix(2, 3);
        temp2 = gnImage::alloc_matrix(3, 2);
        temp3 = gnImage::alloc_matrix(2, 2);
        temp4 = gnImage::alloc_matrix(2, 2);
        temp5 = gnImage::alloc_matrix(2, 2);
        temp6 = gnImage::alloc_matrix(3, 2);

        temp7 = gnImage::alloc_matrix(2, 1);
        temp8 = gnImage::alloc_matrix(2, 1);
        temp9 = gnImage::alloc_matrix(3, 1);

        temp10 = gnImage::alloc_matrix(3, 3);
        temp11 = gnImage::alloc_matrix(3, 3);

        temp12 = gnImage::alloc_matrix(3, 1);

        temp13 = gnImage::alloc_matrix(3, 3);
        temp14 = gnImage::alloc_matrix(3, 3);
        temp15 = gnImage::alloc_matrix(3, 3);

        temp16 = gnImage::alloc_matrix(3, 3);

        gnImage::set_matrix(A,
                            1.0, 0.0, timeStep,
                            0.0, 1.0, 0.0,
                            0.0, 0.0, 1.0);
        gnImage::set_matrix(H,
                            1.0, 0.0, 0.0,
                            0.0, 1.0, 0.0);
        set_matrix(Q,
                   0.001, 0.0, 0.0,
                   0.0, 0.001, 0.0,
                   0.0, 0.0, 0.001);
        set_matrix(R,
                   1.0, 0.0,
                   0.0, 1.0);
        multiply_matrix(H, *p_priori, temp1);
        transpose_matrix(H, temp2);
        multiply_matrix(temp1, temp2, temp3);

        add_matrix(temp3, R, temp4);

        destructive_invert_matrix(temp4, temp5);

        multiply_matrix(*p_priori, temp2, temp6);

        multiply_matrix(temp5, temp6, K);

        multiply_matrix(H, *x_priori, temp7);
        subtract_matrix(Z, temp7, temp8);

        multiply_matrix(K, temp8, temp9);

        add_matrix(*x_priori, temp9, x_posteriori);

        multiply_matrix(K, H, temp10);
        subtract_from_identity_matrix(temp10);
        multiply_matrix(temp10, *p_priori, temp11);

        multiply_matrix(A, x_posteriori, temp12);
        copy_matrix(temp12, *x_priori);

        multiply_matrix(A, p_posteriori, temp13);
        transpose_matrix(A, temp14);
        multiply_matrix(temp13, temp14, temp15);
        add_matrix(temp15, Q, temp16);
        copy_matrix(temp16, *p_priori);
        free_matrix(temp1);
        free_matrix(temp2);
        free_matrix(temp3);
        free_matrix(temp4);
        free_matrix(temp5);
        free_matrix(temp6);
        free_matrix(temp7);
        free_matrix(temp8);
        free_matrix(temp9);
        free_matrix(temp10);
        free_matrix(temp11);
        free_matrix(temp12);
        free_matrix(temp13);
        free_matrix(temp14);
        free_matrix(temp15);
        free_matrix(temp16);

    }


    void matrixSolve(Matrix a, Matrix b, Matrix x)
    {
        Matrix a1 = gnImage::alloc_matrix(a.rows, a.cols);
        gnImage::destructive_invert_matrix(a, a1);
//    print_matrix(a1);
        gnImage::multiply_matrix(a1, b, x);
    }


};
