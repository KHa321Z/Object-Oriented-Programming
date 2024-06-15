#include <iostream>
#include <fstream>

using namespace std;

char** ReadStudentsListFromFile(int& size) {

	char** students;
	fstream studentFile("StudentsList.txt", ios::in);

	studentFile >> size;
	studentFile.ignore(numeric_limits<streamsize>::max(), '\n');

	students = new char* [size];

	for (int i = 0; i < size; i++) {

		students[i] = new char[80];
		studentFile.getline(students[i], 80);

	}

	return students;

}

void PrintAllNames(char** studentsList, int& size) {

	cout << "Students:" << endl << endl;

	for (int i = 0; i < size; i++)
		cout << "\t" << i + 1 << "- " << studentsList[i] << endl;

}

int FirstIndexOfSubString(char* myStr, char* strToFind) {

	int index = 0;

	for (int i = 0; myStr[i]; i++) {
		
		if (myStr[i] == strToFind[index++]) {
			if (!strToFind[index])
				return (i - index + 1);
		} else
			index = 0;

	}

	return -1;

}

char** FindNameFromStudentsList(char** list, char* SearchString, int size, int &filteredSize) {

	int counter = 0;
	char** namesFound = new char* [size];

	for (int i = 0; i < size; i++)
		if (FirstIndexOfSubString(list[i], SearchString) != -1)
			namesFound[counter++] = list[i];

	filteredSize = counter;
	char** tempNameArray = new char* [counter];

	for (int i = 0; i < counter; i++)
		tempNameArray[i] = namesFound[i];

	delete[] namesFound;
	return tempNameArray;

}

void RemoveStudents(char** &list, char* filteringName, int& size, int filteredSize) {

	for (int i = 0; i < size; i++)
		if (FirstIndexOfSubString(list[i], filteringName) != -1) {
			delete[] list[i];
			list[i] = 0;
		}

	int counter = 0;
	char** newList = new char* [size - filteredSize];

	for (int i = 0; i < size; i++)
		if (list[i])
			newList[counter++] = list[i];

	delete[] list;

	size -= filteredSize;
	list = newList;

}

int main()
{

	char choice;
	int size, filteredSize;
	char* name = new char [80];
	char** filteredNames;
	char** students = ReadStudentsListFromFile(size);
	PrintAllNames(students, size);

	cout << endl << endl;
	cout << "Search String: ";
	cin.getline(name, 80);
	cout << endl;
	cout << "Result Found:" << endl;

	filteredNames = FindNameFromStudentsList(students, name, size, filteredSize);
	PrintAllNames(filteredNames, filteredSize);

	cout << endl;
	cout << "Do you want to Delete these Names (Y/N): ";
	cin >> choice;
	cout << endl;

	if (choice == 'Y' || choice == 'y')
		RemoveStudents(students, name, size, filteredSize), PrintAllNames(students, size);

	else
		cout << "Program Terminated!";

	for (int i = 0; i < size; i++)
		delete[] students[i];

	delete[] name;
	delete[] filteredNames;
	delete[] students;

	return 0;

}