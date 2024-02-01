#include <iostream>

using namespace std;

int main() {

    int num1, num2, sum;
    int *xPtr, *yPtr, *sumPtr;

    num1 = 5, num2 = 7, sum = 0;
    xPtr = yPtr = sumPtr = 0;

    cout << "Num1 = " << num1 << endl;
    cout << "Num2 = " << num2 << endl;
    cout << "Address of Num1 = " << &num1 << endl;
    cout << "Address of Num2 = " << &num2 << endl;

    xPtr = &num1, yPtr = &num2;

    cout << "*xPtr = " << *xPtr << endl;
    cout << "*yPtr = " << *yPtr << endl;

    sumPtr = &sum;
    sum = *xPtr + *yPtr;

    cout << "*sumPtr = " << *sumPtr << endl;
    cout << "xPtr = " << xPtr << endl;
    cout << "yPtr = " << yPtr << endl;

    return 0;

}
