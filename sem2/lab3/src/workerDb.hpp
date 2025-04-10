#include "string.hpp"

struct WorkerData
{
    MyString name;
    int age;
    float salary;
    MyString position;

    WorkerData(const MyString &_name = MyString("none"), int _age = 0,
               float _salary = 0.0, const MyString &_position = MyString("none"))
        : name(_name), age(_age), salary(_salary), position(_position) {}
};

class WorkerDb
{
private:
    struct Node
    {
        MyString key;
        WorkerData data;
        Node *next;
        Node(const MyString &_key, const WorkerData &_data, Node *_next = nullptr)
            : key(_key), data(_data), next(_next) {}
    };

    Node *head;
    size_t size;

public:
    WorkerDb() : head(nullptr), size(0) {}

    ~WorkerDb();

    WorkerData &operator[](const MyString &key);
    void clear();

    class Iterator
    {
    private:
        Node *current;

    public:
        Iterator(Node *node) : current(node) {}

        bool operator==(const Iterator &other) const;
        bool operator!=(const Iterator &other) const;

        Iterator &operator++();
        Iterator operator++(int);

        WorkerData &operator*();
        WorkerData *operator->();

        const MyString &key() const;
    };

    Iterator begin();
    Iterator end();
};

void print_db(WorkerDb &db);
double get_avg_age(WorkerDb &);