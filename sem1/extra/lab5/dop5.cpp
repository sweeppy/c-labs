//TODO 
/*
    шифр транспонирования
*/

#include <iostream>
#include "matrix.h"

using std::cin, std::cout, std::endl;

const char abc[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ .?";

// Функция получение номера сивола (для будующего заполнения вектор-матрицы)
double get_sym_number(char c)
{
    for (int i = 0; i < 30; i++)
    {
        if(c == abc[i])
            return double(i);
    }
}

// Заполняет массив из строк по 3 символа значениями
void devide_str_by_3(const char* src, int substrCount, char **dst)
{
    for (int i = 0; i < substrCount; i++)
    {
        strncpy(dst[i], src + i * 3, 3);
        dst[i][3] = '\0';
    }
}

// Инициализация матриц размером 3x1
void initialize_vectors_3_by_1(Matrix *vectors, int size)
{
    for (int i = 0; i < size; i++)
    {
        m_zero(&vectors[i], 3, 1);
    }
}

// Заполнение матриц размером 3x1 цифрами, которые соответствуют индексу алфавита
void fill_vectors(Matrix *matrices, char **substrings, int m_count)
{
    for (int i = 0; i < m_count; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrices[i].matrix[j][0] = get_sym_number(toupper(substrings[i][j]));
            // cout << "Ok" << " | " << get_sym_number(substrings[i][j]) << endl;
        }
    }
}

// Вывод матриц в буквах
void print_vectors(const Matrix *vectros, int count)
{
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%c", abc[int(vectros[i].matrix[j][0])]);
            // cout << int(vectros[i].matrix[0][j]) << endl;
        }
    }
}
// * Для дебага
// void print_matrix(Matrix* matrix)
// {
//     if (!matrix || !matrix->matrix) 
//     {
//         std::cerr << "Matrix is not initialized.\n";
//         return;
//     }

//     for (int i = 0; i < matrix->height; i++)
//     {
//         for (int j = 0; j < matrix->width; j++)
//         {
//             std::cout << matrix->matrix[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }
// }

int main()
{
    char inputText[1000];
    cout << "\nВведите текст для шифрования:\n";
    cin.getline(inputText, 1000);

    int inputLen = strlen(inputText);

    while (inputLen % 3 != 0)
    {
        inputText[inputLen++] = ' ';
    }
    inputText[inputLen] = '\0';

    int substrCount = inputLen / 3; // Количество подстрок

    char **substrings = new char*[substrCount]; // Массив подстрок
    for (int i = 0; i < substrCount; i++)
    {
        substrings[i] = new char[4];
    }

    // Разбитие исходного текста на подстроки по 3 символа
    devide_str_by_3(inputText, substrCount, substrings);
    // Матрицы со словами по 3 символа
    Matrix* vectors = new Matrix[substrCount];

    Matrix* encoded_vectors = new Matrix[substrCount];

    // Инициализация матриц нулями
    initialize_vectors_3_by_1(vectors, substrCount);
    initialize_vectors_3_by_1(encoded_vectors, substrCount);

    // Заоплонение мтариц кодами букв
    fill_vectors(vectors, substrings, substrCount);

    Matrix key;
    m_zero(&key, 3, 3);

    m_set(&key, 0, 0, 6);
    m_set(&key, 0, 1, 24);
    m_set(&key, 0, 2, 1);
    m_set(&key, 1, 0, 13);
    m_set(&key, 1, 1, 16);
    m_set(&key, 1, 2, 10);
    m_set(&key, 2, 0, 20);
    m_set(&key, 2, 1, 17);
    m_set(&key, 2, 2, 15);

    Matrix deKey;
    m_zero(&deKey, 3, 3);

    m_set(&deKey, 0, 0, 2);
    m_set(&deKey, 0, 1, 25);
    m_set(&deKey, 0, 2, 18);
    m_set(&deKey, 1, 0, 25);
    m_set(&deKey, 1, 1, 2);
    m_set(&deKey, 1, 2, 26);
    m_set(&deKey, 2, 0, 27);
    m_set(&deKey, 2, 1, 5);
    m_set(&deKey, 2, 2, 22);

    for (int i = 0; i < substrCount; i++)
    {
        m_hill_mult(&key, &vectors[i], &encoded_vectors[i]);
        // print_matrix(&encoded_vectors[i]);
    }

    cout << "Закодированная строка:\n";
    print_vectors(encoded_vectors, substrCount);
    cout << endl;

    Matrix *decoded_vectors = new Matrix[substrCount];
    initialize_vectors_3_by_1(decoded_vectors, substrCount);

    for (int i = 0; i < substrCount; i++)
    {
        m_hill_mult(&deKey, &encoded_vectors[i], &decoded_vectors[i]);
    }
    cout << "Разкодированная строка:\n";
    print_vectors(decoded_vectors, substrCount);
    cout << endl;

    for (int i = 0; i < substrCount; i++)
    {
        delete[] substrings[i];
    }
    delete[] substrings;


    for (int i = 0; i < substrCount; i++)
    {
        m_free(&vectors[i]);
    }
    delete[] vectors;

    for (int i = 0; i < substrCount; i++)
    {
        m_free(&encoded_vectors[i]);
    }
    delete[] encoded_vectors;

    for (int i = 0; i < substrCount; i++)
    {
        m_free(&decoded_vectors[i]);
    }
    delete[] decoded_vectors;

    m_free(&key);
    m_free(&deKey);

    return 0;
}
