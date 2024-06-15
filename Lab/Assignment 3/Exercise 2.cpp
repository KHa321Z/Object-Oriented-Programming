#include <iostream>
using namespace std;

int GetCharacterCount(char* myString, char ch) {

	int count = 0;

	for (int i = 0; ; i++)
		if (!myString[i])
			return count;
		else if (myString[i] == ch)
			count++;

}

void main()
{

	char character;
	char* myStr1 = new char [80] {};

	cout << "Enter String: ";
	cin.getline(myStr1, 80);
	cout << "Enter Character: ";
	cin >> character;
	cout << "Total Number of Occurances:\t" << GetCharacterCount(myStr1, character) << endl;

}