#include "word.hpp"

#include <iostream>
#include <iomanip>

Word::Word(const std::string &deutsch, const std::string &russisch,
           unsigned correct, unsigned incorrect):
           _deutsch(deutsch), _russisch(russisch),
           _correct(correct), _incorrect(incorrect) {}

std::ostream& operator << (std::ostream& out, Word& word) {
    out << word._deutsch << ", " << word._russisch << ", ";
    out << word._correct << ", " << word._incorrect;

    return out;
}

double Word::get_accuracy() const {
    return double(_correct) / (_correct + _incorrect);
}

std::string Word::get_deutsch() const {
    return _deutsch;
}

std::string Word::get_russian() const {
    return _russisch;
}

void Word::prettyprint() {
    unsigned accuracy = (_correct * 100) / (_correct + _incorrect);
    std::cout << "{ German: \"" << _deutsch << "\" ; Russian: \"";
    std::cout << _russisch << "\" ; Accuracy: " << std::fixed;
    std::cout << std::setprecision(2) << get_accuracy() << "% }";
    std::cout.unsetf(std::ios::basefield);
    std::cout << std::endl;
}

void Word::update(bool update) {
    if (update)
        ++_correct;
    else
        ++_incorrect;    
}