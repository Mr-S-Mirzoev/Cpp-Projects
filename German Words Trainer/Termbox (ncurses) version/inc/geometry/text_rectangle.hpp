#ifndef TEXT_RECTANGLE_H
#define TEXT_RECTANGLE_H

#include "types.hpp"
#include "rectangle.hpp"

#include <vector>
#include <string>

class TextedRectangle
{
private:
    Rectangle _pose;
    std::vector <std::string> _text;
public:
    TextedRectangle(const Rectangle &rect, const std::string &text, 
                    const TextPolicy tp);
    TextedRectangle(const Rectangle &rect, const std::string &text);

    Rectangle pose() const;
    std::vector <std::string> txt() const;
};

#endif// TEXT_RECTANGLE_H