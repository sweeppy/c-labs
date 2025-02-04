#include "library.h"
#include <iostream>

#define INIT_SIZE 0
#define INIT_CAPACITY 4
void initialize_lib(Library &lib)
{
    lib.books = new Book[INIT_CAPACITY];
    lib.size = INIT_SIZE;
    lib.capacity = INIT_CAPACITY;
}
void initialize_lib(Library &lib, int capacity)
{
    lib.books = new Book[capacity];
    lib.size = INIT_SIZE;
    lib.capacity = capacity;
}

void increase_size(Library &lib)
{
    lib.capacity *= 2;
    Book *newbooks = new Book[lib.capacity];

    for (int i = 0; i < lib.size; i++)
    {
        newbooks[i] = lib.books[i];
    }
    delete[] lib.books;
    lib.books = newbooks;
}

void print_library(Library lib)
{
    if (lib.size < 1)
    {
        printf("В библиотеке нет книг.\n");
        return;
    }
    for (int i = 0; i < lib.size; i++)
    {
        printBook(lib.books[i]);
    }
}

void addBook(Library &lib)
{
    // Если места нет, увеличиваем библиотеку
    if (lib.size == lib.capacity)
        increase_size(lib);

    printf("-------------------\n");

    while (true)
    {
        printf("Введите название книги:\n");
        char input[256] = "";
        scanf("%255[^\n]", input);
        getchar();

        if (strlen(input) == 0)
        {
            printf("Название книги не может быть пустым. Попробуйте заново.\n");
        }
        else
        {
            lib.books[lib.size].title = new char[256];
            strcpy(lib.books[lib.size].title, input);
            break;
        }
    }

    while (true)
    {
        printf("Введите автора книги:\n");
        char input[256] = "";
        scanf("%255[^\n]", input);
        getchar();

        if (strlen(input) == 0)
        {
            printf("Автор книги не может быть пустым полем. Попробуйте заново.\n");
        }
        else
        {
            lib.books[lib.size].author = new char[256];
            strcpy(lib.books[lib.size].author, input);
            break;
        }
    }

    while (true)
    {
        printf("Введите год издания книги:\n");
        int year;
        if (scanf("%d", &year) != 1)
        {
            printf("Данный ввод некорректный. Попробуйте снова.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        if (year < -3500 || year > 2025)
        {
            printf("Год не может быть годом до начала письменности или больше текущего.\n");
        }
        else
        {
            lib.books[lib.size].year = year;
            break;
        }
    }

    while (true)
    {
        printf("Введите цену книги:\n");
        int price;
        if (scanf("%d", &price) != 1)
        {
            printf("Данный ввод некорректный. Попробуйте снова.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        if (price < 0)
        {
            printf("Цена книги не может быть отрицательной.\n");
        }
        else
        {
            lib.books[lib.size].price = price;
            break;
        }
    }
    lib.books->category = new char[256];
    choose_category(lib.books[lib.size]);

    lib.size++;

    printf("Книга успешно создана.\n");
}

void edit_book(Library &lib)
{
    if (lib.size < 1)
    {
        printf("Невозможно отредактировать книги, библиотека пуста.\n");
        return;
    }
    while (true)
    {
        printf("Введите название книги которую хотите отредактировать.\nДля выхода введите <q>.\n");

        char input[256] = "";
        scanf("%255[^\n]", input);
        getchar();

        if (strcmp(input, "q") == 0)
            break;

        bool isBookExists = false; // Существует ли данная книга
        Book *current_book;

        for (int i = 0; i < lib.size; i++)
        {
            if (strcmp(lib.books[i].title, input) == 0)
            {
                current_book = &lib.books[i];
                isBookExists = true;
                break;
            }
        }
        if (!isBookExists)
        {
            printf("Книги с таким названием нет в библиотеке.\n");
            continue;
        }

        bool toContinue = true;
        while (toContinue)
        {

            printf("Изменение книги:\nВыберите номер операции:\n");
            show_edit_menu();
            printf("0. Выйти из режима редактирования.\n");

            int command;

            if (scanf("%d", &command) != 1)
            {
                printf("Некорректный ввод. Пожалуйста, введите номер операции.\n");
                fflush(stdin);
                continue;
            }
            fflush(stdin);

            switch (command)
            {
            case 1:
                editAuthor((*current_book).author);
                break;
            case 2:
                editTitle((*current_book).title);
                break;
            case 3:
                editYear((*current_book).year);
                break;
            case 4:
                editPrice((*current_book).price);
                break;
            case 5:
                editCategory((*current_book).category);
                break;
            case 0:
                toContinue = false;
                printf("Вы вышли из режима редактирования.\n");
                break;

            default:
                printf("Данной операции нет в списке.\n");
                break;
            }
        }
    }
}

void delete_book_by_title(Library &lib)
{
    if (lib.size < 1)
    {
        printf("Невозможно удалить книги, библиотека пуста.\n");
        return;
    }

    printf("Введите название книги, которую хотите удалить:\n");

    char input[256] = "";
    scanf("%255[^\n]", input);
    getchar();
    bool isDeleted = false;

    for (int i = 0; i < lib.size; i++)
    {
        if (strcmp(lib.books[i].title, input) == 0)
        {
            delete[] lib.books[i].title;
            delete[] lib.books[i].author;
            delete[] lib.books[i].category;

            for (int j = i; j < lib.size - 1; j++)
            {
                lib.books[j] = lib.books[j + 1];
            }
            lib.size--;
            isDeleted = true;
            printf("Книга успешно удалена.\n");
            break;
        }
    }

    if (isDeleted == false)
    {
        printf("Книги с таким названием не нашлось.\n");
    }
}

void find_by_SL_title(Library &lib)
{
    if (lib.size < 1)
    {
        printf("Невозможно выполнить действие, библиотека пуста.\n");
        return;
    }

    bool toContinue = true;
    while (toContinue)
    {
        printf("Введите номер операции:\n \
1. Найти книгу с самым коротким названием.\n \
2. Найти книгу с самым длинным названием.\n \
0. Выйти из поиска.\n");

        int command;

        if (scanf("%d", &command) != 1)
        {
            printf("Некорректный ввод. Пожалуйста, введите номер операции.\n");
            fflush(stdin);
            continue;
        }
        fflush(stdin);

        switch (command)
        {
        case 1:
            print_with_shortestTitle(lib);
            break;
        case 2:
            print_with_longestTitle(lib);
            break;
        case 0:
            toContinue = false;
            printf("Вы вышли из режима поиска.\n");
            break;

        default:
            printf("Данной команды нет в списке.\n");
            break;
        }
    }
}

void print_with_shortestTitle(Library &lib)
{
    if (lib.size < 1)
    {
        printf("Библиотека пуста.\n");
        return;
    }
    int title_length = strlen(lib.books[0].title);
    for (int i = 1; i < lib.size; i++)
    {
        if (strlen(lib.books[i].title) < title_length)
        {
            title_length = strlen(lib.books[i].title);
        }
    }
    printf("Вот книги с самым коротким названием:\n");
    for (int i = 0; i < lib.size; i++)
    {
        if (strlen(lib.books[i].title) == title_length)
        {
            printBook(lib.books[i]);
        }
    }
}

void print_with_longestTitle(Library &lib)
{
    if (lib.size < 1)
    {
        printf("Библиотека пуста.\n");
        return;
    }
    int title_length = strlen(lib.books[0].title);
    for (int i = 1; i < lib.size; i++)
    {
        if (strlen(lib.books[i].title) > title_length)
        {
            title_length = strlen(lib.books[i].title);
        }
    }
    printf("Вот книги с самым длинным названием:\n");
    for (int i = 0; i < lib.size; i++)
    {
        if (strlen(lib.books[i].title) == title_length)
        {
            printBook(lib.books[i]);
        }
    }
}

void show_edit_menu()
{
    const char *edit_commands[] = {
        "Изменить автора книги.",
        "Изменить название книги.",
        "Изменить год издания книги.",
        "Изменить цену книги.",
        "Изменить категорию книги.",
    };
    for (int i = 0; i < sizeof(edit_commands) / 8; i++)
    {
        printf("%d. %s\n", i + 1, edit_commands[i]);
    }
}

void saveLib_toFile(const Library &lib)
{
    if (lib.size < 1)
    {
        printf("Невозможно выполнить действие, библиотека пуста.\n");
        return;
    }
    printf("Введите название фала в который вы хотите \
сохранить содержимое картотеки.(example.txt)\n");
    char filename[100] = "";

    scanf("%99[^\n]", filename);
    getchar();

    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Не удалось открыть файл для записи.\n");
        return;
    }

    fprintf(file, "%d\n", lib.size);
    for (int i = 0; i < lib.size; i++)
    {
        fprintf(file, "%s\n%s\n%d\n%d\n%s\n",
                lib.books[i].title,
                lib.books[i].author,
                lib.books[i].year,
                lib.books[i].price,
                lib.books[i].category);
    }
    fclose(file);

    printf("Данные успешно сохранены в файл.\n");
}
void uploadLib_fromFile(Library &lib)
{
    printf("Введите название файла, который хотите открыть.\n");

    char filename[100] = "";
    scanf("%99[^\n]", filename);
    getchar();

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Не удалось открыть файл для чтения.\n");
        return;
    }

    delete_library(lib); // удаление всех книг

    int file_lib_size;
    fscanf(file, "%d\n", &file_lib_size);

    while (lib.capacity < file_lib_size)
    {
        lib.capacity *= 2;
    }

    initialize_lib(lib, lib.capacity); // новая библиотека

    for (int i = 0; i < file_lib_size; i++)
    {
        lib.books[i].title = new char[100];
        lib.books[i].author = new char[100];
        lib.books[i].category = new char[100];
        fscanf(file, "%99[^\n]\n", lib.books[i].title);
        fscanf(file, "%99[^\n]\n", lib.books[i].author);
        fscanf(file, "%d\n", &lib.books[i].year);
        fscanf(file, "%d\n", &lib.books[i].price);
        fscanf(file, "%99[^\n]\n", lib.books[i].category);
        lib.size++;
    }
    fclose(file);
    printf("Данные библиотеки успешно обновлены.\n");
}

void delete_library(Library &lib)
{
    for (int i = 0; i < lib.size; i++)
    {
        delete[] lib.books[i].title;
        delete[] lib.books[i].author;
        delete[] lib.books[i].category;
    }
    delete[] lib.books;
    lib.size = INIT_SIZE;
    lib.capacity = INIT_CAPACITY;
}

void find_books(const char *fields[], Library lib, int size)
{
    if (lib.size < 1)
    {
        printf("Невозможно выполнить поиск книг, библиотека пуста.\n");
        return;
    }
    show_book_fields(fields, size);
    printf("Введите номер критерия поиска:\n");
    int operation_num;
    while (true)
    {
        if (scanf("%d", &operation_num) != 1)
        {
            printf("Данный ввод некорректен. Попробуйте снова.\n");
            getchar();
            continue;
        }
        else
            break;
    }
    getchar();
    switch (operation_num)
    {
    case 1:
        find_by_title(lib);
        break;
    case 2:
        find_by_author(lib);
        break;
    case 3:
        find_by_category(lib);
        break;
    default:
        printf("Такого критерия нет в списке.\n");
        break;
    }
}

void show_book_fields(const char *fields[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d) %s\n", i + 1, fields[i]);
    }
}

void find_by_title(Library lib)
{
    printf("Введите название книги, которую хотите найти:\n");
    char input_title[256] = "";
    scanf("%255[^\n]", input_title);
    getchar();
    printf("Вот список книг с таким названием:\n");

    bool isFound = false;

    for (int i = 0; i < lib.size; i++)
    {
        if (strcmp(lib.books[i].title, input_title) == 0)
        {
            printBook(lib.books[i]);
            isFound = true;
        }
    }
    if (isFound == false)
    {
        printf("В библиотеке нет книг с таким названием.\n");
    }
}

void find_by_author(Library lib)
{
    printf("Введите автора книги, которую хотите найти:\n");
    char input_author[256] = "";
    scanf("%255[^\n]", input_author);
    getchar();
    printf("Вот список книг от этого автора:\n");

    bool isFound = false;

    for (int i = 0; i < lib.size; i++)
    {
        if (strcmp(lib.books[i].author, input_author) == 0)
        {
            printBook(lib.books[i]);
            isFound = true;
        }
    }
    if (isFound == false)
    {
        printf("В библиотеке нет книг от этого автора.\n");
    }
}

void find_by_category(Library lib)
{
    printf("Введите жанр книги, которую хотите найти:\n");

    char input_category[256] = "";
    scanf("%255[^\n]", input_category);
    getchar();

    bool isFound = false;

    printf("Вот список книг с таким жанром:\n");
    for (int i = 0; i < lib.size; i++)
    {
        if (strcmp(lib.books[i].category, input_category) == 0)
        {
            printBook(lib.books[i]);
            isFound = true;
        }
    }
    if (isFound == false)
    {
        printf("В библиотеке нет книг такого жанра.\n");
    }
}

void sort_library(const char *sort_criteria[], Library lib, int criteria_size)
{
    if (lib.size < 2)
    {
        printf("Невозможно выполнить сортировку, в библиотеке меньше двух книг.\n");
        return;
    }
    show_book_fields(sort_criteria, criteria_size);
    printf("Введите номер критерий сортировки:\n");

    int operation_num;
    while (true)
    {
        if (scanf("%d", &operation_num) != 1)
        {
            printf("Данный ввод некорректен. Попробуйте снова.\n");
            getchar();
            continue;
        }
        else
            break;
    }
    getchar();
    bool isSuccess = true;
    enum SortCriteria criteria;

    switch (operation_num)
    {
    case 1:
        criteria = title;
        break;
    case 2:
        criteria = author;
        break;
    case 3:
        criteria = year;
        break;
    case 4:
        criteria = price;
        break;
    case 5:
        criteria = category;
        break;

    default:
        printf("Такого критерия нет в списке.\n");
        isSuccess = false;
        break;
    }

    if (isSuccess)
    {
        enum SortOrder order = chooseOrder();
        bubble_sort(lib, criteria, order);
        printf("Библиотека успешно отсортирована.\n");
    }
}

SortOrder chooseOrder()
{
    while (true)
    {
        printf("Выберите порядок сортировки:\n \
1) Сортировка по возрастанию\n \
2) Сортировка по убыванию\n");
        int operation_num;
        while (true)
        {
            if (scanf("%d", &operation_num) != 1)
            {
                printf("Данный ввод некорректен. Попробуйте снова.\n");
                getchar();
                continue;
            }
            else
                break;
        }
        getchar();

        switch (operation_num)
        {
        case 1:
            return up;
        case 2:
            return down;
        default:
            printf("Такой операции нет в списке.\n");
            break;
        }
    }
}

void bubble_sort(Library lib,
                 enum SortCriteria criteria, enum SortOrder order)
{
    for (int i = 0; i < lib.size; i++)
    {
        for (int j = 0; j < lib.size - 1 - i; j++)
        {
            int compare_result = 0;
            switch (criteria)
            {
            case title:
                compare_result = strcmp(lib.books[j].title, lib.books[j + 1].title);
                break;
            case author:
                compare_result = strcmp(lib.books[j].author, lib.books[j + 1].author);
                break;
            case year:
                compare_result = lib.books[j].year - lib.books[j + 1].year;
                break;
            case price:
                compare_result = lib.books[j].price - lib.books[j + 1].price;
                break;
            case category:
                compare_result = strcmp(lib.books[j].category, lib.books[j + 1].category);
                break;
            }
            if ((order == up && compare_result > 0) ||
                (order == down && compare_result < 0))
            {
                Book temp = lib.books[j];
                lib.books[j] = lib.books[j + 1];
                lib.books[j + 1] = temp;
            }
        }
    }
}