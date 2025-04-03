#include<iostream>
void inc_by_value(int value);
void inc_by_pointer(int* value);
void inc_by_reference(int& value);


void swap(int *first, int *second);
void swap(int &first, int &second);


int findMinInArray(const int *array, int length);
int findMinIn2DArray(int **array, int rows, int columns);


short my_str_cmp(const char *str1, const char *str2);


bool isLeapYear(unsigned int year);
unsigned short day_of_year(unsigned short day, unsigned short month, unsigned short year);
short* day_of_month(unsigned short day, unsigned short year);


void add_unique(int *&arr, int& length, int newValue);
void print_array(int *arr, int length);


unsigned int sum_of_natural(unsigned int N);


int encoded32_size(int raw_size);
int decoded32_size(int encode_size);

int encode32(const char *raw_data, int raw_size, char *dst);
int decode32(const char *encoded_data, int encoded_size, char *dst);


void var_args(int first, ...);


int *my_min(int *arr, int size);