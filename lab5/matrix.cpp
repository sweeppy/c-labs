#include<iostream>
#include<matrix.h>

void m_zero(Matrix *A, int m, int n)
{
    m_free(A);
    A->width = m;
    A->height = n;
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
    if (A->matrix != nullptr)
    {
        for (int i = 0; i < n; i++)
        {
            delete[] A->matrix[i];
        }
        delete[] A->matrix;
    }

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
        for (int i = 0; i < A->width; i++)
        {
            delete[] A->matrix[i];
        }
        delete[] A->matrix;
    }
}
void m_copy(const Matrix *src, Matrix *dst);
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