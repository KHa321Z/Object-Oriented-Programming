#include <iostream>

using namespace std;

struct Data {
    int rows;
    int *cols;
    int **outputArray;
    int sum;
};

Data shrinkAndSum(int** inputArray, const int rows, const int cols) {

    int sum = 0;
    int currentRow = 0;
    int r = 0;
    int **outputArray;
    int *colArray = new int [rows] {};

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++)
            if (*(*(inputArray + i) + j) > 0)
                sum += *(*(inputArray + i) + j), colArray[i]++;

        if (colArray[i])
            r++;

    }

    outputArray = new int* [r];

    for (int i = 0; i < r; i++) {

        int currentCol = 0;

        while (!colArray[currentRow])
            currentRow++;

        outputArray[i] = new int [colArray[currentRow]];

        for (int j = 0; j < cols; j++)
            if (*(*(inputArray + currentRow) + j) > 0)
                *(*(outputArray + i) + currentCol++) = *(*(inputArray + currentRow) + j);

        currentRow++;

    }

    int* tempColArray = new int [r];
    currentRow = 0;

    for (int i = 0; i < rows; i++)
        if (colArray[i])
            *(tempColArray + currentRow++) = *(colArray + i);

    delete[] colArray;

    return (Data {r, tempColArray, outputArray, sum});

}

int main()
{
    int rows, cols;

    cout << "Enter Number of Rows: ";
    cin >> rows;
    cout << "Enter Number of Columns: ";
    cin >> cols;
    cout << endl;

    int** inputArray = new int* [rows];

    for (int i = 0; i < rows; i++) {

        *(inputArray + i) = new int [cols];

        for (int j = 0; j < cols; j++)
           cout << "Enter Value for [" << i << "][" << j <<"] = ", cin >> *(*(inputArray + i) + j);

        cout << endl;

    }

    cout << "Original Array:" << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
           cout << *(*(inputArray + i) + j) << "\t";
        
        cout << endl;
    }

    Data data = shrinkAndSum(inputArray, rows, cols);

    cout << endl;
    cout << "Sum = " << data.sum << endl << endl;
    cout << "Positive Array:" << endl;
    
    for (int i = 0; i < data.rows; i++) {

        for (int j = 0; j < *(data.cols + i); j++)
            cout << *(*(data.outputArray + i) + j) << "\t";
        
        cout << endl;

    }

    for (int i = 0; i < rows; i++)
        delete[] *(inputArray + i);

    for (int i = 0; i < data.rows; i++)
        delete[] *(data.outputArray + i);

    delete[] inputArray;
    delete[] data.outputArray;
    delete[] data.cols;

}
