#ifndef POINT_H
#define POINT_H

class Point
{
private:
    int _x, _y;
public:
    Point(int x = -1, int y = -1);

    int x() const;
    int y() const;

    Point operator-(const Point &other);
    bool operator>(const Point &other);
    bool operator==(const Point &other);
};

#endif// POINT_H