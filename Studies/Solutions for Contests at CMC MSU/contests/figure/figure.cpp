#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include <ctype.h>
#include <algorithm>
#define _USE_MATH_DEFINES

class Figure
{
public:
    virtual ~Figure () {};
    virtual double get_square () const = 0;
};

class Rectangle: public Figure
{
    double a = 0.0, b = 0.0;
public:
    static Rectangle* make (std::string &s) {
        Rectangle *x = new Rectangle;
        sscanf(s.c_str(), "%lf %lf", &(x->a), &(x->b));
        return x;
    }
    virtual double get_square () const override {
        return (a * b);
    }
};

class Square: public Figure
{
    double a = 0.0;
public:
    static Square* make (std::string &s) {
        Square *x = new Square;
        sscanf(s.c_str(), "%lf", &(x->a));
        return x;
    }
    virtual double get_square () const override {
        return (a * a);
    }
};

class Circle: public Figure
{
    double r = 0.0;
public:
    static Circle* make (std::string &s) {
        Circle *x = new Circle;
        sscanf(s.c_str(), "%lf", &(x->r));
        return x;
    }
    virtual double get_square () const override {
        return (M_PI * r * r);
    }
};

bool compare (Figure *i, Figure *j)
{
    return (i->get_square() < j->get_square());
}

int main () {
    std::vector <Figure *> v;
    std::string s;
    while (std::getline(std::cin, s)) {
        unsigned i;
        for (i = 0; i < s.length(); i++) {
            if (!isspace(s[i])) {
                break;
            }
        }
        std::string for_make = s.substr(i + 2);
        Figure *x;
        switch (s[i]) {
            case 'R':
                x = Rectangle::make(for_make);
                break;
            case 'S':
                x = Square::make(for_make);
                break;
            case 'C':
                x = Circle::make(for_make);
                break;
            default:
                for (auto it = v.begin(); it != v.end(); ++it) {
                    if (*it) {
                        delete [](*it);
                    }
                }
                return 1;
        }
        v.push_back(x);
    }
    std::stable_sort (v.begin(), v.end(), compare);
    for (auto x : v) {
        std::cout << x.to_string() << std::endl;
    }
    for (auto x : v) {
        if x {
            delete x;
        }
    }
    return 0;
}
