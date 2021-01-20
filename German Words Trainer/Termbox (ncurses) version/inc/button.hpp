#ifndef BUTTON_H
#define BUTTON_H

#include "text_rectangle.hpp"

class Button {
    Rectangle _active;
    TextedRectangle _textRect;
public:
    Button(const Rectangle &active, const TextedRectangle &text);
    Button(const TextedRectangle &text);

    Rectangle active() const;
    TextedRectangle text() const;
};

#endif// BUTTON_H