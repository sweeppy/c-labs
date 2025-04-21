#include "List.hpp"

List::Node::~Node()
{
    if (pPrev)
        pPrev->pNext = pNext;
    if (pNext)
        pNext->pPrev = pPrev;
}

List::Node *List::split(Node *head)
{
    Node *slow = head;        // * moving per 1
    Node *fast = head->pNext; // * moving per 2

    while (fast != &Tail && fast->pNext != &Tail)
    {
        slow = slow->pNext;
        fast = fast->pNext->pNext;
    }

    Node *second_half = slow->pNext;
    slow->pNext = &Tail; // * broke relations in center into 2 parts
    return second_half;
}

List::Node *List::merge(Node *left, Node *right)
{
    if (left == &Tail)
        return right;
    if (right == &Tail)
        return left;

    if (left->m_Data.get_square() <= right->m_Data.get_square())
    {
        left->pNext = merge(left->pNext, right);
        left->pNext->pPrev = left;
        left->pPrev = nullptr;
        return left;
    }
    else
    {
        right->pNext = merge(left, right->pNext);
        right->pNext->pPrev = right;
        right->pPrev = nullptr;
        return right;
    }
}

List::Node *List::merge_sort(Node *head)
{
    if (head == &Tail || head->pNext == &Tail)
        return head; // * List is empty or only 1 element

    Node *second_half = split(head);

    // * Sorting both parts
    head = merge_sort(head);
    second_half = merge_sort(second_half);

    return merge(head, second_half);
}

List::List() : Head(), Tail(), m_size(0)
{
    Head.pNext = &Tail;
    Tail.pPrev = &Head;
}

List::~List()
{
    clear();
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

    // * Update tail
    Tail.pPrev->pNext = new_node;
    Tail.pPrev = new_node;

    m_size++;
}

bool List::remove_first(const Circle &target)
{
    Node *current_node = Head.pNext;
    while (current_node != &Tail)
    {
        Node *next_node = current_node->pNext;
        if (current_node->m_Data == target)
        {
            delete current_node;
            m_size--;
            return true;
        }
        current_node = next_node;
    }
    return false;
}

unsigned int List::remove_all(const Circle &target)
{
    unsigned int count = 0;
    Node *current_node = Head.pNext;
    while (current_node != &Tail)
    {
        Node *next_node = current_node->pNext;
        if (current_node->m_Data == target)
        {
            delete current_node;
            m_size--;
            count++;
        }
        current_node = next_node;
    }
    return count;
}

void List::clear()
{
    Node *current_node = Head.pNext;
    while (current_node != &Tail)
    {
        Node *next_node = current_node->pNext;
        delete current_node;
        current_node = next_node;
    }
    Head.pNext = &Tail;
    Tail.pPrev = &Head;
    m_size = 0;
}

void List::sort_by_square()
{
    if (Head.pNext == &Tail || Head.pNext->pNext == &Tail)
        return; // * nothing to sort (1 or 0 elements)

    Node *newHead = merge_sort(Head.pNext);

    // * Update Head
    Head.pNext = newHead;
    newHead->pPrev = &Head;

    // * Update Tail
    Node *current = newHead;
    while (current->pNext != &Tail)
    {
        current = current->pNext;
    }
    Tail.pPrev = current;
    current->pNext = &Tail;
}

void List::print(std::ostream &os) const
{
    Node *current = Head.pNext;
    os << "-------------------------\n";
    while (current != &Tail)
    {
        os << current->m_Data << "\n-------------------------\n";
        current = current->pNext;
    }
}

void List::read_from_file(const char *filename)
{
    std::ifstream fin(filename);
    if (!fin)
        throw std::runtime_error("Error was occurred while trying to read from file");

    clear(); // * clear current list

    Circle temp;
    while (fin >> temp)
    {
        add_tail(temp);
    }

    fin.close();
}

std::ostream &operator<<(std::ostream &os, const List &list)
{
    list.print(os);
    return os;
}
