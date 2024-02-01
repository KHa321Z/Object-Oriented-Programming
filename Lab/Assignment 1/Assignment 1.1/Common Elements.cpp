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

    int index = 0;
    int size1, size2;
    int *array1, *array2, *array3;

    cout << "Enter Size of Array1: ";
    cin >> size1;
    cout << "Enter Size of Array2: ";
    cin >> size2;

    array1 = new int [size1];
    array2 = new int [size2];

    cout << endl;
    cout << "Array1:";
    cout << endl;

    for (int i = 0; i < size1; i++)
        cout << "Enter Element of Index " << i << ": ", cin >> array1[i];

    cout << endl;
    cout << "Array2:";
    cout << endl;

    for (int i = 0; i < size2; i++)
        cout << "Enter Element of Index " << i << ": ", cin >> array2[i];

    cout << endl;

    compressArray(array1, size1);
    compressArray(array2, size2);
    array1 = AllocateAndCopyArray(array1, size1);
    array2 = AllocateAndCopyArray(array2, size2);
    array3 = new int [size1 + size2];

    for (int i = 0; i < size1; i++)
        for (int j = 0; j < size2; j++)
            if (array1[i] == array2[j])
                array3[index++] = array1[i];

    array3 = AllocateAndCopyArray(array3, index);

    cout << "Common Elements: ";

    for (int i = 0; i < index; i++)
        cout << array3[i] << ((i != index - 1) ? ", " : "");

    return 0;

}