#include <iostream>

using namespace std;

inline int** AllocateMemory(int& rows, int& cols);
inline void InputMatrix(int** matrix, const int& rows, const int& cols);
inline void DisplayMatrix(int** matrix, const int& rows, const int& cols);
inline void DeallocateMemory(int** matrix, const int& rows);
int* MaxOfColumn(int** matrix, const int& rows, const int& cols);
bool IsMatrixUpperTriangle(int** matrix, const int& rows, const int& cols);
int* GetDiagonal(int** matrix, const int& rows, const int& cols);

int main() {

	int rows, cols;
	int** matrix;
	int* diagonal;

	matrix = AllocateMemory(rows, cols);
	
	InputMatrix(matrix, rows, cols);
	DisplayMatrix(matrix, rows, cols);

	diagonal = MaxOfColumn(matrix, rows, cols);

	cout << "Max Elements of Column: ";
	for (int i = 0; i < rows; i++)
		cout << *(diagonal + i) << " ";
	cout << endl;
	cout << ((IsMatrixUpperTriangle(matrix, rows, cols)) ? "Matrix is Upper Triangular" : "Matrix is not Upper Triangular");
	cout << endl;

	diagonal = GetDiagonal(matrix, rows, cols);

	cout << "Diagonal: ";
	for (int i = 0; i < rows; i++)
		cout << *(diagonal + i) << " ";
	cout << endl;

	DeallocateMemory(matrix, rows);

	delete[] diagonal;
	diagonal = NULL;
	matrix = NULL;

	return 0;

}

inline int** AllocateMemory(int& rows, int& cols) {

	cout << "Enter Rows of Matrix: ";
	cin >> rows;
	cout << "Enter Cols of Matrix: ";
	cin >> cols;
	cout << endl;

	int** matrix = new int* [rows];

	for (int i = 0; i < rows; i++)
		*(matrix + i) = new int [cols];

	return matrix;

}

inline void InputMatrix(int** matrix, const int& rows, const int& cols) {

	cout << "Enter Elements of Matrix:" << endl;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			cout << "Element [" << i << "][" << j << "]: ", cin >> *(*(matrix + i) + j);

		cout << endl;
	}

	cout << endl;

}

inline void DisplayMatrix(int** matrix, const int& rows, const int& cols) {

	cout << "Matrix:" << endl;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			cout << *(*(matrix + i) + j) << '\t';

		cout << endl;
	}

	cout << endl;

}

inline void DeallocateMemory(int** matrix, const int& rows) {

	for (int i = 0; i < rows; i++)
		delete[] *(matrix + i);

	delete[] matrix;

}

int* MaxOfColumn(int** matrix, const int& rows, const int& cols) {

	int* maxNumbers = new int [cols];

	for (int j = 0; j < cols; j++) {

		*(maxNumbers + j) = **(matrix + j);

		for (int i = 0; i < rows; i++)
			if (*(*(matrix + i) + j) > *(maxNumbers + j))
				*(maxNumbers + j) = *(*(matrix + i) + j);

	}

	return maxNumbers;

}

bool IsMatrixUpperTriangle(int** matrix, const int& rows, const int& cols) {

	if (rows != cols)
		return false;

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < i; j++)
			if (*(*(matrix + i) + j))
				return false;

	return true;

}

int* GetDiagonal(int** matrix, const int& rows, const int& cols) {

	if (rows != cols)
		return NULL;

	int* diagonal = new int [rows];

	for (int i = 0; i < rows; i++)
		*(diagonal + i) = *(*(matrix + i) + i);

	return diagonal;

}