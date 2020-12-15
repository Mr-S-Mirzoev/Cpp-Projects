#include "button.hpp"

#include <exception>
#include <stdexcept>

Button::Button(const Rectangle &active, const TextedRectangle &text):
    _active(active), _textRect(text) {
    if (!active.owns(text.pose())) {
        throw std::runtime_error("Logic error: text not in button");
    }
}

Button::Button(const TextedRectangle &text):
    Button(text.pose(), text) {}

Rectangle Button::active() const {
    return _active;
}

TextedRectangle Button::text() const {
    return _textRect;
}