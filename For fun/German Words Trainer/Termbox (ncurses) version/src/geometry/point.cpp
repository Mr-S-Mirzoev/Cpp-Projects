#include "point.hpp"

Point::Point (int x, int y):
    _x(x), _y(y) {}

int Point::x() const {
    return _x;
}

int Point::y() const {
    return _y;
}

Point Point::operator-(const Point &other) {
    return {_x - other._x, _y - other._y};
}

bool Point::operator>(const Point &other) {
    return (_x > other._x && _y > other._y);
}

bool Point::operator==(const Point &other) {
    return (_x == other._x && _y == other._y);
}