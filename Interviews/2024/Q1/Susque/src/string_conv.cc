#include "string_conv.h"

#if __has_include(<charconv>)

#include <charconv>

#if defined(_MSC_VER) && !defined(__clang__)
#pragma message("Using std::from_chars")
#else
#warning "Using std::from_chars"
#endif

bool int_from_chars(std::string_view int_repr, int& result)
{
    auto [ptr, ec] = std::from_chars(int_repr.data(), int_repr.data() + int_repr.size(), result);
    // Check if the conversion was successful and the entire string was consumed
    return ec == std::errc() && ptr == int_repr.data() + int_repr.size();
}

#else

#include <cctype>

#if defined(_MSC_VER) && !defined(__clang__)
#pragma message("Using custom int_from_chars")
#else
#warning "Using custom int_from_chars"
#endif

// since std::from_chars isn't available
bool int_from_chars(std::string_view int_repr, int& result)
{
    result = 0;

    bool is_negative = false;
    std::size_t index = 0;

    if (!int_repr.empty() && int_repr.front() == '-')
    {
        is_negative = true;
        index = 1;
    }

    for (; index < int_repr.size(); ++index)
    {
        char c = int_repr[index];

        if (!std::isdigit(c))
            return false;

        int digit = c - '0';

        // check for overflow
        if (is_negative)
        {
            // doesn't fit in int
            if (-result < (std::numeric_limits<int>::min() + digit) / 10)
                return false;
        }
        else
        {
            // doesn't fit in int
            if (result > (std::numeric_limits<int>::max() - digit) / 10)
                return false;
        }

        result = result * 10 + digit;
    }

    if (is_negative)
        result = -result;

    return true;
}

#endif
