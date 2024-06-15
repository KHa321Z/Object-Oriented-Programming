#include <iostream>
#include "Point.h"


Point::Point(int X = 0, int Y = 0) : x(X), y(Y) {

    std::cout << "Point() called" << std::endl;

}

Point::~Point() {

    std::cout << "~Point() called" << std::endl;

}

void Point::print() {

    std::cout << "(" << this->x << ", " << this->y << ")";
    
}