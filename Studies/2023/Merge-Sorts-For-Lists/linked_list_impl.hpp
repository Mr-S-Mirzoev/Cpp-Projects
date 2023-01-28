#include "linked_list.hpp"

#include "printable.hpp"

#include <ranges>
#include <utility>

template <typename DataType>
LinkedList<DataType>::Node::Node(const DataType& value, Node::UPtr next)
    : value(value), next(std::move(next))
{
}

template <typename DataType>
LinkedList<DataType>::Node::Node(DataType&& value, Node::UPtr next)
    : value(std::move(value)), next(std::move(next))
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
    ptr = ptr->next.get();
    return *this;
}

template <typename DataType>
inline typename LinkedList<DataType>::Iterator& LinkedList<DataType>::Iterator::operator++()
{
    ptr = ptr->next.get();
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
inline LinkedList<DataType>::LinkedList(const LinkedList<DataType> &other)
{
    for (auto it = other.cbegin(); it != other.cend(); ++it)
        push_back(*it);
}

template <typename DataType>
inline LinkedList<DataType>::LinkedList(LinkedList<DataType> &&other)
{
    tail = (other.head) ? other.tail : &head;
    head = std::move(other.head);
}

template <typename DataType>
LinkedList<DataType>::LinkedList(const std::initializer_list<DataType> &elements)
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
    while (head)
        head = std::move(head->next);
}

template <typename DataType>
inline LinkedList<DataType>& LinkedList<DataType>::operator=(const LinkedList<DataType> &other)
{
    for (const auto &el : other)
        push_back(el);

    return *this;
}

template <typename DataType>
inline LinkedList<DataType>& LinkedList<DataType>::operator=(LinkedList<DataType> &&other)
{
    tail = (other.head) ? other.tail : &head;
    head = std::move(other.head);

    return *this;
}

template <typename DataType>
inline void LinkedList<DataType>::push_back(const DataType& element)
{
    *tail = std::make_unique<Node>(element);
    tail = &((*tail)->next);
}

template <typename DataType>
inline void LinkedList<DataType>::emplace_back(const DataType&& element)
{
    *tail = std::make_unique<Node>(std::move(element));
    tail = &((tail->get())->next);
}

template <typename DataType>
inline void LinkedList<DataType>::push_front(const DataType& element)
{
    head = std::make_unique<Node>(element, std::move(head));

    // `tail` should always point to nullptr value inside.
    // other situation happens only when we push_front on an empty node
    if (*tail)
        tail = &((*tail)->next);
}

template <typename DataType>
inline void LinkedList<DataType>::emplace_front(const DataType&& element)
{
    head = Node::UPtr(new Node{std::move(element), std::move(head)});

    // `tail` should always point to nullptr value inside.
    // other situation happens only when we push_front on an empty node
    if (*tail)
        tail = &((*tail)->next);
}

template <typename DataType>
inline void LinkedList<DataType>::pop_back()
{
    if (!head) return;

    typename Node::UPtr *last_node = &head;

    while ((*last_node)->next)
        last_node = &(*last_node)->next;

    *last_node = nullptr;
}

template <typename DataType>
inline void LinkedList<DataType>::pop_front()
{
    if (!head) return;

    head = std::move(head->next);
}

template <typename DataType>
inline DataType &LinkedList<DataType>::front()
{
    return head.get()->value;
}

template <typename DataType>
inline DataType &LinkedList<DataType>::back()
{
    typename Node::UPtr *last_node = &head;

    while ((*last_node)->next)
        last_node = &(*last_node)->next;

    return (*last_node).get()->value;
}

template <typename DataType>
inline DataType LinkedList<DataType>::front() const
{
    return head.get()->value;
}

template <typename DataType>
inline DataType LinkedList<DataType>::back() const
{
    auto *last_node = const_cast<typename Node::UPtr *>(&head);

    while ((*last_node)->next)
        last_node = &(*last_node)->next;

    return (*last_node).get()->value;
}

template <typename DataType>
inline typename LinkedList<DataType>::Iterator LinkedList<DataType>::begin()
{
    return Iterator(head.get());
}

template <typename DataType>
inline typename LinkedList<DataType>::Iterator LinkedList<DataType>::end()
{
    return Iterator(nullptr);
}

template <typename DataType>
inline typename LinkedList<DataType>::Iterator LinkedList<DataType>::cbegin() const
{
    return Iterator(head.get());
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
    for (Node *curr = head.get(); curr; curr = curr->next.get(), ++len);
    return len;
}

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
