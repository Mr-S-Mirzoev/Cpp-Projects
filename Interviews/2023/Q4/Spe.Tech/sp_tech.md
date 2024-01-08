# Spe Tech

## 1. [C++ System / API design](#cpp1)

```cpp
std::unordered_map<int64_t, std::shared_ptr<Order>> orders;

&Order

auto it = orders.find(GetId());
Order& order = *(it->second).get();

// 1

f(id) {
    orders[id].count++;

    g(id);

    ...

    h(id);
}
...

A a{id};
...


Log(order_ptr);

// 2

auto it = orders.find(GetId());

f(it);
...

A a{it};
...

// ??
```

## 2. [C++ metaprogramming fix](#cpp2)

```cpp

---------

template<class T>
class Vector {
public:
    explicit Vector(size_t size, T default_value) { ... }

    template<class Iterator>
    Vector(Iterator first, Iterator last) {
        for (auto it = first; it != last; ++it) {
            push_back(*it);
        }
    }

    ...
};

...
Vector<int> data(5, 3);
```

## 3. [C++ bin protocol decoder](#cpp3)

```cpp

/*

uint64_t

 0        1          2        3
00000001 10000000 | 00000001 10000001
 0000001  0000000 |  0000001  0000001
   00000010000000 |    00000010000001
              128 |               129

00000000

2^64 - 1

01101101 01111111 01111111 01111111 01111111 01111111 01111111 01111111 01111111 11111111

    000001 11111111  1111111 1111111 1111111 1111111 1111111 1111111 1111111 1111111

// 10th


*/

std::vector<uint64_t> decode(const std::vector<uint8_t>& data)
{
    std::vector<uint64_t> decoded;
    constexpr uint8_t value_size_in_bits = sizeof(uint8_t) * 8 - 1;
    constexpr uint8_t max_valid_sequence_size = (sizeof(uint64_t) * 8 + 7) / value_size_in_bits; // 10 for 64-bit

    uint64_t current_value = 0;
    int last_number_start = 0;
    bool is_last = false;
    for (int i = 0; i < data.size(); ++i)
    {
        is_last = (data[i] >> value_size_in_bits);

        if (i - last_number_start == max_valid_sequence_size - 1 && !(current_value >> (max_valid_sequence_size * value_size_in_bits)))
        {
            throw std::invalid_argument("Sequence of bytes cannot be a valid encoded message: dirty auxilary bits");
        }
        else if (i - last_number_start > max_valid_sequence_size - 1)
        {
            throw std::invalid_argument("Sequence of bytes cannot be a valid encoded message: max seq len exceeded");
        }

        current_value = (current_value << value_size_in_bits) + (data[i] ^ (static_cast<uint8_t>(is_last) << value_size_in_bits));

        const bool is_max_possible_length = i - last_number_start == max_valid_sequence_size - 1;

        if (is_last)
        {
            decoded.push_back(current_value);
            last_number_start = i + 1;
            current_value = 0;
        }
    }

    if (!is_last && !data.empty())
    {
        throw std::invalid_argument("Sequence of bytes cannot be a valid encoded message: last message is not terminated");
    }

    return decoded;
}
```

## 4. [C++ memory management](#cpp4)

How to enhance std::lower_bound for a 200 MB array of 64-bit integers?
