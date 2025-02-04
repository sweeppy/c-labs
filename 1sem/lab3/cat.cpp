#include <iostream>
#include <string>
#include <cstring>
using namespace std;

#define MAX_WORD_LENGTH 40

int main()
{
    string inputStr;
    cout << "Введите строку:" << "\n";
    cin.ignore();
    getline(cin, inputStr);
    unsigned int strCounter = 0;
    unsigned int wordsCounter = 0;
    char **words = new char *[inputStr.length()];

    string word = "";

    for (int i = 0; i < inputStr.length(); i++) // Разбиение строки на слова
    {
        if (inputStr[i] != ' ' && i != inputStr.length() - 1)
        {
            word += inputStr[i];
        }
        else
        {
            if (i == inputStr.length() - 1)
                word += inputStr[i];
            if (word.length() > MAX_WORD_LENGTH)
            {
                cout << "Данное слово слишком большое \n";
                return 0;
            }
            words[wordsCounter] = new char[word.length() + 1];
            strcpy(words[wordsCounter++], word.c_str());
            word = "";
        }
    }
    cout << "  __________________________________________" << "\n";

    string now = "";
    for (int i = 0; i < wordsCounter; i++)
    {
        if (now.length() + strlen(words[i]) < MAX_WORD_LENGTH)
        {
            now += words[i];
            now += ' ';
        }
        else
        {
            string endspace((40 - (now.length() - 1)), ' ');
            cout << " |" << ' ' << now << endspace << '|' << "\n";
            now = words[i];
            now += ' ';
        }
    }
    string endspace((40 - (now.length() - 1)), ' ');
    cout << " |" << ' ' << now << endspace << '|' << "\n";
    cout << "  __________________________________________" << "\n";

    std::cout << "     \\ \n";
    std::cout << "      \\ \n";
    std::cout << "        /\\_/\\  (\n";
    std::cout << "       ( ^.^ ) _)\n";
    std::cout << "         \\\"/  (\n";
    std::cout << "       ( | | )\n";
    std::cout << "      (__d b__)\n";

    for (int i = 0; i < wordsCounter; i++)
    {
        delete[] words[i];
    }
    delete[] words;
}