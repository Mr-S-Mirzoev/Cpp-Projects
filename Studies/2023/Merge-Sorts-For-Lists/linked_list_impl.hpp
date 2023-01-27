#include "linked_list.hpp"

#include <iostream>
#include <ranges>
#include <utility>

template <typename DataType>
LinkedList<DataType>::Node::Node(const DataType& value, Node *next)
    : value(value), next(next)
{
}

template <typename DataType>
LinkedList<DataType>::Node::Node(DataType&& value, Node *next)
    : value(std::move(value)), next(next)
{
}

template <typename DataType>
LinkedList<DataType>::Iterator::Iterator(Node *ptr)
    : ptr(ptr)
{
}

template <typename DataType>
inline typename LinkedList<DataType>::Iterator& LinkedList<DataType>::Iterator::operator++(int)
{
    ptr = ptr->next;
    return *this;
}

template <typename DataType>
inline typename LinkedList<DataType>::Iterator& LinkedList<DataType>::Iterator::operator++()
{
    ptr = ptr->next;
    return *this;
}

template <typename DataType>
inline DataType& LinkedList<DataType>::Iterator::operator*()
{
    return ptr->value;
}

template <typename DataType>
inline DataType& LinkedList<DataType>::Iterator::operator*() const
{
    return ptr->value;
}

template <typename DataType>
inline bool LinkedList<DataType>::Iterator::operator==(const Iterator &other) const
{
    return ptr == other.ptr;
}

template <typename DataType>
LinkedList<DataType>::LinkedList(const std::initializer_list <DataType>& elements)
{
    for (const auto &el : elements)
        push_back(el);
}

template <typename DataType>
LinkedList<DataType>::LinkedList(std::initializer_list <DataType>&& elements)
{
    for (auto &&el : elements)
        emplace_back(std::move(el));
}

template <typename DataType>
LinkedList<DataType>::~LinkedList()
{
    Node *next;
    while (head)
    {
        next = head->next;
        delete head;
        head = next;
    }
}

template <typename DataType>
inline void LinkedList<DataType>::push_back(const DataType& element)
{
    *tail = new Node(element);
    tail = &((*tail)->next);
}

template <typename DataType>
inline void LinkedList<DataType>::emplace_back(const DataType&& element)
{
    *tail = new Node(std::move(element));
    tail = &((*tail)->next);
}

template <typename DataType>
inline void LinkedList<DataType>::push_front(const DataType& element)
{
    head = new Node(element, head);

    // `tail` should always point to nullptr value inside.
    // other situation happens only when we push_front on an empty node
    if (*tail)
        tail = &((*tail)->next);
}

template <typename DataType>
inline void LinkedList<DataType>::emplace_front(const DataType&& element)
{
    head = new Node(std::move(element), head);

    // `tail` should always point to nullptr value inside.
    // other situation happens only when we push_front on an empty node
    if (*tail)
        tail = &((*tail)->next);
}

template <typename DataType>
inline void LinkedList<DataType>::pop_back()
{
    if (!head) return;

    Node **last_node = &head;

    while ((*last_node)->next)
        last_node = &(*last_node)->next;

    delete (*last_node);
    *last_node = nullptr;
}

template <typename DataType>
inline void LinkedList<DataType>::pop_front()
{
    if (!head) return;

    Node *last_head = head;
    head = head->next;

    delete last_head;
}

template <typename DataType>
inline typename LinkedList<DataType>::Iterator LinkedList<DataType>::begin()
{
    return Iterator(head);
}

template <typename DataType>
inline typename LinkedList<DataType>::Iterator LinkedList<DataType>::end()
{
    return Iterator(nullptr);
}

template <typename DataType>
inline typename LinkedList<DataType>::Iterator LinkedList<DataType>::cbegin() const
{
    return Iterator(head);
}

template <typename DataType>
inline typename LinkedList<DataType>::Iterator LinkedList<DataType>::cend() const
{
    return Iterator(nullptr);
}

template <typename DataType>
inline u32 LinkedList<DataType>::length() const
{
    u32 len = 0;
    for (Node *curr = head; curr; curr = curr->next, ++len);
    return len;
}

template<typename T>
concept Printable = requires(T t) {
    { std::cout << t } -> std::same_as<std::ostream&>;
};
static_assert(Printable<int>);

template <Printable T>
inline std::ostream &operator<<(std::ostream &os, LinkedList<T> &ll)
{
    os << "{ ";
    for (const auto &el : ll)
        os << el << " ";
    os << "}";

    return os;
}

template <typename DataType>
template <Iterable IterableType>
inline bool LinkedList<DataType>::operator==(const IterableType &other) const
{
    return std::equal(other.begin(), other.end(), cbegin());
}
