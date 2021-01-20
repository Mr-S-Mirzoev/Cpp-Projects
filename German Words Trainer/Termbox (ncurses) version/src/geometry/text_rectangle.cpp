#include "text_rectangle.hpp"

namespace config {
    namespace text {
        extern int CENTRE;
        extern int LEFT;
        extern int RIGHT;
        extern int NO_BREAK_LINE;
        extern int BREAK_LINE;
    }
}

TextedRectangle::TextedRectangle(const Rectangle &rect, const std::string &text, 
    const TextPolicy tp): 
    _pose(rect)
{
    if (text.length() < _pose.width()) {
        if ((tp & config::text::CENTRE)) {
            std::string allignment(' ', (_pose.width() - text.length()) / 2);
            _text.push_back(allignment + text + allignment);
        } else if (tp & config::text::LEFT) {
            std::string allignment(' ', _pose.width() - text.length());
            _text.push_back(text + allignment);
        } else if (tp & config::text::RIGHT) {
            std::string allignment(' ', _pose.width() - text.length());
            _text.push_back(allignment + text);
        }
    } else {
        if (tp & config::text::NO_BREAK_LINE) {
            _text.push_back(text.substr(_pose.width()));
        } else if (tp & config::text::BREAK_LINE) {
            size_t offset = 0;
            for (int i = 0; i < _pose.height(); ++i) {
                _text.push_back(text.substr(offset, offset + _pose.width()));
                offset += _pose.width();
            }
        }
    }
}

TextedRectangle::TextedRectangle(const Rectangle &rect, const std::string &text):
    TextedRectangle(rect, text, config::text::CENTRE | config::text::BREAK_LINE) {}

Rectangle TextedRectangle::pose() const {
    return _pose;
}

std::vector <std::string> TextedRectangle::txt() const {
    return _text;
}