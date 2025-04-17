#include "List.hpp"
#include "colors.hpp"
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;

int main()
{
    cout << PURPLE << "=== START ===" << RESET << endl;
    ;
    List list;
    list.add_tail(Circle(Pointer(3, 3), 3));
    list.add_tail(Circle(Pointer(1, 1), 1));
    list.add_tail(Circle(Pointer(2, 2), 2));

    cout << "Before sort:\n"
         << list << endl;
    list.sort_by_square();
    cout << "After sort:\n"
         << list << endl;

    const char *folder = "txt_files/";
    cout << YELLOW << "Enter Output File Name: " << RESET;

    char filename[80];
    cin >> filename;

    cout << endl;
    char full_path[100];
    strcpy(full_path, folder);
    strcat(full_path, filename);
    strcat(full_path, ".txt");

    std::ofstream fout(full_path);
    fout << list;
    fout.close();

    list.clear();
    list.read_form_file(full_path);

    cout << "List from file:\n"
         << list << endl;

    return 0;
}
