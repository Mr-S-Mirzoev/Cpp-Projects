#include "rectangle.hpp"

Rectangle::Rectangle(int blx, int bly, int trx, int tr_y):
    bottom_left_x(blx), bottom_left_y(bly), top_right_x(trx), top_right_y(tr_y) {}

Rectangle::Rectangle(Point bottom_left, Point top_right):
    bottom_left_x(bottom_left.x()), bottom_left_y(bottom_left.y()),
    top_right_x(top_right.x()), top_right_y(top_right.y()) {}

bool Rectangle::owns (const Rectangle &other) const {
    if (bottom_left_x <= other.bottom_left_x &&
        bottom_left_y >= other.bottom_left_y &&
        top_right_x   >= other.top_right_x   &&
        top_right_y   <= other.top_right_y)  {
        return true;
    } else {
        return false;
    }
}

bool Rectangle::owns (const Point &pt) const {
    if (pt.x() > bottom_left_x && pt.x() < bottom_left_y && 
        pt.y() > top_right_x && pt.y() < top_right_y) 
        return true; 
  
    return false;
}

int Rectangle::width() const {
    return (top_right_x - bottom_left_x);
}

int Rectangle::height() const {
    return (top_right_y - bottom_left_y);
}