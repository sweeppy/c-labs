#include "workerDb.hpp"
#include "colors.hpp"

// * private:
void WorkerDb::clear()
{
    while (head)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

WorkerDb::Iterator WorkerDb::begin()
{
    return Iterator(head);
}

WorkerDb::Iterator WorkerDb::end()
{
    return Iterator(nullptr);
}

// * public:

WorkerDb::~WorkerDb()
{
    clear();
}

WorkerData &WorkerDb::operator[](const MyString &key)
{
    Node *current = head;
    while (current)
    {
        if (current->key == key)
        {
            return current->data;
        }
        current = current->next;
    }

    Node *newNode = new Node(key, WorkerData(), head);
    head = newNode;
    size++;
    return newNode->data;
}

bool WorkerDb::Iterator::operator==(const Iterator &other) const
{
    return current == other.current;
}

bool WorkerDb::Iterator::operator!=(const Iterator &other) const
{
    return !(*this == other);
}

WorkerDb::Iterator &WorkerDb::Iterator::operator++()
{
    if (current)
    {
        current = current->next;
    }
    return *this;
}

WorkerDb::Iterator WorkerDb::Iterator::operator++(int)
{
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

WorkerData &WorkerDb::Iterator::operator*()
{
    return current->data;
}

WorkerData *WorkerDb::Iterator::operator->()
{
    return &current->data;
}

const MyString &WorkerDb::Iterator::key() const
{
    return current->key;
}

void print_db(WorkerDb &db)
{
    std::cout << PURPLE << "Worker Database:" << RESET << std::endl;
    std::cout << "---------------------------\n";
    for (auto it = db.begin(); it != db.end(); ++it)
    {
        std::cout
            << CYAN << "Name: " << RESET << it->name << "\n"
            << CYAN << "Surname :" << RESET << it.key() << "\n"
            << CYAN << "Age :" << RESET << it->age << "\n"
            << CYAN << "Salary :" << RESET << it->salary << "\n"
            << CYAN << "Position :" << RESET << it->position << "\n"
            << "---------------------------\n";
    }
}
double get_avg_age(WorkerDb &db)
{
    double ages_sum = 0;
    double workers_count = 0;
    for (auto it = db.begin(); it != db.end(); ++it)
    {
        ages_sum += it->age;
        workers_count++;
    }
    return ages_sum / workers_count;
}

void print_times(char value, size_t times)
{
    for (size_t i = 0; i < times; ++i)
    {
        std::cout << value;
    }
}

void align_print(MyString string)
{
    std::cout << string;
}
