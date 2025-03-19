/**
 * Лабораторная работа №2. Массивы объектов, простое наследование, виртуальные
 * функции, применение наследования.
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
#include <iostream>

#include "string.hpp"
#include "file.hpp"
#include "colors.hpp"
#include "file2.hpp"

using std::cout;
using std::endl;

int main()
{
    /**
     * Задание 1. Массивы объектов класса.
     */

    /**
     * Задание 1.1. Массив объектов.
     *
     * Объявите и проинициализируйте массив ar из объектов типа MyString.
     * Выведите элементы массива на консоль.
     */
    cout << endl;
    {
        MyString ar[5] = {
            MyString("First string"),
            MyString("Second string"),
            MyString("Third string"),
        };
        for (int i = 0; i < 3; ++i)
        {
            cout << ar[i].get_data() << std::endl;
        }
    }
    cout << endl;

    /**
     * Замените размер массива с 3 на 5, не меняя список инициализаторов.
     *
     * Чем были инициализированы последние 2 элемента? Какие значения могут
     * стоять в списке инициализаторов - в вашем случае и в общем случае?
     */

    /*
        Последние два элемента будут инициализированы значением из конструктора
        по умолчанию. В списке инициализаторов могут стоять любые конструкторы,
        которые заданы в классе string.
    */

    /**
     * Задание 1.2. Массив указателей на объекты.
     *
     * Объявите и проинициализируйте массив arPtr из трех указателей на объекты
     * типа MyString. Выведите элементы массива на консоль.
     */

    cout << endl;
    {
        MyString *atPtr[3];

        atPtr[0] = new MyString("First");
        atPtr[1] = new MyString("Second");
        atPtr[2] = new MyString("Third");

        for (int i = 0; i < 3; i++)
        {
            cout << atPtr[i]->get_data() << endl;
        }

        for (int i = 0; i < 3; i++)
        {
            delete atPtr[i];
            atPtr[i] = nullptr;
        }
    }
    cout << endl;

    /**
     * Задание 2. Простое наследование. Аргументы конструктора, передаваемые в
     * базовый класс.
     */

    /**
     * Задание 2.1. Базовый класс.
     *
     * Создайте класс BaseFile, который будет реализовывать работу с файлами с
     * помощью стандартных средств C (cstdio).
     *
     * Класс должен иметь 3 конструктора: первый - конструктор по умолчанию,
     * второй должен принимать путь к файлу и параметры для открытия (как в
     * fopen), третий должен принимать готовый указатель FILE*.
     *
     * Считается, что этот класс *обладает* своим ресурсом - открытым файлом.
     * Что должно быть в деструкторе этого класса?
     *
     * Добавьте следующие методы:
     * - bool is_open() - возвращает true, если файл успешно открыт;
     * - bool can_read() - возвращает true, если из файла можно считать данные;
     * - bool can_write() - возвращает true, если в файл можно записать данные;
     * - size_t write_raw(const void *buf, size_t n_bytes) - записывает
     *   указанное количество байт в файл и возвращает количество байт, которое
     *   удалось записать;
     * - size_t read_raw(void *buf, size_t max_bytes) - читает доступные данные
     *   в буфер, но не более указанного количества и возвращает количество
     *   байт, которое удалось считать;
     * - long tell() - возвращает текущий сдвиг файла (см. функцию ftell);
     * - bool seek(long offset) - устанавливает сдвиг файла (см. функцию fseek)
     *   и возвращает true, если операция успешна.
     *
     * Добавьте также методы `read` и `write`, которые в этом классе будут
     * делать буквально то же, что `read_raw` и `write_raw`, они понадобятся нам
     * позже.
     *
     * Проверьте работу этого класса.
     */
