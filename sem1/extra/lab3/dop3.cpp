// Дополнительное задание к 3 лабораторной.
/*
TODO

"Напиши программу, которая на основе динамически выделенного массива целых
чисел строит двоичное дерево поиска. Каждый элемент массива должен быть
вставлен в дерево, а после этого программа должна вывести элементы дерева
в порядке ""в глубину"".

Условия:

1. Программа должна динамически выделять память под массив и структуру дерева.
2. Каждый элемент массива должен быть добавлен в дерево с учетом свойств
двоичного дерева поиска (меньшие элементы - в левое поддерево, большие - в правое).

Пример ввода:

Введите количество элементов массива: 7
Введите элементы массива: 50 30 20 40 70 60 80

Пример вывода:

Элементы дерева в порядке инфиксного обхода: 20 30 40 50 60 70 80"
*/


#include<iostream>
#include<cmath> // для возведения в степень(pow)

using std::cout, std::cin, std::endl;

void insertIntoTree(int* tree, int value, int index) 
{
    if (tree[index] == -1)
    {
        tree[index] = value;
        return;
    }
    short where = (value < tree[index]) ? 0 : 1; // 0 - влево, 1 - вправо
    switch (where)
    {
    case 0:
        {
            int leftChildIndex = index * 2 + 1;
            if (tree[leftChildIndex] == -1)
                tree[leftChildIndex] = value;
            else
                insertIntoTree(tree, value, leftChildIndex);
            break;
        }
    case 1:
        {
            int rightChildIndex = index * 2 + 2;
            if (tree[rightChildIndex] == -1)
                tree[rightChildIndex] = value;
            else
                insertIntoTree(tree, value, rightChildIndex);
            break;
        }
    }
}

void printInInfixMove(int *tree, int index, int size)
{
    if (index >= size)
        return;
    int leftChild = index * 2 + 1;
    int rightChild = index * 2 + 2;

    printInInfixMove(tree, leftChild, size);
    if (tree[index] != -1)
    {
        // cout << tree[index] << "|" << index << " "; // для дебага(просмотр индексов)
        cout << tree[index] << " ";
    }
    printInInfixMove(tree, rightChild, size);
}

int main()
{
    int n;
    cout << "Введите количество элементов массива: " << "\n";
    cin >> n;
    cout << endl;
    if (n < 1)
    {
        cout << "В массиве должен быть хотя бы один элемент.";
        return 0;
    }
    int size = pow(2, n) - 1;
    int *tree = new int[size];

    for (int i = 0; i < size; i++) {
        tree[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
            int inputNumber;
            cout << "Введите число массива:" << "\n";
            cin >> inputNumber;

            insertIntoTree(tree, inputNumber, 0);
            // cout << "\n";
            // printInInfixMove(tree, 0, size);
    }
    cout << endl;

    cout << "Двоичное дерево в инфиксном обходе: " << "\n";
    printInInfixMove(tree, 0, size);

    delete[] tree;


    return 0;
}