#include "digit.hpp"

Digit::Digit(short value): value_(value) {} 
Digit::Digit(char char_value) {
    value_ = (char_value >= 'A') ? char_value - 'A' + 10 : char_value - '0';
}

char Digit::to_char() const {
    return (value_ >= 10) ? 'A' + (value_ - 10) : '0' + value_;
}
int Digit::to_dec() const {
    return value_;
}

bool Digit::operator< (const Digit &rhs) const {
    return value_ < rhs.value_;
}

bool Digit::operator<= (const Digit &rhs) const {
    return value_ <= rhs.value_;
}

void Digit::operator++ () {
    ++value_;
}