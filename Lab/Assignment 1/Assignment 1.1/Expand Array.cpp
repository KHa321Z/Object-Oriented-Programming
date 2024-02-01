#include <iostream>

using namespace std;

int* AllocateAndCopyArray(int *myArray, int &size) {

    size *= 2;
    int *newArray = new int [size];

    for (int i = 0; i < size; i++)
        *(newArray + i) = *(myArray + i);

    delete[] myArray;

    return newArray;

}

int main() {

    int index = 0;
    int size = 5;
    int *dynamicArray = new int [size];

    cout << "Enter Elements:";
    cout << endl;

    while (true) {

        cout << "Enter Element at Index " << index << ": ";
        cin >> *(dynamicArray + index);

        if (*(dynamicArray + index) == -1) {

            *(dynamicArray + index) = 0;
            size = index;

            break;
        
        }

        if (index == size - 1)
            dynamicArray = AllocateAndCopyArray(dynamicArray, size);

        index++;

    }

    dynamicArray = AllocateAndCopyArray(dynamicArray, index);

    cout << endl;
    cout << "Elements of Array:";
    cout << endl;

    for (int i = size - 1; i >= 0; i--)
        cout << "Element at Index " << (size - i - 1) << ": " << *(dynamicArray + i) << endl;

    cout << endl;

    return 0;

}