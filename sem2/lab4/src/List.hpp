#include <iostream>
#include <fstream>

#include "Circle.hpp"
#include "colors.hpp"
class List
{
private:
    class Node
    {
    private:
        Node *pPrev;
        Node *pNext;
        Circle m_Data;

    public:
        Node() : pPrev(nullptr), pNext(nullptr), m_Data(Circle()) {}
        Node(Node *pPrev, Node *pNext, const Circle *pc) : pPrev(pPrev), pNext(pNext), m_Data(*pc) {}
        ~Node();

        friend class List;
    };

    Node Head;
    Node Tail;

    size_t m_size;

    // * For sorting
    Node *split(Node *head);
    Node *merge(Node *left, Node *right);
    Node *merge_sort(Node *head);

public:
    List();
    ~List();

    void add_head(const Circle &circle);
    void add_tail(const Circle &circle);

    bool remove_first(const Circle &target);
    unsigned int remove_all(const Circle &target);

    void clear();

    void sort_by_square();

    void print(std::ostream &os) const;

    void read_form_file(const char *filename);
};

std::ostream &operator<<(std::ostream &os, const List &list);
