#pragma once
#include "Point.h"
#include "Style.h"

class Circle {

    private:

        Point center;
        float radius;
        Style st;

    public:

        Circle(int, int, float, Style);
        ~Circle();

        void print();

        void setStyle(Style&);
        void setColor(const char*);
        void setFilled(bool);

};