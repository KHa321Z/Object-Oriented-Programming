#include <iostream>
#include "Point.h"
#include "Circle.h"
#include "Triangle.h"
#include "Style.h"

using namespace std;

int main() {

	// =====================================================================
	
    Style s1("Red", true);
    Circle c1(3, 4, 2.5, s1);
    c1.print();
    Style s2("Blue", false);
    c1.setStyle(s2);
    c1.print();
    c1.setFilled(true);
    c1.print();
    c1.setColor("Green");
    c1.print();

    // =====================================================================

    Triangle t1(1, 2, 3, 4, 5, 6, s1);
    t1.print();
    Style s3("Yellow", false);
    t1.setStyle(s3);
    t1.print();
    t1.setFilled(true);
    t1.print();
    t1.setColor("Purple");
    t1.print();

}