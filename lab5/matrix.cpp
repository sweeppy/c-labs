#include <iostream>
#include "matrix.h"

void m_zero(Matrix *A, int m, int n)
{
    m_free(A);
    A->width = n;
    A->height = m;
    A->matrix = new double *[m];
    for (int i = 0; i < m; i++)
    {
        A->matrix[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            A->matrix[i][j] = 0;
        }
    }
}

void m_id(Matrix *A, int n)
{
    m_free(A);

    A->matrix = new double*[n];
    for (int i = 0; i < n; i++)
    {
        A->matrix[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                A->matrix[i][j] = 1;
            else
                A->matrix[i][j] = 0;
        }
    }
}

void m_free(Matrix *A)
{
    if (A->matrix != nullptr)
    {
        for (int i = 0; i < A->height; i++)
        {
            delete[] A->matrix[i];
        }
        delete[] A->matrix;
        A->matrix = nullptr;
        A->width = 0;
        A->height = 0;
    }
}

void m_copy(const Matrix *src, Matrix *dst)
{
    for (int i = 0; i < src->height; i++)
    {
        for (int j = 0; j < src->width; j++)
        {
            dst->matrix[i][j] = src->matrix[i][j];
        }
    }
}

int m_width(const Matrix *A)
{
    return A->width;
}

int m_height(const Matrix *A)
{
    return A->height;
}

double m_get(const Matrix *A, int i, int j)
{
    return A->matrix[i][j];
}

void m_set(Matrix *A, int i, int j, double value)
{
    A->matrix[i][j] = value;
}

int m_add(Matrix *A, const Matrix *B)
{
    if (A->height != B->height || A->width != B->width)
        return 1;

    for (int i = 0; i < A->height; i++)
    {
        for (int j = 0; j < A->width; j++)
        {
            A->matrix[i][j] += B->matrix[i][j];
        }
    }
        return 0;
}

void m_neg(Matrix *A)
{
    for (int i = 0; i < A->height; i++)
    {
        for (int j = 0; j < A->width; j++)
        {
            A->matrix[i][j] = -A->matrix[i][j];
        }
    }
}

int m_mult(const Matrix *A, const Matrix *B, Matrix *dst)
{
    // Матрицы не могут умножиться из-за их размерности
    if (A->width != B->height)
        return 1;
    // Конечная матрица неверного размера
    if (dst->height != A->height || dst->width != B->width)
        return 1;

    for (int i = 0; i < dst->height; i++)
    {
        for (int j = 0; j < dst->width; j++)
        {
            dst->matrix[i][j] = 0;
            for (int k = 0; k < A->width; k++)
            {
                dst->matrix[i][j] += (A->matrix[i][k] * B->matrix[k][j]);
            }
        }
    }
    return 0;
}

// ДЛЯ ДОПОЛНИТЕЛЬНОГО ЗАДАНИЯ

void m_hill_mult(const Matrix *A, const Matrix *B, Matrix *dst)
{
    for (int i = 0; i < dst->height; i++)
    {
        for (int j = 0; j < dst->width; j++)
        {
            dst->matrix[i][j] = 0;
            for (int k = 0; k < A->width; k++)
            {
                dst->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
            int module = int(dst->matrix[i][j]) % 29; // Берем по модулу от 29(кол-во символов)
            dst->matrix[i][j] = double(module);
        }
    }
}
