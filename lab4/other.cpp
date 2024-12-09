#include "other.h"
#include<iostream>
#include<cassert>
using std::cout;

void inc_by_value(int value)
{
    value++;
}
void inc_by_pointer(int* value)
{
    value++;
}
void inc_by_reference(int& value)
{
    value++;
}


void swap(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}
void swap(int& first, int& second)
{
    int temp = first;
    first = second;
    second = temp;
}


int findMinInArray(const int *array, int length)
{
    assert(length > 0 && "Длина массива должна быть больше 0");
    int min = array[0];
    for (int i = 1; i < length; i++)
    {
        if (array[i] < min)
        {
            min = array[i];
        }
    }
    return min;
}
int findMinIn2DArray(int **array, int rows, int columns)
{
    assert(rows > 0 && columns > 0 && "Длина массива должна быть больше 0");
    int min = array[0][0];
    for (int i = 0; i < rows; i++)
    {
        int res = findMinInArray(array[i], columns);
        if (res < min)
        {
            min = res;
        }
    }
    return min;
}




short my_str_cmp(const char *str1, const char *str2)
{
    short res = 0;
    while(*str1 != '\0' && *str2 != '\0')
    {
        if (*str1 != *str2)
        {
            *str1 < *str2 ? res = 1 : res = -1;
            break;
        }
        str1++;
        str2++;
    }
    return res;
}




bool isLeapYear(unsigned short year)
{
    return (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
}

int nDayTab[2][12] = {
    {31,28,31,30,31,30,31,31,30,31,30,31}, //невисокосный год
    {31,29,31,30,31,30,31,31,30,31,30,31}};  //високосный год

unsigned short day_of_year(unsigned short day, unsigned short month, unsigned short year)
{
    short whatYear = isLeapYear(year) ? 1 : 0;
    unsigned short dayOfYear = day;
    for (int i = 0; i < month - 1; i++)
    {
        dayOfYear += nDayTab[whatYear][i];
    }
    return dayOfYear;
}

short* day_of_month(unsigned short day, unsigned short year)
{

    short whatYear = isLeapYear(year) ? 1 : 0;

    short month = 0;
    while (day - nDayTab[whatYear][month] > 0)
    {
        day -= nDayTab[whatYear][month];
        month++;
    }

    short *dayAndMonth = new short[2];
    dayAndMonth[0] = day;
    dayAndMonth[1] = ++month; // так как счет месяце начинаетяс с 0 (для правильной индексации nDatTab)
    return dayAndMonth;
}




void add_unique(int *&arr, int& length, int newValue)
{
    for (int i = 0; i < length; i++)
    {
        if (arr[i] == newValue)
            return;
    }
    length++;
    int *newArr = new int[length];
    for (int i = 0; i < length - 1; i++) {
        newArr[i] = arr[i];
    }
    newArr[length - 1] = newValue;
    delete[] arr;
    arr = newArr;
}
void print_array(int *arr, int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << arr[i] << " ";
    }
    cout << std::endl;
}



unsigned int sum_of_natural(unsigned int n)
{
    if (n == 1)
        return 1;
   
    return n + sum_of_natural(n - 1);
}



const char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";

int encoded32_size(int raw_size)
{
    return (raw_size * 8 + 4) / 5;
}
int decoded32_size(int encode_size)
{
    return (encode_size * 5) / 8;
}

int encode32(const char *raw_data, int raw_size, char *dst)
{
    if (!raw_data || !dst || raw_size <= 0)
        return 1;

    int bit_pos = 0;
    int dst_pos = 0;
    int current_value = 0; // здесь число от 0 до 31 (5 бит)

    for (int i = 0; i < raw_size; i++)
    {
        for (int bit = 7; bit >= 0; bit--)
        {
            int bit_value = (raw_data[i] >> bit) & 1; // Получение значения бита

            current_value = (current_value << 1) | bit_value; // Добавление значение бита в число из 5 бит;

            bit_pos++;

            // Если считался 5-ый бит
            if (bit_pos == 5)
            {
                dst[dst_pos++] = table[current_value];
                bit_pos = 0;
                current_value = 0;
            }
        }

    }

    if (bit_pos > 0) // Если остались незакодированные биты(дополнение нулями)
        {
            current_value = current_value << (5 - bit_pos);
            dst[dst_pos] = table[current_value];
        }
    return 0;
}

int decode32(const char *encoded_data, int encoded_size, char *dst)
{
    if (!encoded_data || !dst || encoded_size <= 0)
        return 1;

    int bit_pos = 0;
    int dst_pos = 0;
    int current_value = 0;

    for (int i = 0; i < encoded_size; i++)
    {
        int code_number = -1; // Чило закондированное в символ (от 0 до 31)
        for (int j = 0; j < 32; j++)
        {
            if (table[j] == encoded_data[i])
            {
                code_number = j;
                break;
            }
        }
        if (code_number == -1)
            return 2;

        for (int bit = 4; bit >= 0; bit--)
        {
            int bit_value = (code_number >> bit) & 1;

            current_value = (current_value << 1) | bit_value;

            bit_pos++;

            if (bit_pos == 8)
            {
                dst[dst_pos++] = current_value;
                current_value = 0;
                bit_pos = 0;
            }
        }
    }
    
    if (bit_pos > 0) // Если остались неразкодированые биты
    {
        current_value <<= 8 - bit_pos;
        dst[dst_pos] = current_value;
    }

    return 0;
}


void var_args(int first, ...)
{
    va_list args;
    va_start(args, first);

    int count = 0;
    int value = first;

    cout << "Параметры: ";
    while (value != 0)
    {
        cout << value << " ";
        count++;
        value = va_arg(args, int);
    }
    cout << "\n";

    va_end(args);
    cout << "Всего параметров: " << count << std::endl;
}



int *my_min(int *arr, int size)
{
    int* min_ptr = &arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] < *min_ptr)
            min_ptr = &arr[i];
    }
    return min_ptr;
}