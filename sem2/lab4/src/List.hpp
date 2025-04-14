#include "Circle.hpp"
#include <iostream>
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

public:
    void add_head(const Circle &circle);
    void add_tail(const Circle &circle);
};
