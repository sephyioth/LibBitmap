//
//  Matrix.hpp
//  okk
//
//  From : https://www.cnblogs.com/tianzhenyun/p/4527742.html
//  Created by 凌志 on 2018/11/26.
//  Copyright © 2018 凌志. All rights reserved.
//

#ifndef LIBBITMAP_MATRIX_H
#define LIBBITMAP_MATRIX_H

#include <stdio.h>

namespace gnImage
{

    typedef struct
    {
        /* 维度 */
        int rows;
        int cols;
        /* 内容 */
        double** data;
    } Matrix;

    void matrixSolve(Matrix a, Matrix b, Matrix x);

    Matrix alloc_matrix(int rows, int cols);

    void free_matrix(Matrix m);

    void set_matrix(Matrix m, ...);

    void set_matrix(Matrix m, int rows, int cols, double value);

    double get_matrix(Matrix m, int rows, int cols);

    void print_matrix(Matrix m);

/* 转换为单元矩阵 */
    void set_identity_matrix(Matrix m);

/* 复制矩阵 */
    void copy_matrix(Matrix source, Matrix destination);

/* 矩阵相加 */
    void add_matrix(Matrix a, Matrix b, Matrix c);

/* 矩阵相减 */
    void subtract_matrix(Matrix a, Matrix b, Matrix c);

/* 用单元矩阵减去该矩阵 */
    void subtract_from_identity_matrix(Matrix a);

/* 矩阵相乘 */
    void multiply_matrix(Matrix a, Matrix b, Matrix c);

/* 乘以一个矩阵的转置矩阵. */
    void multiply_by_transpose_matrix(Matrix a, Matrix b, Matrix c);

/* 矩阵转置 */
    void transpose_matrix(Matrix input, Matrix output);

/* 两矩阵是否相等 */
    int equal_matrix(Matrix a, Matrix b, double tolerance);

/* 矩阵乘以一个系数 */
    void scale_matrix(Matrix m, double scalar);

/* 交换矩阵的两行 */
    void swap_rows(Matrix m, int r1, int r2);

/* 矩阵某行乘以一个系数 */
    void scale_row(Matrix m, int r, double scalar);

/* Add scalar * row r2 to row r1. */
    void shear_row(Matrix m, int r1, int r2, double scalar);
/* 矩阵的求逆 */
/* Uses Gauss-Jordan elimination.
 
 The elimination procedure works by applying elementary row
 operations to our input matrix until the input matrix is reduced to
 the identity matrix.
 Simultaneously, we apply the same elementary row operations to a
 separate identity matrix to produce the inverse matrix.
 If this makes no sense, read wikipedia on Gauss-Jordan elimination.
 
 This is not the fastest way to invert matrices, so this is quite
 possibly the bottleneck. */
    int destructive_invert_matrix(Matrix input, Matrix output);

    /* 卡尔曼预测 */
    void predict(Matrix* x_priori, Matrix* p_priori, Matrix Z, double timeStep);
}

#endif /* Matrix_hpp */
