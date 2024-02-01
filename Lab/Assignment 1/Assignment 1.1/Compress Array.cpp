#include <iostream>

using namespace std;

int* AllocateAndCopyArray(int *myArray, int &size) {

    int *newArray = new int [size];

    for (int i = 0; i < size; i++)
        *(newArray + i) = *(myArray + i);

    delete[] myArray;

    return newArray;

}

void compressArray(int *myArray, int &size) {

    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
            if (j == size - 1)
                size -= j - i;

            else if (myArray[i] != myArray[j]) {

                size -= j - i - 1;

                if (j - i - 1 != 0)
                    for (int k = i + 1; k < size; k++)
                        myArray[k] = myArray[k + (j - i - 1)];

                break;
            }

}

int main() {

    int size;
    int *dynamicArray;

    cout << "Enter Size: ";
    cin >> size;
    cout << endl;

    dynamicArray = new int [size];

    for (int i = 0; i < size; i++)
        cout << "Enter Element of Index " << i << ": ", cin >> *(dynamicArray + i);

    cout << endl;
    cout << "Array Before Compression: ";

    for (int i = 0; i < size; i++)
        cout << *(dynamicArray + i) << ((i != size - 1) ? ", " : "");

    compressArray(dynamicArray, size);
    dynamicArray = AllocateAndCopyArray(dynamicArray, size);

    cout << endl;
    cout << "Array After Compression: ";

    for (int i = 0; i < size; i++)
        cout << *(dynamicArray + i) << ((i != size - 1) ? ", " : "");

    return 0;

}