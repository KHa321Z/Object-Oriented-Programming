#pragma once
#include "Point.h"
#include "Style.h"

class Triangle {

    private:

        Point x;
        Point y;
        Point z;
        Style st;

    public:

        Triangle(int, int, int, int, int, int, Style);
        ~Triangle();

        void print();

        void setStyle(Style&);
        void setColor(const char*);
        void setFilled(bool);

};