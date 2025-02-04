#include "other.h"
#include "book.h"
#include <iostream>

void sort(char *pcFirst, int nNumber, int size,
          void (*Swap)(void *, void *), int (*Compare)(void *, void *))
{
    int i;
    for (i = 1; i < nNumber; i++)
        for (int j = nNumber - 1; j >= i; j--)
        {
            char *pCurrent = pcFirst + j * size;
            char *pPrevious = pcFirst + (j - 1) * size;
            if ((*Compare)(pPrevious, pCurrent) > 0) // требуется переставить
                (*Swap)(pPrevious, pCurrent);
        }
}

void swap_int(void *p1, void *p2)
{
    int temp = *(int *)p1;
    *(int *)p1 = *(int *)p2;
    *(int *)p2 = temp;
}

int cmp_int(void *p1, void *p2)
{
    int nResult;

    if (*(int *)p1 < *(int *)p2)
        nResult = -1;
    else if (*(int *)p1 > *(int *)p2)
        nResult = 1;
    else
        nResult = 0;

    return nResult;
}

void swap_double(void *p1, void *p2)
{
    double temp = *(double *)p1;
    *(double *)p1 = *(double *)p2;
    *(double *)p2 = temp;
}

int cmp_double(void *p1, void *p2)
{
    if (*(double *)p1 < *(double *)p2)
        return -1;
    else if (*(double *)p1 > *(double *)p2)
        return 1;
    else
        return 0;
}

void swap_str(void *p1, void *p2)
{
    const char *temp = *(const char **)p1;
    *(const char **)p1 = *(const char **)p2;
    *(const char **)p2 = temp;
}

int cmp_str(void *p1, void *p2)
{
    return strcmp(*(const char **)p1, *(const char **)p2);
}

double add(double first, double second)
{
    return first + second;
}
double sub(double first, double second)
{
    return first - second;
}
double mul(double first, double second)
{
    return first * second;
}
double div(double first, double second)
{
    if (second == 0)
    {
        printf("Деление на 0 невозможно! \n");
        return NAN;
    }
    return first / second;
}

void print_math_operations()
{
    printf("1) <+> - сложение \n");
    printf("2) <-> - вычитание \n");
    printf("3) <*> - умножение \n");
    printf("4) </> - деление \n");
    printf("5) <^> - возведение в степень \n");
    printf("6) <q> - выход из калькулятора\n");
}

void print_max(double *arr, int size)
{
    double max = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (max < arr[i])
            max = arr[i];
    }
    printf("Наибольший элемент массива: %lf\n", max);
}
void print_min(double *arr, int size)
{
    double min = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (min > arr[i])
            min = arr[i];
    }
    printf("Наименьший элемент массива: %lf\n", min);
}
void sort_asc(double *arr, int size)
{
    printf("Исходный массив double:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%lf ", arr[i]);
    }
    printf("\n");

    for (int i = 0; i < size - 1; i++)
    {
        bool wasSorted = false;
        for (int j = 1; j < size - i; j++)
        {
            if (arr[j] < arr[j - 1])
            {
                double temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
                wasSorted = true;
            }
        }
        if (wasSorted == false)
            break;
    }

    printf("Отсортированный по возрастанию массив double:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%lf ", arr[i]);
    }
    printf("\n");
}
void sort_desc(double *arr, int size)
{
    printf("Исходный массив double:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%lf ", arr[i]);
    }
    printf("\n");

    for (int i = 0; i < size - 1; i++)
    {
        bool wasSorted = false;
        for (int j = 1; j < size - i; j++)
        {
            if (arr[j] > arr[j - 1])
            {
                double temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
                wasSorted = true;
            }
        }
        if (wasSorted == false)
            break;
    }

    printf("Отсортированный по убыванию массив double:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%lf ", arr[i]);
    }
    printf("\n");
}

double integrate(double (*function)(double), double a, double b, int n)
{
    double result = 0;

    double h = (b - a) / n;
    for (int i = 0; i < n; i++)
    {
        result += function(a + h / 2 + i * h);
    }
    result *= h;
    return result;
}

double square_function(double x)
{
    return x * x;
}
double sin_function(double x)
{
    return std::sin(x);
}
double exp_function(double x)
{
    return std::exp(x);
}
double linear_function(double x)
{
    return 3 * x + 8;
}