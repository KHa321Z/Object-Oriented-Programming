#include <iostream>

using namespace std;

int* InputArray(int &);
void OutputArray(int *, const int &);
int* AllocateAndCopyArray(int *, const int &);
void ExpandArray();

int* InputArray(int &size) {

    cout << "Enter size of Array: ";
    cin >> size;

    cout << endl;
    cout << "Enter Elements:";
    cout << endl;

    int *dynamicArray = new int [size];

    for (int i = 0; i < size; i++)
        cout << "Element at Index " << i << ": ", cin >> *(dynamicArray + i);

    cout << endl;

    OutputArray(dynamicArray, size);

    return dynamicArray;

}

void OutputArray(int *myArray, const int &size) {

    cout << "Elements of Array:";
    cout << endl;

    for (int i = 0; i < size; i++)
        cout << "Element at Index " << i << ": " << *(myArray + i) << endl;

    cout << endl;

}

int* AllocateAndCopyArray(int *myArray, int &size) {

    size *= 2;
    int *newArray = new int [size];

    for (int i = 0; i < size; i++)
        *(newArray + i) = *(myArray + i);

    delete[] myArray;

    return newArray;

}

void ExpandArray() {

    int temp, index = 0, size = 5;
    int *dynamicArray = new int [size];

    cout << endl;
    cout << "Expand Array:";
    cout << endl;

    while (true) {

        cout << "Enter Element at Index " << index << ": ";
        cin >> *(dynamicArray + index);

        if (*(dynamicArray + index) == -1) {

            *(dynamicArray + index) = 0;
            index--;

            break;
        
        }

        if (index == size)
            dynamicArray = AllocateAndCopyArray(dynamicArray, size);

        index++;

    }

    for (int i = 0; i < index / 2; i++)
        temp = *(dynamicArray + index - i), *(dynamicArray + index - i) = *(dynamicArray + i), *(dynamicArray + i) = temp;

    cout << endl;

    OutputArray(dynamicArray, index);

    delete[] dynamicArray;

}

int main() {

    int size;

    delete[] InputArray(size);
    ExpandArray();

    return 0;

}
