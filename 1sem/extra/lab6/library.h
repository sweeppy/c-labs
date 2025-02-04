#include "book.h"
#include <cstring>

struct Library
{
    Book *books;

    int size;
    int capacity;
};

enum SortCriteria
{
    title,
    author,
    year,
    price,
    category
};
enum SortOrder
{
    up,
    down
};

void initialize_lib(Library &lib);
void initialize_lib(Library &lib, int capacity);

void increase_size(Library &lib);

void print_library(Library lib);
void printBook(Book book);

void addBook(Library &lib);

void edit_book(Library &lib);

void delete_book_by_title(Library &lib);

void find_by_SL_title(Library &lib);

void print_with_shortestTitle(Library &lib);
void print_with_longestTitle(Library &lib);

void show_edit_menu();

void saveLib_toFile(const Library &lib);
void uploadLib_fromFile(Library &lib);

void delete_library(Library &lib);

void show_book_fields(const char *fields[], int size);

void find_books(const char *fields[], Library lib, int size);
void find_by_title(Library lib);
void find_by_author(Library lib);
void find_by_category(Library lib);

void sort_library(const char *sort_criteria[], Library lib, int criteria_size);

SortOrder chooseOrder();
void bubble_sort(Library lib,
                 enum SortCriteria criteria, enum SortOrder order);
