#include "library.h"
#include <iostream>
void printBook(Book book)
{
    printf("*****************************\n\n");
    printf("Автор: %s\n", book.author);
    printf("Название: %s\n", book.title);
    printf("Год издания: %d\n", book.year);
    printf("Цена: %d\n", book.price);
    printf("Категория: %s\n", book.category);
    printf("\n\n*****************************\n");
}

void choose_category(Book &book)
{
    const char *categories[] = {"Роман", "Публицистика", "Поэзия",
                                "Фантастика", "Биография", "Нет нужной категории"};

    for (int i = 0; i < 6; i++)
    {
        printf("%d) %s\n", i + 1, categories[i]);
    }
    printf("Выберите категорию книги(введите номер выбранной категории):\n");

    int category_number;

    while (true)
    {
        if (scanf("%d", &category_number) != 1)
        {
            printf("Данный ввод некорректный. Попробуйте снова.\n");
            while (getchar() != '\n')
                ;
            continue;
        }
        if (category_number < 0 || category_number > 6)
        {
            printf("Введен неверный номер категории! Попробуйте снова.\n");
        }
        else
            break;
    }
    getchar();
    if (category_number == 6)
    {
        change_string_field("Неопределенно", book.category);
    }
    else
    {
        change_string_field(categories[category_number - 1], book.category);
    }
}

void change_string_field(const char *src, char *&dst)
{
    int size = strlen(src) + 1;

    if (dst != nullptr)
    {
        delete[] dst;
    }

    dst = new char[size];

    strcpy(dst, src);
}

void editAuthor(char *&author)
{
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
            change_string_field(input, author);
            printf("Автор книги успешно изменен.\n");
            break;
        }
    }
}
void editTitle(char *&title)
{
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
            change_string_field(input, title);
            printf("Название книги успешно изменено.\n");
            break;
        }
    }
}
void editYear(int &year)
{
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
            year = year;
            printf("Год книги успешно изменен.\n");
            break;
        }
    }
}
void editPrice(int &price)
{
    while (true)
    {
        printf("Введите цену книги:\n");
        int input_price;
        if (scanf("%d", &input_price) != 1)
        {
            printf("Данный ввод некорректный. Попробуйте снова.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        if (input_price < 0)
        {
            printf("Цена книги не может быть отрицательной.\n");
        }
        else
        {
            price = input_price;
            printf("Цена книги успешно изменена.\n");
            break;
        }
    }
}
void editCategory(char *&category)
{
    int category_number;

    const char *categories[] = {"Роман", "Проза", "Лирика", "Драма", "Эпос"};

    printf("Для изменения выберете номер категории из списка ниже:\n\n");

    for (int i = 0; i < sizeof(categories) / 8; i++)
    {
        printf("%d. %s\n", i + 1, categories[i]);
    }

    scanf("%d", &category_number);
    while (getchar() != '\n')
        ;

    switch (category_number)
    {
    case 1:
        change_string_field(categories[0], category);
        break;
    case 2:
        change_string_field(categories[1], category);
        break;
    case 3:
        change_string_field(categories[2], category);
        break;
    case 4:
        change_string_field(categories[3], category);
        break;
    case 5:
        change_string_field(categories[4], category);
        break;

    default:
        printf("Такой категории нет в списке! \n");
        break;
    }
}
