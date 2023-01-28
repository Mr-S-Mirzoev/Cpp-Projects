#pragma once

#include <iostream>

template<typename T>
concept Printable = requires(T t) {
    { std::cout << t } -> std::same_as<std::ostream&>;
};
static_assert(Printable<int>);
