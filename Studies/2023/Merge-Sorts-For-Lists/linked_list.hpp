#pragma once

#include <cstdint>
#include <initializer_list>
#include <memory>
#include <ostream>

typedef uint32_t u32;

template<typename T>
concept Iterable = requires(T t) {
    t.begin();
    t.end();
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
        using difference_type   = std::ptrdiff_t;
        using value_type        = DataType;
        using pointer           = Node*;  // or also value_type*
        using reference         = DataType&;  // or also value_type&

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
    friend std::ostream& operator<<(std::ostream& os, LinkedList<U> &ll);

    Iterator begin();
    Iterator end();

    Iterator cbegin() const;
    Iterator cend() const;

    u32 length() const;
};

#include "linked_list_impl.hpp"
