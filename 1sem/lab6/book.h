struct Book
{
    char *author;
    char *title;

    int year;
    int price;

    char *category;
};

void choose_category(Book &book);

void editAuthor(char *&author);
void editTitle(char *&title);
void editYear(int &year);
void editPrice(int &price);
void editCategory(char *&category);

void change_string_field(const char *src, char *&dst);

void show_edit_menu();