/**
 * Лабораторная работа №3. Перегрузка операторов, константные методы, битовые
 * поля, объединения.
 *
 * В этой работе и далее предполагается, что вы будете использовать классы,
 * написанные в прошлых работах, и дополнять их по необходимости. Эти классы
 * будут называться по имени без дополнительных указаний, что их надо взять из
 * прошлой работы.
 *
 * Предполагается, что новый классы будут созданы по аналогии с предыдущими
 * работами в отдельных файлах, которые будут включены в сборку.
 *
 * При работе с классами - в учебных целях - нельзя пользоваться контейнерами
 * стандартной библиотеки и нужно следовать принципам инкапсуляции.
 */

#include <utility>
#include <cassert>
#include <iostream>
#include "matrix.hpp"
#include "colors.hpp"
#include "shortArray.hpp"
#include "workerDb.hpp"
#include "file.hpp"
#include "boolArray.hpp"

using std::cout;
using std::endl;

int main()
{

    /**
     * Задание 1. Перегрузка операторов.
     */

    /**
     * Задание 1.1. Оператор присваивания.
     *
     * Перегрузите оператор присваивания для классов `MyString` и `Matrix`.
     * Ожидается, что оператор присваивания работает так же, как конструктор
     * копирования.
     *
     * Проверьте корректность работы оператора в следующих блоках кода.
     */

    {
        MyString s1("AAA"), s2;
        s2 = s1;
        s1 = "CCC";
        s2 = MyString("tmp");

        // * Не дает -Werror
        // s1 = s1;

        s1 = *&s1;
    }

    {
        Matrix m1(10), m2(10, 2);
        m1 = m2;
        m2 = Matrix(3, 4, 1.0);

        // * Не дает -Werror
        // m1 = m1;

        m1 = *&m1;
    }

    /**
     * Задание 1.2. Перегрузка арифметических операторов. Перегрузка методами и
     * глобальными функциями.
     */

    /**
     * Задание 1.2.1. Составное присваивание.
     *
     * Для класса `Matrix` перегрузите следующие операторы методом класса:
     * - `+=` и `-=` с объектом класса `Matrix`;
     * - `*=` и `/=` со значением double.
     *
     * Такие операторы не должны менять правый операнд. При наличии недопустимых
     * аргументов выкиньте какое-нибудь исключение.
     *
     * Ваши операторы должны работать в следующем блоке кода.
     */

    {
        Matrix m1(4), m2(4, 4, 1);
        m2 += m1;
        m2 -= m1 += m1;
        m1 *= 2;
        m2 /= 3;
    }

    /**
     * Задание 1.2.2. Бинарные операторы.
     *
     * Для класса `Matrix` перегрузите следующие операторы методом класса:
     * - `+` и `-` с объектом класса `Matrix`;
     * - `*` с объектом класса `Matrix`;
     * - `*` и `/` со значением double.
     *
     * Эти операторы не должны изменять ни левый, ни правый операнд и возвращать
     * новое значение.
     */

    {
        Matrix m1(4), m2(4, 4, 1);
        Matrix m3 = (m1 + m2) * m1 * 4 / 2 - m2;
    }

    /**
     * Задание 1.2.3. Перегрузка глобальными функциями.
     *
     * Перегрузите оператор `*` для операндов `double` и `Matrix` глобальной
     * функцией.
     *
     * Перегрузите унарный оператор `-` для класса `Matrix` с помощью глобальной
     * функции.
     *
     * Какую из этих функций нельзя перегрузить методом класса? Почему?
     */
    /*
     * Функцию operator*(double, Matrix) нельзя перегрузить методом класса,
     * потому что методы класса всегда имеют неявный параметр this (левый операнд),
     * который должен быть объектом этого класса.
     * Поэтому это работало бы только для вызова вида (matrix * 2.0), но не для (2.0 * matrix)
     */

    /**
     * Задание 1.2.4. Операторы для строки.
     *
     * Перегрузите операторы `+` и `+=` для класса `MyString`, где в качестве
     * правого операнда будет `MyString` или `const char *`. Сложение в этом
     * случае должно выполнять конкатенацию строк.
     *
     * Ваши операторы должны работать в следующем блоке кода.
     */

    cout << endl;
    {
        MyString s1("abc"), s2("def"), s3;
        s1 += s2 += "111";
        s2 += "222" + s1 + "333";
        s3 += s3;
        cout << s1.get_data() << "\n"  // correct
             << s2.get_data() << "\n"  // correct
             << s3.get_data() << endl; // correct
    }
    cout << endl;

    /**
     * Задание 1.3. Move-семантика.
     *
     * Перегрузите move-оператор присваивания и move-конструктор для классов
     * `MyString` и `Matrix`. В этих операторах нужно "забирать" данные из
     * правого операнда, а не копировать. При этом правый операнд должен
     * становиться "пустым".
     *
     * С помощью отладчика или отладочной печати отследите, сколько раз в
     * следующем блоке происходит выделение динамической памяти, - до реализации
     * move-оператора/конструктора и после.
     */

    cout << endl;
    cout << PURPLE << "Allocation:" << RESET << endl;
    {
        MyString s1("abc");
        MyString s2 = s1 + "ccc";
        s1 = "abc" + s2;
        s2 = std::move(s1);

        Matrix m1(4), m2 = m1 + m1;
        m1 = m2 * m1;
        m2 = std::move(m1);
    }
    cout << endl;
    /*
        * Без move-конструктора; выделилась память:
        String: 5
        Matrix: 5
        * С move-конструктором; выделилась память:
        String: 3
        Matrix: 3
    */

    /**
     * Задание 1.4. Операторы сравнения.
     *
     * Реализуйте для класса `MyString` операторы сравнения `==`, `!=`, `<`,
     * `<=` для сравнения с объектами `MyString` и `const char *`.
     *
     * Операторы должны сравнивать строки лексикографически.
     */
    {
        MyString s1("abc"), s2("ab"), s3 = s1;
        assert(s2 < s1);
        assert(s1 == s3);
        assert(s1 != s2);
        assert(s1 <= s3);
        assert("ab" == s2);
        assert("aba" < s1);
        assert("aba" <= s3);
    }

    /**
     * Задание 1.5. Оператор индексирования.
     *
     * Перегрузите оператор индексирования для класса `MyString`, который
     * возвращает ссылку на i-тый символ. Если индекс выходит за границы
     * массива, киньте какое-нибудь исключение.
     */
    cout << endl;
    {
        MyString s1("abc");
        s1[0] = s1[1] = 'd';
        cout << s1[0] << ' ' << s1[1] << endl;
    }
    cout << endl;

    /**
     * Задание 1.6. Операторы ввода и вывода с потоками стандартной библиотеки.
     *
     * Реализуйте для класса `MyString` операторы `<<`, который позволит
     * выводить строку в поток вывода `std::ostream`.
     *
     * Реализуйте для класса `MyString` оператор `>>`, который позволит вводить
     * строку до первого переноса строки из потока ввода `std::istream`.
     *
     * Проверьте работу этих операторов на следующем примере.
     */

    {
        MyString s("123");
        std::cout << "This is my string: '" << s << "'\n";
        std::cout << "Enter your string: ";
        std::cin >> s;
        std::cout << "Your string: '" << s << "'\n";
    }

    /**
     * Задание 2. Константные методы.
     *
     * Объявите все методы (в том числе перегруженные операторы), которые не
     * должны менять объект, для которого они были вызваны, константными.
     *
     * После этого следующая функция должна собираться:
     *
     * MyString addTxtExtension(const MyString &path) { return path + ".txt"; }
     */

    /**
     * Задание 3. Объединения и битовые поля.
     */

    /**
     * Задание 3.1. Динамический массив.
     *
     * Реализуйте класс ShortArray, который будет хранить динамический массив
     * элементов типа short, количество выделенной памяти (size_t) и количество
     * элементов массива (size_t).
     *
     * Реализуйте для этого класса конструкторы и операторы, которые посчитаете
     * нужными, оператор `[]`, а также методы:
     * - `void push(short new_val)` - для добавления элемента в конец массива;
     * - `short pop()` - для удаления и возвращения элемента из конца массива;
     * - `size_t size() const` - возвращает размер массива;
     * - `void resize(size_t new_size, short fill_value = 0)` - изменение
     *    размера массива, при увеличении размера массив заполняется значением
     *    `fill_value`.
     *
     * Продемонстрируйте ниже работу класса.
     */
    cout << endl;
    cout << PURPLE << "ShortArray Task:" << RESET << endl;
    {
        ShortArray arr;
        arr.push(10);
        arr.push(20);
        arr.push(30);

        std::cout << "Array size: " << arr.size() << std::endl;
        std::cout << "Elements: ";
        for (size_t i = 0; i < arr.size(); i++)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "Popped: " << arr.pop() << std::endl;
        arr.resize(5, 99);

        std::cout << "After resize: ";
        for (size_t i = 0; i < arr.size(); i++)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
    cout << endl;

    /**
     * Задание 3.2. Объединения.
     *
     * Есть проблема: даже для самого маленького массива будет
     * выделена динамическая память. Однако, размер у такой структуры может
     * быть, например, 24 байта, что вмещает встроенный массив из 12 элементов.
     *
     * С помощью объединений в языке С мы можем интерпретировать одни и те же
     * данные по разному. Поля динамического массива { short *, size_t, size_t }
     * мы можем воспринимать как массив short.
     *
     * Используя объединения, реализуйте хранение элементов массива прямо в
     * памяти, отведенной под этот класс, если массив туда помещается.
     * По каким признаком вы можете различить хранится ли память динамически или
     * она встроена в класс?
     *
     * Рассчитайте допустимый размер массива через оператор sizeof. Проверьте,
     * что объем памяти, занимаемой классом не увеличилась.
     *
     * Продемонстрируйте, что все методы работают верно для обоих способов
     * хранения памяти.
     */

    cout << endl;
    cout << PURPLE << "ShortArray Union Task:" << RESET << endl;
    {
        cout << YELLOW << "=== Testing ShortArray (stack storage) ==="
             << RESET << endl;

        ShortArray arr_stack(5, 42);

        // param constructor stack
        assert(arr_stack.size() == 5);
        for (size_t i = 0; i < arr_stack.size(); i++)
        {
            assert(arr_stack[i] == 42);
        }
        cout << GREEN "Constructor with parameters (stack): OK"
             << RESET << endl;

        // push/pop stack
        arr_stack.push(99);
        assert(arr_stack.size() == 6);
        assert(arr_stack[5] == 99);

        short val = arr_stack.pop();
        assert(val == 99);
        assert(arr_stack.size() == 5);
        cout << GREEN "Push/pop (stack): OK"
             << RESET << endl;

        // [] stack
        arr_stack[2] = 77;
        assert(arr_stack[2] == 77);
        cout << GREEN << "Operator [] (stack): OK"
             << RESET << endl;

        // resize stack
        arr_stack.resize(3);
        assert(arr_stack.size() == 3);
        cout << GREEN << "Resize smaller (stack): OK"
             << RESET << endl;

        // resize stack
        arr_stack.resize(5, 100);
        assert(arr_stack.size() == 5);
        assert(arr_stack[3] == 100);
        assert(arr_stack[4] == 100);
        cout << GREEN << "Resize larger within stack: OK"
             << RESET << endl;

        cout << YELLOW << "\n=== Testing ShortArray (heap storage) ==="
             << RESET << endl;
        ShortArray arr_heap(20, 55);

        // param constructor heap
        assert(arr_heap.size() == 20);

        for (size_t i = 0; i < arr_heap.size(); i++)
        {
            assert(arr_heap[i] == 55);
        }
        cout << GREEN << "Constructor with parameters (heap): OK"
             << RESET << endl;

        // push/pop heap
        arr_heap.push(123);
        assert(arr_heap.size() == 21);
        assert(arr_heap[20] == 123);

        val = arr_heap.pop();
        assert(val == 123);
        assert(arr_heap.size() == 20);
        cout << GREEN << "Push/pop (heap): OK"
             << RESET << endl;

        // [] heap
        arr_heap[10] = 777;
        assert(arr_heap[10] == 777);
        cout << GREEN << "Operator [] (heap): OK"
             << RESET << endl;

        // resize to stack
        arr_heap.resize(5);
        assert(arr_heap.size() == 5);
        cout << GREEN << "Resize to stack size: OK"
             << RESET << endl;

        // resize to heap
        arr_heap.resize(25, 200);
        assert(arr_heap.size() == 25);
        assert(arr_heap[24] == 200);
        cout << GREEN << "Resize back to heap: OK"
             << RESET << endl;

        // copy stack
        ShortArray arr_copy1(arr_stack);
        assert(arr_copy1.size() == arr_stack.size());
        for (size_t i = 0; i < arr_copy1.size(); i++)
        {
            assert(arr_copy1[i] == arr_stack[i]);
        }
        cout << GREEN << "Copy constructor (stack->stack): OK"
             << RESET << endl;

        // copy heap
        ShortArray arr_copy2(arr_heap);
        assert(arr_copy2.size() == arr_heap.size());
        for (size_t i = 0; i < arr_copy2.size(); i++)
        {
            assert(arr_copy2[i] == arr_heap[i]);
        }
        cout << GREEN << "Copy constructor (heap->heap): OK"
             << RESET << endl;

        // move stack
        ShortArray arr_move1(std::move(arr_stack));
        assert(arr_move1.size() == 5);
        assert(arr_stack.size() == 0);
        cout << GREEN << "Move constructor (stack): OK"
             << RESET << endl;

        // move heap
        ShortArray arr_move2(std::move(arr_heap));
        assert(arr_move2.size() == 25);
        assert(arr_heap.size() == 0);
        cout << GREEN << "Move constructor (heap): OK"
             << RESET << endl;

        cout << GREEN << "\n=== All tests passed successfully! ==="
             << RESET << endl;

        cout << BLUE << "Size of the ShortArray: " << sizeof(ShortArray) << RESET << endl;
    }
    cout << endl;

    /**
     * Задание 3.3. Выравнивание и битовые поля.
     *
     * Для того, чтобы различить, используется ли динамическая память, можно
     * использовать последний бит адреса динамически выделенного массива. Из-за
     * того, что используется тип short, этот адрес всегда будет делиться на 2
     * из-за выравнивания адресов. Таким образом, если самый младший бит будет
     * равен 1, то мы можем быть уверены, что динамическая память не
     * используется.
     *
     * С помощью битовых полей получите доступ к этому биту, а остальную часть
     * байта, в котором он находится, интерпретируйте как размер массива.
     *
     * Добейтесь, чтобы ваш класс работал, как в пункте 3.2, при этом его размер
     * был бы равен `sizeof(short *) + 2 * sizeof(size_t)`.
     */

    /**
     * Задание 4. Ассоциативный массив. Итератор. Операторы инкремента.
     */

    /**
     * Задание 4.1. Ассоциативный массив.
     *
     * Создайте класс `WorkerDb`, который будет хранить базу данных рабочих
     * некой организации в виде ассоциативного массива. В таком массиве индексом
     * является не номер элемента, а какое-то другое значение. В этом случае -
     * фамилия сотрудника. В самом же массиве будет храниться структура с
     * информацией о работнике.
     *
     * Реализуйте для этого класса оператор `[]`, который будет по фамилии
     * возвращать ссылку на данные работника. Если такого работника еще нет,
     * то запись для этого работника создается.
     *
     * Используйте для хранения строковых данных ваш класс MyString.
     */
    cout << endl;
    cout << PURPLE << "WorkerDb Task 4.1: " << RESET << endl;
    {
        WorkerDb db;
        db["Ivanov"] = WorkerData("Ivan", 34, 10000.0, "intern");
        db["Petrov"] = WorkerData("Petr", 43, 50000.0, "leader");
        std::cout << "Ivanov's name = " << db["Ivanov"].name << "\n";
        std::cout << "Petrov's age = " << db["Petrov"].age << "\n";
        std::cout << "Ivanov's salary: " << db["Ivanov"].salary << "\n";
        std::cout << "Petrov's postion: " << db["Petrov"].position << endl;
    }
    cout << endl;

    /**
     * Задание 4.2. Итератор.
     *
     * На практике воспользоваться таким классом будет довольно сложно, потому
     * что чтобы получить информацию о работниках, нужно откуда-то знать их
     * фамилии (ключи в массиве).
     *
     * Чтобы решить такую проблему, часто используют паттерн *итератор*.
     * Объект-контейнер (у нас - WorkerDb) умеет возвращать объект, который
     * перебирает его элементы. Для обычного массива в С таким объектом является
     * указатель, однако, сам по себе указатель не содержит информации, когда
     * элементы массива закончатся. Поэтому в пару к указателю, который
     * указывает на элементы (`begin`), добавляют указатель, который будет
     * обозначать, что элементы закончены (`end`):
     *
     * ```
     * int arr[] = {1, 2, 3, 4, 5};
     *
     * for (int *begin = arr, *end = arr + sizeof(arr) / sizeof(arr[0]);
     *      begin != end;
     *      ++begin)
     *  {
     *      std::cout << *begin << ' ';
     *  }
     *
     * ```
     *
     * В языке C++ наследуется эта идиома: объекты-контейнеры возвращают
     * объект-итератор методами `begin()` и `end()`. Для итератора определены
     * операторы `==`, `!=`, префиксный и постфиксный `++`, а также операторы
     * разыменования `*` и `->`. Также часто итераторы копируются (оператор
     * `=`).
     *
     * Реализуйте для вашего класса `WorkerDb` итератор, который при
     * разыменовании будет возвращать ссылку на `WorkerData`, а также иметь
     * метод `key()`, который будет возвращать ключ для этих данных
     * (фамилию). Итераторы допускается объявлять дружественными для
     * класса-контейнера.
     *
     * Проверьте ниже работу итератора.
     */
    cout << endl;
    {
        WorkerDb db;
        db["Ivanov"] = WorkerData("Ivan", 34, 10000.0, "intern");
        db["Petrov"] = WorkerData("Petr", 43, 50000.0, "leader");
        for (auto it = db.begin(); it != db.end(); ++it)
        {
            std::cout << it.key() << " -> " << it->name << '\n';
        }
    }
    cout << endl;

    /**
     * Задание 4.3. Работа "прикладного программиста".
     *
     * Не меняя класс `WorkerDb`, напишите функцию `print_db(WorkerDb&)`,
     * которая будет печатать базу данных работников на консоль, и функцию
     * `double get_avg_age(WorkerDb&)`, которая будет подсчитывать средний
     * возраст сотрудников. Эти функции не должны быть дружественными классу
     * `WorkerDb`.
     */
    cout << endl;
    {
        WorkerDb db;
        db["Ivanov"] = WorkerData("Ivan", 34, 10000.0, "intern");
        db["Petrov"] = WorkerData("Petr", 43, 50000.0, "leader");
        db["Sidorov"] = WorkerData("Sidor", 29, 30000.0, "developer");

        print_db(db);

        std::cout << CYAN << "Average age: " << get_avg_age(db) << RESET << "\n";
    }
    cout << endl;

    /**
     * Задание 5. Неявно определенные операторы. Удаление операторов.
     *
     * Проверьте, определен ли оператор присваивания для класса `BaseFile` из
     * работы 2? Что он делает? Имеется ли смысл в таком операторе?
     *
     * Явно удалите оператор присваивания и конструктор копирования ключевым
     * словом `delete`, но определите их move-аналоги в этом классе.
     * Продемонстрируйте их работу.
     */
    cout << endl;
    {
        cout << CYAN << "=== BaseFile Test===" << RESET << endl;

        cout << GREEN << "Creating file1 (test.txt)" << RESET << endl;
        BaseFile file1("test.txt", "w+");
        file1.write_raw("Hello", 5);
        cout << "file1 is_open: " << file1.is_open() << endl;

        cout << YELLOW << "\nUsing move constructor (file2 = std::move(file1))" << RESET << endl;
        BaseFile file2(std::move(file1));

        cout << "file1 is_open after move: " << file1.is_open() << endl;
        cout << "file2 is_open: " << file2.is_open() << endl;
        cout << "Position in file2: " << file2.tell() << endl;

        cout << YELLOW << "\nCreating file3 (temp.txt)" << RESET << endl;
        BaseFile file3("temp.txt", "w+");

        cout << YELLOW << "Using move assignment (file3 = std::move(file2))" << RESET << endl;
        file3 = std::move(file2);

        cout << "file2 is_open after move: " << file2.is_open() << endl;
        cout << "file3 is_open: " << file3.is_open() << endl;
        cout << "Position in file3: " << file3.tell() << endl;

        cout << YELLOW << "\nReading data from file3:" << RESET << endl;
        file3.seek(0);
        char buffer[6] = {0};
        size_t read = file3.read_raw(buffer, 5);
        cout << "Read " << read << " bytes: " << buffer << endl;

        cout << CYAN << "\n=== Test Complete ===" << RESET << endl;
    }
    cout << endl;

    /**
     * Задание 6. Оператор неявного приведения типа.
     *
     * Реализуйте класс `BoolArray`, представляющий динамический массив
     * логических значений (тип bool). В наивной реализации (`new bool[n]`) есть
     * проблема: каждая переменная типа bool занимает 1 байт, то есть 8 бит, в
     * то время как она могла бы занимать 1 бит.
     *
     * Реализуйте этот класс таким образом, чтобы каждое значение значений
     * действительно занимало 1 бит (точнее сказать, чтобы n значений занимали
     * не более ceil(n / 8), где ceil - целая часть числа с округлением вверх).
     *
     * Класс должен поддерживать следующее поведение:
     */
    cout << endl;
    cout << PURPLE << "BoolArray Task: " << RESET << endl;
    {
        /// Создается массив из 10 значений false
        BoolArray ar1(10);

        /// Создается массив из 5 значений true
        BoolArray ar2(5, true);

        /// Создается независимая копия `ar2`
        BoolArray ar3(ar2);

        /// 4 и 6 элементу (нумерация с 0) устанавливаются заданное значение
        ar1[4] = ar1[6] = true;

        /// Над полученными значениями выполняем логические операции
        ar1[2] = ((!ar1[6] && ar1[8]) || (ar1[0] != true));

        /// Выведем массив на печать
        std::cout << "[";
        for (size_t i = 0; i < ar1.size(); ++i)
        {
            if (i > 0)
                std::cout << ", ";
            std::cout << ar1[i];
        }
        std::cout << "]\n";

        /// Выведем массив на печать по-другому
        std::cout << "[";
        for (size_t i = 0, printed = 0; i < ar1.size(); ++i)
        {
            if (ar1[i])
            {
                if (printed++ > 0)
                    std::cout << ", ";
                std::cout << i;
            }
        }
        std::cout << "]\n";

        /// Метод `resize` изменяет размер массива. Если новый размер больше, то
        /// новые значения дополняются заданным значением (по умолчанию false). Если
        /// новый размер меньше, то конец массива отбрасывается.

        ar1.resize(12, true);
        /// выведите массив на печать

        std::cout << "[";
        for (size_t i = 0; i < ar1.size(); ++i)
        {
            if (i > 0)
                std::cout << ", ";
            std::cout << ar1[i];
        }
        std::cout << "]\n";

        ar1.resize(4, true);
        /// выведите массив на печать снова

        std::cout << "[";
        for (size_t i = 0; i < ar1.size(); ++i)
        {
            if (i > 0)
                std::cout << ", ";
            std::cout << ar1[i];
        }
        std::cout << "]\n";
    }
    cout << endl;

    return 0;
}
