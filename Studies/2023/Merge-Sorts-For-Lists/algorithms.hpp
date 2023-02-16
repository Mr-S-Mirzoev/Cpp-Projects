#pragma once

#include "linked_list.hpp"

template <typename DataType>
void merge_sort(LinkedList<DataType> &list);

template <typename DataType>
LinkedList<DataType> divide(LinkedList<DataType> &list);

template <typename DataType>
LinkedList<DataType> concat(LinkedList<DataType> &list1, LinkedList<DataType> &&list2);

template <typename DataType>
inline void merge_sort(LinkedList<DataType> &list)
{
    if (list.empty() || list.head->next == nullptr) return;

    auto list_rest = divide(list);

    merge_sort(list);
    merge_sort(list_rest);

    LinkedList<DataType> res;
    while (!list.empty() || !list_rest.empty())
    {
        if (list.empty())
        {
            res.add_node_back(std::move(list_rest.head));
            break;
        }

        if (list_rest.empty())
        {
            res.add_node_back(std::move(list.head));
            break;
        }

        if (list.front() > list_rest.front())
            res.add_node_back(list_rest.detach_front());
        else
            res.add_node_back(list.detach_front());
    }

    list = std::move(res);
}

template <typename DataType>
inline LinkedList<DataType> divide(LinkedList<DataType> &list)
{
    typename LinkedList<DataType>::Node::UPtr *half = &list.head;
    typename LinkedList<DataType>::Node *fast = list.head.get();
    while (fast && fast->next)
    {
        fast = fast->next->next.get();
        half = &(*half)->next;
    }

    LinkedList<DataType> ret{std::move(*half), list.tail};
    assert(*half == nullptr);
    list.tail = half;

    return ret;
}

template <typename DataType>
inline LinkedList<DataType> concat(LinkedList<DataType> &list1, LinkedList<DataType> &&list2)
{
    *list1.tail = std::move(list2.head);
    list1.tail = list2.tail;
    return list1;
}
