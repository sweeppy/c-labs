#include <iostream>
#include <cmath>

using std::cout, std::cin;

const char numbers[] = "0123456789ABCDEF";

char x16First[10] = " 00000000";
char x16Second[10] = " 00000000";

char result[10] = " 00000000";

int charToInt(char c)
{
    if (c >= '0' && c<= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
}

void differense(int size, char *bigger, char *smaller)
{
    int additive = 0;
    for (int i = size - 1; i >= 1; i--)
    {
        int diff = charToInt(bigger[i]) - additive - charToInt(smaller[i]);
        if (diff < 0)
        {
            diff += 16;
            additive = 1;
        }
        else
            additive = 0;
        result[i] = numbers[diff];
    }
}

int main() {
        //todo доп задание | Вывод в 16ричной + сложение этих чисел
        int num1, num2; // 0100 1111 0000 0000 0110 1111 0000 0010 -- 1325428482

        short size = sizeof(x16First) - 1;

        short point = 1;

        cout << "Введите первое число: " << "\n";
        cin >> num1;
        if (num1 < 0)
        {
            x16First[0] = '-';
            num1 = -num1;
        }

        while (num1 > 0)
        {
            int temp = num1 & 0xf;
            x16First[size - point] = numbers[temp];
            point++;
            num1 >>= 4;
        }

        cout << "Ваше первое число в 16-ой СС: " << "\n" << x16First << "\n";

        point = 1;
        cout << "Введите второе число: " << "\n";
        cin >> num2;
        if (num2 > 0)
        {
            x16Second[0] = ' ';
        }
        else
        {
            x16Second[0] = '-';
            num2 = -num2;
        }

        while (num2 > 0)
        {
            int temp = num2 & 0xf;
            x16Second[size - point] = numbers[temp];
            point++;
            num2 >>= 4;
        }

        cout << "Ваше второе число в 16-ой СС: " << "\n" << x16Second << "\n";

        // Сложение
        if ((x16First[0] == '-' && x16Second[0] == '-') || (x16First[0] == ' ' && x16Second[0] == ' '))
        {
            unsigned short next = 0;
            for (int i = size - 1; i >= 1; i--)
            {
                int sum = charToInt(x16First[i]) + charToInt(x16Second[i]) + next;
                result[i] = numbers[sum % 16];
                next = sum / 16;
            }
            if (x16First[0] == '-')
                result[0] = '-';
        }
        else // Вычитание
        {
            bool firstIsBigger = num1 > num2;
            int additive = 0;
            if (firstIsBigger)
            {
                differense(size, x16First, x16Second);
                result[0] = x16First[0];
            }
            else {
                differense(size, x16Second, x16First);
                result[0] = x16Second[0];
            }
        }

        cout << "\n";

        cout << "Результат сложения: " << "\n" << result << "\n";
}