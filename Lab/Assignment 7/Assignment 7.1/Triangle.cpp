#include <iostream>
#include "Triangle.h"

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3, Style style) : x(x1, y1), y(x2, y2), z(x3, y3), st(style) {

    std::cout << "Triangle() called" << std::endl;

}

Triangle::~Triangle() {

    std::cout << "~Triangle() called" << std::endl;

}

void Triangle::print() {

    std::cout << "x: "; this->x.print();
    std::cout << std::endl;
    std::cout << "y: "; this->y.print();
    std::cout << std::endl;
    std::cout << "z: "; this->z.print();
    std::cout << std::endl;
    
    this->st.print();

}

void Triangle::setStyle(Style &style) {

    this->st = style;

}

void Triangle::setColor(const char* col) {

    this->st.setColor(col);

}

void Triangle::setFilled(bool value) {

    this->st.setFilled(value);

}