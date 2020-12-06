#ifndef WORD_H
#define WORD_H

#include <string>
#include <ostream>

class Word
{
private:
    std::string _deutsch, _russisch;
    unsigned _correct, _incorrect;
public:
    Word(const std::string &deutsch,
         const std::string &russisch,
         unsigned correct,
         unsigned incorrect);
    ~Word() = default;

    std::string get_deutsch() const;
    std::string get_russian() const;
    double get_accuracy() const;

    void update(bool correctness);

    void prettyprint();

    friend std::ostream& operator << (std::ostream& out, Word& word);
};

#endif