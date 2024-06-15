#include <iostream>

using namespace std;

int* AllocateAndCopyArray(int*, int&);
int* InputArray(int&);
void OutputArray(int*, const int&);
int* CompressArray(int*, int&);
int* Intersection(int*, int&, int*, int&, int&);

int main() {

    int sizeA, sizeB, sizeC;
    int *setA, *setB, *setC;

    cout << "Set A: " << endl;
    setA = InputArray(sizeA);

    cout << endl;
    cout << "Set B: " << endl;
    setB = InputArray(sizeB);
    cout << endl;

    setA = CompressArray(setA, sizeA);
    setB = CompressArray(setB, sizeB);

    sizeC = sizeA + sizeB;
    setC = Intersection(setA, sizeA, setB, sizeB, sizeC);

    cout << "After Compression:" << endl;
    cout << "Set A:" << endl;
    OutputArray(setA, sizeA);
    cout << "Set B:" << endl;
    OutputArray(setB, sizeB);
    cout << endl;
    cout << "A Intersection B:" << endl;
    OutputArray(setC, sizeC);

    delete[] setA;
    delete[] setB;
    delete[] setC;

    setA = setB = setC = NULL;

    return 0;

}

int* AllocateAndCopyArray(int* myArray, int& size) {

    int* newArray = new int [size];

    for (int i = 0; i < size; i++)
        *(newArray + i) = *(myArray + i);

    delete[] myArray;

    return newArray;

}

int* InputArray(int& size) {

    cout << "Enter Size: ";
    cin >> size;
    cout << endl;
    cout << "Enter Elements of Set:" << endl;

    int* dynamicArray = new int [size];

    for (int i = 0; i < size; i++)
        cout << "Element [" << (i + 1) << "]: ", cin >> *(dynamicArray + i);

    cout << endl;

    return dynamicArray;

}

void OutputArray(int* myArray, const int& size) {

    cout << "Elements of Array: ";

    for (int i = 0; i < size; i++)
        cout << *(myArray + i) << " ";

    cout << endl;

}

int* CompressArray(int* originalArr, int& size) {

    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
            if (*(originalArr + i) != *(originalArr + j)) {

                size -= j - i - 1;

                if (j - i - 1 != 0)
                    for (int k = i + 1; k < size; k++)
                        *(originalArr + k) = *(originalArr + k + (j - i - 1));

                break;

            } else if (j == size - 1)
                size -= j - i;


    return AllocateAndCopyArray(originalArr, size);

}

int* Intersection(int* setA, int& size1, int* setB, int& size2, int& size3) {

    int index = 0;
    int* setC = new int [size3];

    for (int i = 0; i < size1; i++)
        for (int j = 0; j < size2; j++)
            if (*(setA + i) == *(setB + j))
                *(setC + index++) = *(setA + i);

    size3 = index;

    return AllocateAndCopyArray(setC, size3);

}