#include <iostream>
#include "Circle.h"

Circle::Circle(int centerX, int centerY, float r, Style style) : center(centerX, centerY), radius(r), st(style) {

    std::cout << "Circle() called" << std::endl;

}

Circle::~Circle() {

    std::cout << "~Circle() called" << std::endl;

}

void Circle::print() {

    std::cout << "Center: "; this->center.print();
    std::cout << std::endl;
    std::cout << "Radius: " << this->radius;
    std::cout << std::endl;

    this->st.print();

}

void Circle::setStyle(Style &style) {

    this->st = style;

}

void Circle::setColor(const char* col) {

    this->st.setColor(col);

}

void Circle::setFilled(bool value) {

    this->st.setFilled(value);

}