#define FILENAME "txt_files/test.txt"
    cout << endl;
    {
        try
        {
            BaseFile file(FILENAME, "w");
            if (file.is_open())
            {
                cout << "File <" << BLUE << FILENAME << RESET << "> is open for writing\n";
            }

            const char *data = "My test text";
            size_t written = file.write_raw(data, strlen(data));
            cout << "Written " << written << " bytes in <"
                 << BLUE << FILENAME << RESET << ">" << endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << RED << e.what() << RESET << '\n';
        }

        try
        {
            BaseFile file(FILENAME, "r");
            if (file.is_open())
            {
                cout << "File <" << BLUE << FILENAME << RESET << "> is open for reading\n";
            }
            char buffer[100];
            size_t read = file.read_raw(buffer, sizeof(buffer));
            buffer[read] = '\0';
            cout << "Read: " << read << " bytes in <"
                 << BLUE << FILENAME << RESET << ">" << endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << RED << e.what() << RESET << '\n';
        }
    }
    cout << endl;

    /**
     * Задание 2.2. Производные классы.
     *
     * Производный класс *наследуется* от базового класса и каким-то образом
     * расширяет его функциональность, при этом все еще умея все, что умеет
     * базовый класс.
     *
     * Реализуйте следующие производные классы от класса BaseFile. Производные
     * классы нужно унаследовать так, чтобы пользователю были все еще доступны
     * методы базового класса. Каким образом нужно унаследовать класс для этого?
     * Как еще можно унаследовать класс?
     *
     * Производные классы могут располагаться в том же файле, где и базовый
     * класс.
     *
     * В производных классах добавьте необходимые конструкторы, которые будут
     * вызывать конструктор базового класса.
     *
     * Проверьте работу производных классов.
     */
    // * Можно унаследовать private | protected | public | virtual
    /**
     * Задание 2.2.1. Base32 кодировщик/декодировщик.
     *
     * Создайте производный класс Base32File, который будет проводить при
     * записи кодировку-декодировку данных, по алгоритму, который вы
     * реализовали в лабораторной работе №4 прошлого семестра.
     *
     * Переопределите методы `read` и `write`, которые будут проводить чтение из
     * файла с декодировкой и запись в файл с кодировкой соответственно.
     *
     * Добавьте возможность пользователю передать в конструктор таблицу
     * кодировки, по умолчанию используется таблица "A..Z1..6".
     */

    cout << endl;
    {

        const char *testData = "Just one sentence.";
        size_t testDataSize = strlen(testData);

        Base32File base32File("txt_files/codeFile.txt", "w+");

        try
        {
            size_t bytesWritten = base32File.write(testData, testDataSize);
            std::cout << "Bytes written: " << bytesWritten << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << RED << "Error during write: " << e.what() << RESET << std::endl;
        }

        base32File.seek(0);

        char readBuffer[100] = {0};

        try
        {
            size_t bytesRead = base32File.read(readBuffer, sizeof(readBuffer));
            std::cout << "Bytes read: " << bytesRead << ". Data: " << BLUE << readBuffer << RESET << std::endl;
            std::cout << "Decoded data: " << readBuffer << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << RED << "Error during read: " << e.what() << RESET << std::endl;
        }

        if (strcmp(testData, readBuffer) == 0)
        {
            std::cout << GREEN << "Test passed: Data matches!" << RESET << std::endl;
        }
        else
        {
            std::cerr << RED << "Test failed: Data does not match!" << RESET << std::endl;
        }
    }
    cout << endl;

    /**
     * Задание 2.2.2. RLE-сжатие.
     *
     * Создайте производный класс RleFile, который будет проводить побайтовое
     * сжатие при помощи алгоритма RLE (для простоты можно реализовать
     * неэффективный алгоритм, где последовательности без повторений отдельно
     * не кодируются).
     *
     * Переопределите методы `read` и `write`, которые будут проводить чтение из
     * файла с извлечением сжатой информации и запись в файл со сжатием
     * соответственно.
     *
     * Проверьте сжатие/извлечение на примере какого-нибудь ASCII-арта,
     * например, котенка из лабораторной №3 прошлого семестра. Посмотрите,
     * получилось ли добиться уменьшения размера хранимых данных.
     */
    cout << endl;
    {
        const char *asciiArt =
            "            _____________________________________\n"
            "           / Here user input is shown. This line \\\n"
            "           \\ must be at most 40 characters long. /\n"
            "            ------------------------------------\n"
            "               \\\n"
            "                \\\n"
            "                  /\\_/\\  (\n"
            "                 ( ^.^ ) _)\n"
            "                   \\\"/  (\n"
            "                 ( | | )\n"
            "                (__d b__)\n";
        size_t testDataSize = strlen(asciiArt);

        RleFile RLE_file("txt_files/RleFile.txt", "w+");

        size_t bytesWritten = RLE_file.write(asciiArt, testDataSize);
        std::cout << "Bytes written: " << bytesWritten << std::endl;

        RLE_file.seek(0);

        char buffer[300];
        size_t bytesRead = RLE_file.read(buffer, sizeof(buffer));
        std::cout << "Bytes read: " << bytesRead << ". Data: \n"
                  << BLUE << buffer << RESET << std::endl;

        if (std::strcmp(asciiArt, buffer) == 0)
        {
            std::cout << GREEN << "Test passed: Data matches!" << RESET << std::endl;
        }
        else
        {
            std::cerr << RED << "Test failed: Data does not match!" << RESET << std::endl;
        }
    }
    cout << endl;

    // Получилось исходные 369 байт сжать до 174 байт.

    /**
     * Задание 2.3. Конструкторы и деструкторы базового и производного классов.
     *
     * Установите отладочную печать в конструкторах и деструкторах каждого
     * класса из этого задания. Создайте локальные объекты производных классов,
     * отметьте, в каком порядке вызываются конструкторы и деструкторы при
     * инициализации и деинициализации этих классов.
     */
    cout << endl;
    {
        std::cout << "Creating Base32File object..." << std::endl;
        {
            Base32File base32File("txt_files/testDerivedClasses/b32.txt", "w+");
        }
        std::cout << "Base32File object destroyed." << std::endl;

        std::cout << "\nCreating RleFile object..." << std::endl;
        {
            RleFile rleFile("txt_files/testDerivedClasses/rle.txt", "w+");
        }
        std::cout << "RleFile object destroyed." << std::endl;
    }
    cout << endl;

    /*
     Creating Base32File object...
    *   BaseFile parameterized constructor (with path and mode) called for object: 0x16d7e6ab0
    *   Base32File parameterized constructor called for object: 0x16d7e6ab0
    *   Base32File destructor called for object: 0x16d7e6ab0
    *   BaseFile destructor called for object: 0x16d7e6ab0
     Base32File object destroyed.
    */

    /*
     Creating RleFile object...
    *  BaseFile parameterized constructor (with path and mode) called for object: 0x16d6daaa0
    *  RleFile parameterized constructor called for object: 0x16d6daaa0
    *  RleFile destructor called for object: 0x16d6daaa0
    *  BaseFile destructor called for object: 0x16d6daaa0
     RleFile object destroyed.
    */

    /**
     * Задание 2.4. Ранее связывание.
     *
     * На основе данной заготовки напишите код, который запишет в файл строковое
     * представление целого числа. Вы должны использовать один и тот же код для
     * всех файлов, меняя только имя объекта (bf / b32f / rf), в который идет
     * запись.
     */

    {
        BaseFile bf("txt_files/numbers1/bf.txt", "w+");
        Base32File b32f("txt_files/numbers1/b32f.txt", "w+");
        RleFile rf("txt_files/numbers1/rf.txt", "w+");

        int n = 123456;
        if (n < 0 && n != 0)
        {
            rf.write("-", 1);
            n = -n;
        }

        int count = (n == 0) ? 1 : 0;
        for (int temp = n; temp > 0; temp /= 10)
        {
            count++;
        }
        while (n > 0)
        {
            int first_number = static_cast<char>(n / static_cast<int>(std::pow(10, count - 1)));
            char digit = first_number + '0';
            bf.write(&digit, 1);
            n = n - first_number * (pow(10, count - 1));
            count--;
        }

        n = 123456;
        if (n < 0 && n != 0)
        {
            rf.write("-", 1);
            n = -n;
        }

        count = (n == 0) ? 1 : 0;
        for (int temp = n; temp > 0; temp /= 10)
        {
            count++;
        }
        while (n > 0)
        {
            int first_number = static_cast<char>(n / static_cast<int>(std::pow(10, count - 1)));
            char digit = first_number + '0';
            b32f.write(&digit, 1);
            n = n - first_number * (pow(10, count - 1));
            count--;
        }

        n = 123456;
        if (n < 0 && n != 0)
        {
            rf.write("-", 1);
            n = -n;
        }

        count = (n == 0) ? 1 : 0;
        for (int temp = n; temp > 0; temp /= 10)
        {
            count++;
        }

        while (n > 0)
        {
            int first_number = static_cast<char>(n / static_cast<int>(std::pow(10, count - 1)));
            char digit = first_number + '0';
            rf.write(&digit, 1);
            n = n - first_number * (pow(10, count - 1));
            count--;
        }
    }

    /**
     * Задание 2.5. Передача объекта по ссылке / указателю.
     *
     * Прошлое задание выглядит странновато - зачем повторять код три раза?
     * Хорошо бы сделать функцию, которая примет объект файла и число, и
     * выполнит эти действия.
     *
     * Реализуйте функцию `write_int(BaseFile &file, int n)`, которая будет
     * принимать ссылку на файл и число, которое нужно будет напечатать.
     *
     * Принцип наследования предписывает, что везде, где можно использовать
     * базовый класс, можно использовать производный класс. Проверьте, можно
     * ли вызвать функцию, передав в нее объект класса Base32File и RleFile.
     *
     * Имеет ли вызов этой функции для производного класса тот же результат,
     * что и код, который вы написали выше? Почему?
     */

    {
        int n = -123456;
        BaseFile bf("txt_files/numbers2/bf.txt", "w+");
        Base32File b32f("txt_files/numbers2/b32f.txt", "w+");
        RleFile rf("txt_files/numbers2/rf.txt", "w+");

        write_int(bf, n);
        write_int(b32f, n);
        write_int(rf, n);
    }
    /*
        Результат отличается. В данном случае для каждого из фалов будет вызван
        write(...) из BaseFile. Это происходит из-за того, что метод write(...)
        объявлен в BaseFile без ключевого слова virtual, что приводит к выполнению
        write(...) из базового класса, при передачи производного класса по ссылке.
        То есть выбор реализации функции определяется не типом объекта, а типом указателя.
    */

    /**
     * Задание 2.6. Виртуальные функции, позднее связывание.
     *
     * Объявите функции read и write в базовом классе *виртуальными*. Что это
     * означает? Как изменился размер объектов классов BaseFile, Base32File и
     * RleFile? Почему?
     *
     * Как изменилось поведение при вызове функции `write_int` для производных
     * классов? Почему?
     */
    /*
        Если метод не виртуальный, то компилятор выполняет статическое связывание.
        Это означает, что вызываемый метод определяется на этапе компиляции, исходя
        из типа указателя или ссылки.

        Если метод виртуальный, то компилятор выполняет динамическое связывание.
        Это означает, что вызываемый метод определяется на этапе выполнения,
        исходя из реального типа объекта.

        При объявлении виртуальных функций в классе, компилятор добавляет
        в объект этого класса указатель на таблицу виртуальных функций (vtable).
        Это увеличивает размер объекта на размер указателя. (В моем случа на 8 байт).

        Теперь при вызове функции `write_int` все работает правильно, так как
        функция write переопределяется и выполняется своя реализация для каждого
        объекта класса.
    */

    /**
     * Задание 2.7. Виртуальный деструктор.
     *
     * В следующем блоке кода добавьте удаление динамической памяти.
     *
     * Какой деструктор при этом вызывается? Почему? К каким проблемам это может
     * привести?
     *
     * Исправьте эту ситуацию.
     */
    cout << endl;
    {
        BaseFile *files[] = {
            new BaseFile("txt_files/destructors/bf.txt", "w+"),
            new Base32File("txt_files/destructors/b32f.txt", "w+"),
            new RleFile("txt_files/destructors/rf.txt", "w+"),
        };

        for (int i = 0; i < 3; ++i)
        {
            files[i]->write("Hello!", 6);
        }

        for (int i = 0; i < 3; i++)
        {
            delete files[i];
        }
    }
    cout << endl;

    /*
        Без виртуального деструктора деструктор будет вызван только у базового класса,
        у производных классов деструкторы вызваны не будут. Поэтому, если производные
        классы выделяют дополнительные ресурсы и освобождают их в своем деструкторе,
        то без виртуального деструктора могут быть проблемы с утечками.
    */

    /**
     * Задание 2.8. Массив объектов производных классов.
     *
     * Раскомментируйте следующий блок и объясните, почему:
     * а) не возникает ошибок при компиляции;
     * б) возникают ошибки при выполнении.
     *
     * Этот пример показывает очень плохую практику, которая приводит к ошибкам;
     * для создания массива объектов производного класса и используйте массив
     * указателей на базовый класс, как это было сделано выше. Реализуйте ту же
     * логику, используя массив указателей на объекты базового класса.
     */
    cout << endl;
    {
        BaseFile *base_files = new BaseFile[2];
        base_files[0] = BaseFile("txt_files/wrongArray/bf1.txt", "w+");
        base_files[1] = BaseFile("txt_files/wrongArray/bf2.txt", "w+");

        Base32File *b32_files = new Base32File[2];
        b32_files[0] = Base32File("txt_files/wrongArray/b32f1.txt", "w+");
        b32_files[1] = Base32File("txt_files/wrongArray/b32f2.txt", "w+");
        for (int i = 0; i < 2; ++i)
        {
            base_files[i].write("Hello!", 6);
            b32_files[i].write("Hello!", 6);
        }
        delete[] base_files;
        delete[] b32_files;
    }
    cout << endl;

    /*
    a)  Компиляция происходит, потому что BaseFile это конкретный класс и компилятор
        знает как выделить под него память, ровно так же как и Base32File. однако
        в случае Base32File компилятор предполагает, что каждый элемент имеет размер
        BaseFile; это может привести к проблемам.

    б)  Ошибки которые происходят: во-первых запись в файлы не происходят, так как
        создаются временные объекты BaseFile и Base32File, которые после копирования
        в элементы массива удаляются. Во-вторых в случае Base32File будут ошибки при
        попытке доступа к его полям, которых нет у BaseFile. В-третьих компилятор будет
        использовать статическое связывание, т.е. будет вызываться реализация методов
        BaseFile, даже если они будут переопределены в Base32File;
    */

    // Исправленный код:
    cout << endl;
    {
        BaseFile *base_files[] = {
            new BaseFile("txt_files/array/bf1.txt", "w+"),
            new BaseFile("txt_files/array/bf2.txt", "w+")};
        BaseFile *base32_files[] = {
            new Base32File("txt_files/array/b32f1.txt", "w+"),
            new Base32File("txt_files/array/b32f2.txt", "w+")};

        for (int i = 0; i < 2; i++)
        {
            base_files[i]->write("Hello!", 6);
            base32_files[i]->write("Hello!", 6);
        }

        for (int i = 0; i < 2; i++)
        {
            delete base_files[i];
            delete base32_files[i];
        }
    }
    cout << endl;

    /**
     * Задание 3. Чисто виртуальные функции. Интерфейсы. Композиция классов.
     *
     * Наследование позволяет довольно просто переиспользовать данные и логику
     * других классов, однако зачастую этот механизм недостаточно гибкий для
     * полноценного переиспользования.
     *
     * Например, сможем ли мы в получившейся иерархии классов реализовать
     * одновременно и кодирование в base32, и сжатие при записи данных в файл?
     * Или сможем ли мы вместо записи в файл на диске делать запись в строковый
     * буфер в памяти?
     *
     * При дальнейшем рассмотрении окажется, что при помощи наследования мы
     * крепко *связали* логику преобразования данных с записью в конкретный
     * файл. Далее мы рассмотрим один из способов разделения такой логики.
     */

    /**
     * Задание 3.1. Абстрактный базовый класс, чисто виртуальные функции.
     *
     * Первая проблема в нашей реализации - все наследники BaseFile будут всегда
     * обязаны непосредственно писать в файл на диске. Чтобы избавиться от этой
     * необходимости, стоит сделать базовый класс *абстрактным* в том смысле,
     * что у него не будет полей связанных с конкретным способом писать в файл.
     *
     * Создайте класс `IFile`, в котором не будет полей, но будут методы
     * `can_read`, `can_write`, `read` и `write` с такими же сигнатурами, как и
     * классе `BaseFile`. Что именно будут делать эти методы? Класс `IFile` не
     * может знать, поскольку логику этих методов будут определять наследники.
     * В этом классе эти методы не имеют реализации, и они должны быть объявлены
     * *чисто виртуальными*.
     *
     * Какие ограничения накладывает на класс наличие чисто виртуального метода?
     *
     * Получается, что в классе `IFile` есть только чисто виртуальные методы, и
     * единственная цель такого класса - определять, что должны уметь делать его
     * наследники. Совокупность действий, которые можно сделать с объектом,
     * называется его *интерфейсом*, и такие классы тоже часто называются
     * интерфейсами, отсюда берется приставка "I" в имени класса.
     *
     * Унаследуйте класс `BaseFile` от класса `IFile` и измените функцию
     * `write_int`, чтобы она работала с произвольным наследником `IFile`.
     *
     * Убедитесь, что в программе выше ничего не сломалось.
     */

    /**
     * Задание 3.2. Композиция вместо наследования.
     *
     * Реализуйте классы `Base32File2` и `RleFile2`, которые будут унаследованы
     * от класса `IFile` и в конструкторе будут получать другой объект `IFile`,
     * чьи функции они будут использовать вместо функций базового класса.
     *
     * Объекты получают объект `IFile` в виде указателя на динамически
     * выделенную память, и они ответственны за ее очищение.
     *
     * Использование объектом другого объекта в качестве поля называется
     * *композицией*.
     *
     * Проверьте, что используемые ниже объекты работают так же, как объекты
     * классов `Base32File` и `RleFile`.
     */
    cout << endl;
    {
        Base32File2 b32f(new BaseFile("txt_files/composition/b32fv2.txt", "w+"));
        RleFile2 rf(new Base32File("txt_files/composition/rleFv2.txt", "w+"));
        write_int(b32f, 123456);
        write_int(rf, 123456);
    }
    cout << endl;
    /* {
        Base32File2 b32f(new BaseFile(...));
        RleFile2 rf(new Base32File(...));
        write_int(b32f, 123456);
        write_int(rf, 123456);
    } */

    /**
     * Задание 3.3. Больше композиции!
     *
     * Не реализовывая больше никаких классов, соорудите объект-наследник IFile,
     * который будет при вызове метода `write` два раза кодировать в base32,
     * после чего применять сжатие RLE и только после этого писать в файл.
     */

    {
        IFile *file = new Base32File2(
            new Base32File2(
                new RleFile2(
                    new BaseFile("txt_files/composition/more_composition.txt", "w+"))));
        file->write("Hello!", 6);
        delete file;

        // Decode and print information from file to terminal
        file = new Base32File2(
            new Base32File2(
                new RleFile2(
                    new BaseFile("txt_files/composition/more_composition.txt", "r"))));
        char buf[100];
        file->read(buf, 99);
        cout << buf << endl;
        delete file;
    }

    return 0;
}
