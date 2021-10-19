#ifndef DIGIT_H
#define DIGIT_H

class Digit
{
private:
    short value_;
public:
    Digit(short value);
    Digit(char char_value);

    char to_char() const;
    int to_dec() const;

    bool operator< (const Digit &rhs) const;
    bool operator<= (const Digit &rhs) const;
    void operator++ ();

    ~Digit() = default;
};

#endif // DIGIT_H