#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>

using namespace std;

void expand(string* &oneDarray, int &size) {

    string* tempArray = new string [++size];

    for (int i = 0; i < size - 1; i++)
        *(tempArray + i) = *(oneDarray + i);

    if (oneDarray)
        delete[] oneDarray;

    oneDarray = tempArray;

}

void expand(int* &oneDarray, int &size) {

    int* tempArray = new int [++size];

    for (int i = 0; i < size - 1; i++)
        *(tempArray + i) = *(oneDarray + i);

    delete[] oneDarray;
    oneDarray = tempArray;

}

void expand(string** &twoDarray, int &size) {

    string** tempArray = new string* [++size];

    for (int i = 0; i < size - 1; i++)
        *(tempArray + i) = *(twoDarray + i);

    delete[] twoDarray;
    twoDarray = tempArray;

}

int main() {

    srand(time(0));

    fstream inputFile("input.txt", ios::in);

    if (!inputFile.is_open()) {

        inputFile.close();
        inputFile.open("input.txt", ios::out);

        int rows = (rand() % 5) + 5;
        int cols = (rand() % 5) + 5;

        for (int i = 0; i < rows; i++) {

            for (int j = 0; j < cols; j++)
                inputFile << ((rand() % 2) ? "Yes " : "No ");

            inputFile << endl;

        }

        inputFile.close();
        inputFile.open("input.txt", ios::in);

    }

    int rows = 0, cols = 0;
    string** inputArray = new string* [++rows];

    while (true) {

        if (cols == 0)
            *(inputArray + rows - 1) = new string [++cols];
        else
            expand(*(inputArray + rows - 1), cols);

        inputFile >> *(*(inputArray + rows - 1) + cols - 1);
        inputFile.ignore();

        if (inputFile.peek() == '\n') {

            inputFile.ignore();
            
            if (inputFile.peek() != EOF)
                cols = 0, expand(inputArray, rows);
            else
                break;

        }

    }

    cout << "Original Array:" << endl;

    for (int i = 0; i < rows; i++, cout << endl)
        for (int j = 0; j < cols; j++)
            cout << *(*(inputArray + i) + j) << " ";

    cout << endl;
    cout << "Compressed Array:" << endl;

    int** compressArray = new int* [rows];
    int** intermediateArray = new int* [rows] {};

    for (int i = 0; i < rows; i++) {

        int counter = 0;
        *(compressArray + i) = new int [2];

        for (int j = 0; j < cols; j++)
            if (*(*(inputArray + i) + j) == "Yes")
                expand(*(intermediateArray + i), counter), *(*(intermediateArray + i) + counter - 1) = j + 1;

        **(compressArray + i) = counter;
        *(*(compressArray + i) + 1) = cols - counter;

        cout << *(*(compressArray + i)) << " " << *(*(compressArray + i) + 1) << endl;

    }

    cout << endl;
    cout << "Intermediate Array:" << endl;

    for (int i = 0; i < rows; i++, cout << endl)
        for (int j = 0; j < **(compressArray + i); j++)
            cout << *(*(intermediateArray + i) + j) << " ";


    for (int i = 0; i < rows; i++) {
        delete[] *(inputArray + i);
        delete[] *(compressArray + i);
        delete[] *(intermediateArray + i);
    }

    delete[] inputArray;
    delete[] compressArray;
    delete[] intermediateArray;

    return 0;

}