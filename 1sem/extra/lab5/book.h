struct Book
{
    char *author;
    char *title;

    int year;
    int price;

    char *category;
};
void change_string_field(const char *src, char *&dst);
void printBook(Book &book);

void editBook(Book &book);
void print_editBook_commands(const char **commands, int size);
void editAuthor(char *&author);
void editTitle(char *&title);
void editYear(int &year);
void editPrice(int &price);
void editCategory(char *&category);