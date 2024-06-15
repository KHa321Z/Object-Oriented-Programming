#include <iostream>

using namespace std;

class pointType {

    private:

        int xCoordinate;
        int yCoordinate;

    public:

        pointType(int x = 0, int y = 0) : xCoordinate(x), yCoordinate(y) {}

        void setCoordinates(int x, int y) {

            xCoordinate = x;
            yCoordinate = y;

        }

        void printCoordinates() {

            cout << "x: " << xCoordinate << endl;
            cout << "y: " << yCoordinate << endl;

        }

        int getX() {
            return xCoordinate;
        }

        int getY() {
            return yCoordinate;
        }

};


int main() {

    pointType point(1,2);
    point.printCoordinates();
    point.setCoordinates(3,4);
    cout << " (" << point.getX() << ", " << point.getY() << ")";
    point.printCoordinates();

    return 0;

}