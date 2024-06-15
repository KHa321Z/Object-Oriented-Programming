#include <iostream>
#include "Style.h"

Style::Style(const char* col, bool fill) {

    std::cout << "Style() called" << std::endl;

}

Style::~Style() {

    std::cout << "~Style() called" << std::endl;

}

void Style::print() {

    std::cout << "Color: " << this->color;
    std::cout << std::endl;
    std::cout << "IsFilled: " << this->isFilled;
    std::cout << std::endl;

}

void Style::setFilled(bool value) {

    this->isFilled = value;

}

void Style::setColor(const char* col) {

    for (int i = 0; ; i++) {

        this->color[i] = col[i];

        if (col[i] == '\0')
            break;

    }

}