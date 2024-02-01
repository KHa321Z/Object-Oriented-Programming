#include <iostream>

using namespace std;

int* InputArray(int &);
void OutputArray(int *, const int &);
int* AllocateAndCopyArray(int *, int &);
void ExpandArray(int &);

int* InputArray(int &size) {

    int index = 0;

    cout << "Enter size of Array: ";
    cin >> size;

    cout << endl;
    cout << "Enter Elements:";
    cout << endl;

    int *dynamicArray = new int [size];

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

    cout << endl;

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

void ExpandArray(int &size) {

    int temp;
    int *dynamicArray = InputArray(size);

    cout << endl;
    cout << "Expand Array:";
    cout << endl;

    for (int i = 0; i <= size / 2; i++)
        temp = *(dynamicArray + size - i - 1), *(dynamicArray + size - i - 1) = *(dynamicArray + i), *(dynamicArray + i) = temp;

    OutputArray(dynamicArray, size);

    delete[] dynamicArray;

}

int main() {

    int size;

    ExpandArray(size);

    return 0;

}
