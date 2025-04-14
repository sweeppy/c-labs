#include "List.hpp"

List::Node::~Node()
{
    if (pPrev)
        pPrev->pNext = pNext;
    if (pNext)
        pNext->pPrev = pPrev;
}

void List::add_head(const Circle &circle)
{
    Node *new_node = new Node(&Head, Head.pNext, &circle);
    // * set for old 1st element new_node before it
    Head.pNext->pPrev = new_node;
    // * set for Head that new_node is first element(1st after Head)
    Head.pNext = new_node;
    m_size++;
}

void List::add_tail(const Circle &circle)
{
    Node *new_node = new Node(Tail.pPrev, &Tail, &circle);
    // * set for old last element new_node after it
    Tail.pPrev->pNext = new_node;
    // * set for Tail that new_node is last element (before Tail)
    Tail.pPrev = new_node;
    m_size++;
}
