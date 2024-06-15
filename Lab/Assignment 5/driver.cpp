#include <iostream>
#include "ComplexNumber.h"

using namespace std;

int main()
{

    //------------------QUESTION 2------------------//

    ComplexNumber c1;

    c1.Input();
    c1.Output();

    cout << endl << endl;

    //------------------QUESTION 3------------------//
    
    ComplexNumber* cPtr;

    // It does not call the constructor as no memory is allocated for the object

    //------------------QUESTION 4------------------//
    
    cPtr = new ComplexNumber(3, 5);

    (*cPtr).Output();
    cout << endl << endl;

    //------------------QUESTION 5------------------//
    
    ComplexNumber complexNumbers[5] = {};

    cout << endl;

    for (int i = 0; i < 5; i++)
        cout << "Complex Number " << i + 1 << ":" << endl, complexNumbers[i].Input(), cout << endl;

    cout << endl;

    for (int i = 0; i < 5; i++)
        cout << "Complex Number " << i + 1 << ":" << endl, complexNumbers[i].Output(), cout << endl;

    cout << endl;

    // We can not delete an array allocated on stack
    // It will de-allocate automatically when it goes out of scope

    //------------------QUESTION 6------------------//

    int size;
    ComplexNumber* dynamicNumbers;

    cout << "Enter Size for Dynamic Array: ";
    cin >> size;
    cout << endl;

    dynamicNumbers = new ComplexNumber [size];

    cout << endl;

    for (int i = 0; i < size; i++)
        cout << "Complex Number " << i + 1 << ":" << endl, complexNumbers[i].Input(), cout << endl;

    cout << endl;

    for (int i = 0; i < size; i++)
        cout << "Complex Number " << i + 1 << ":" << endl, complexNumbers[i].Output(), cout << endl << "Magnitude = " << complexNumbers[i].Magnitude() << endl << endl;

    cout << endl;

    delete[] dynamicNumbers;

    // Yes we need to de-allocate the memory alotted to the array on heap

    //------------------QUESTION 7------------------//

    /*
    ComplexNumber c1(3, 4);
    ComplexNumber c2(4, 5);
    {
        ComplexNumber temp = c1;
        c1 = c2;
        c2 = temp;
    }
    c1.Output();
    c2.Output();
    */

    // The code will give re-declaration error as c1 is already declared for question 1
    // The code will also not run and give an exception for delete scalar as the temp object shallow copied the data on heap using default copy constructor and assignment operator
    // Which will de-allocate the data once it goes out of scope
    // Leaving c1 with dangling pointer

    //------------------QUESTION 8------------------//

    /*
    ComplexNumber c1(5, 10);
    {
        ComplexNumber c2(c1);
        cout << "c2 = ";
        c2.Output();
    }
    cout << "C1 = ";
    c1.Output();
    */

    // The code will give re-declaration error as c1 is already declared for question 1
    // The code will also not run and give an exception for delete scalar as the temp object shallow copied the data on heap using default copy constructor
    // Which will de-allocate the data once it goes out of scope
    // Leaving c1 with dangling pointer

    //------------------QUESTION 9------------------//

    ComplexNumber c11(5, 10);
    {
        ComplexNumber c2(c11);

        cout << "c2 = ";
        c2.Output();    
        cout << endl;
    }

    cout << "c11 = ";
    c11.Output();
    cout << endl;

    //------------------QUESTION 10-----------------//

    /*
    ComplexNumber c1(3, 4);
    {
        ComplexNumber c2, c3;
        C3 = c2 = c1;
        C2.Print();
        C3.Print();
    }
    C1.print();
    */

    // The code will give re-declaration error as c1 is already declared for question 1
    // The code will also not run and give an exception for delete scalar as the temp object shallow copied the data on heap using default assignment operator
    // Which will de-allocate the data once it goes out of scope
    // Leaving c1 with dangling pointer

    return 0;

}