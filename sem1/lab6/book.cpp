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

    scanf("%d", &category_number);

    if (category_number < 0 || category_number > 6)
    {
        printf("Введен неверный номер категории!\n");
        change_string_field("Пусто", book.category);
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
    char new_author[256];
    printf("Введите нового автора книги:\n");
    scanf("%255[^\n\r]", new_author);
    change_string_field(new_author, author);
}
void editTitle(char *&title)
{
    char new_title[256];
    printf("Введите нового автора книги:\n");
    scanf("%255[^\n\r]", new_title);
    change_string_field(new_title, title);
}
void editYear(int &year)
{
    printf("Введите новый год издания:\n");
    int new_year;
    scanf("%d", &new_year);
    if (new_year < -3500)
    {
        printf("Год не может быть годом до начала письменности\n");
        return;
    }
    year = new_year;
}
void editPrice(int &price)
{
    printf("Введите новую цену в рублях:\n");
    int new_price;
    scanf("%d", &new_price);
    if (new_price < 0)
    {
        printf("Цена не может быть отрицательной\n");
        return;
    }
    price = new_price;
}
void editCategory(char *&category)
{
    int category_number;

    const char *categories[] = {"Роман", "Проза", "Лирика", "Драма", "Эпос"};

    printf("Для изменения выбирете номер категории из списка ниже:\n\n");

    for (int i = 0; i < sizeof(categories) / 8; i++)
    {
        printf("%d. %s\n", i + 1, categories[i]);
    }

    scanf("%d", &category_number);
    fflush(stdin);

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
