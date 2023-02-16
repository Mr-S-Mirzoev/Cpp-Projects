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
inline LinkedList<DataType>::LinkedList(typename Node::UPtr other_head, typename Node::UPtr* other_tail)
{
    tail = (other_head) ? other_tail : &head;
    head = std::move(other_head);
}

template <typename DataType>
inline void LinkedList<DataType>::add_node_back(typename Node::UPtr new_node)
{
    *tail = std::move(new_node);
    tail = &(*tail)->next;
}

template <typename DataType>
inline void LinkedList<DataType>::add_node_front(typename Node::UPtr new_node)
{
    assert(new_node->next == nullptr);

    new_node->next = std::move(head);
    head = std::move(new_node);

    // `tail` should always point to nullptr value inside.
    // other situation happens only when we push_front on an empty node
    if (*tail)
        tail = &((*tail)->next);
}

template <typename DataType>
inline typename LinkedList<DataType>::Node::UPtr LinkedList<DataType>::detach_back()
{
    if (!head) return nullptr;

    typename Node::UPtr *last_node = &head;

    while ((*last_node)->next)
        last_node = &(*last_node)->next;

    return std::move(*last_node);
}

template <typename DataType>
inline typename LinkedList<DataType>::Node::UPtr LinkedList<DataType>::detach_front()
{
    if (!head) return nullptr;

    typename Node::UPtr next = std::move(head->next);
    typename Node::UPtr ret = std::move(head);
    head = std::move(next);

    return ret;
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
    add_node_back(std::make_unique<Node>(element));
}

template <typename DataType>
inline void LinkedList<DataType>::emplace_back(const DataType&& element)
{
    add_node_back(std::make_unique<Node>(std::move(element)));
}

template <typename DataType>
inline void LinkedList<DataType>::push_front(const DataType& element)
{
    add_node_front(std::make_unique<Node>(element, nullptr));
}

template <typename DataType>
inline void LinkedList<DataType>::emplace_front(const DataType&& element)
{
    add_node_front(std::make_unique<Node>(std::move(element), nullptr));
}

template <typename DataType>
inline void LinkedList<DataType>::pop_back()
{
    detach_back();
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
inline u32 LinkedList<DataType>::size() const
{
    u32 len = 0;
    for (Node *curr = head.get(); curr; curr = curr->next.get(), ++len);
    return len;
}

template <typename DataType>
inline bool LinkedList<DataType>::empty() const
{
    return !(head.get());
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
    return other.size() == size() && std::equal(other.cbegin(), other.cend(), cbegin());
}
