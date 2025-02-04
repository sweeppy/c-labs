#include "other.h"
#include "book.h"
#include <iostream>

void printBook(Book &book)
{
    printf("Автор: %s\n", book.author);
    printf("Название: %s\n", book.title);
    printf("Год издания: %d\n", book.year);
    printf("Цена: %d\n", book.price);
    printf("Категория: %s\n", book.category);
}

void print_commands(const char *commands[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d. %s\n", i + 1, commands[i]);
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

void editBook(Book &book)
{
    const char *edit_commands[] = {"Изменить автора книги", "Изменить название книги",
                                   "Изменить год издания книги", "Изменить цену книги",
                                   "Изменить категорию книги"};

    char command;

    while (true)
    {
        printf("Изменение книги:\nВыберите номер операции:\n");
        print_commands(edit_commands, sizeof(edit_commands) / 8);
        printf("   Для выхода введите символ <q>\n");

        scanf(" %c", &command);

        if (command == 'q')
            break;

        getchar(); // Чтобы не выводился опять список операций

        switch (command)
        {
        case '1':
            editAuthor(book.author);
            break;
        case '2':
            editTitle(book.title);
            break;
        case '3':
            editYear(book.year);
            break;
        case '4':
            editPrice(book.price);
            break;
        case '5':
            editCategory(book.category);
            break;

        default:
            printf("Данной операции нет в списке.\n");
            break;
        }
    }
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
    if (new_year < -3500 || new_year > 2024)
    {
        printf("Год издания не может быть годом до начала письменности или больше текущего.\n");
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
    getchar();

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