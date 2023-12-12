#pragma once

#include <cstdint>
#include <initializer_list>
#include <memory>
#include <ostream>

typedef uint32_t u32;

template <typename T>
concept Iterable = requires(T t) {
    t.begin();
    t.end();
    t.size();
    t.begin()++;
};

template <typename DataType>
class LinkedList
{
private:
    struct Node
    {
        DataType value;
        using UPtr = std::unique_ptr<Node>;
        UPtr next;

        Node(const DataType& value, UPtr next = nullptr);
        Node(DataType&& value, UPtr next = nullptr);
    };

    typename Node::UPtr head = nullptr;
    typename Node::UPtr* tail = &head;

    LinkedList(typename Node::UPtr head, typename Node::UPtr* tail = nullptr);
    void add_node_back(typename Node::UPtr new_node);
    void add_node_front(typename Node::UPtr new_node);

    typename Node::UPtr detach_back();
    typename Node::UPtr detach_front();

public:
    LinkedList() = default;
    LinkedList(const LinkedList<DataType>& other);
    LinkedList(LinkedList<DataType>&& other);
    LinkedList(const std::initializer_list<DataType>& elements);
    LinkedList(std::initializer_list<DataType>&& elements);
    ~LinkedList();

    LinkedList<DataType>& operator=(const LinkedList<DataType>& other);
    LinkedList<DataType>& operator=(LinkedList<DataType>&& other);

    class Iterator
    {
    private:
        Node* ptr;

    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = DataType;
        using pointer = Node*;       // or also value_type*
        using reference = DataType&; // or also value_type&

        Iterator(Node* ptr);

        Iterator& operator++(int);
        Iterator& operator++();
        DataType& operator*();
        DataType& operator*() const;

        bool operator==(const Iterator& other) const;
    };

    void push_back(const DataType& element);
    void emplace_back(const DataType&& element);
    void push_front(const DataType& element);
    void emplace_front(const DataType&& element);

    void pop_back();
    void pop_front();

    DataType& front();
    DataType& back();

    DataType front() const;
    DataType back() const;

    template <Iterable IterableType>
    bool operator==(const IterableType& other) const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, LinkedList<U>& ll);

    Iterator begin();
    Iterator end();

    Iterator cbegin() const;
    Iterator cend() const;

    u32 size() const;
    bool empty() const;

    template <typename T>
    friend LinkedList<T> divide(LinkedList<T>& list);

    template <typename T>
    friend LinkedList<T> concat(LinkedList<T>& list1, LinkedList<T>&& list2);

    template <typename T>
    friend void merge_sort(LinkedList<T>& list);
};

#include "linked_list_impl.hpp"
