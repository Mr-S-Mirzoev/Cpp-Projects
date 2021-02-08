#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.hpp"

class Rectangle
{
private:
    int bottom_left_x, bottom_left_y;
    int top_right_x, top_right_y;
public:
    Rectangle(int blx, int bly, int trx, int tr_y);
    Rectangle(Point bottom_left, Point top_right);

    int width() const;
    int height() const;

    bool owns(const Point &pt) const;
    bool owns(const Rectangle &other) const;
};

#endif// RECTANGLE_H