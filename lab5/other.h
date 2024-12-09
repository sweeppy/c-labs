
//Прототипы используемых в данном задании функций:

void sort(char* pcFirst, int nNumber, int size,
void (*Swap)(void*, void*), int (*Compare)(void*, void*) );

void swap_int(void* p1, void* p2);
int cmp_int(void* p1, void* p2);

void swap_double(void *p1, void *p2);
int cmp_double(void *p1, void *p2);

void swap_str(void *p1, void *p2);
int cmp_str(void *p1, void *p2);

double add(double first, double second);
double sub(double first, double second);
double mul(double first, double second);
double div(double first, double second);
void print_math_operations();


void print_max(double *arr, int size);
void print_min(double *arr, int size);
void sort_asc(double *arr, int size);
void sort_desc(double *arr, int size);


double integrate(double(*function)(double), double a, double b, int n);
double square_function(double x);
double sin_function(double x);
double exp_function(double x);
double linear_function(double x);
