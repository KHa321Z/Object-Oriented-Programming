#include <iostream>

using namespace std;

int arr[5] = {};

double add(double a, double b) {
	
	if (std::isnan(a) || std::isnan(b))
		throw(std::invalid_argument("Variable a or b is NaN!"));
	else
		return a + b;

}

class CustomArray {

	int arr[5];

	public:

		class ArrayIndexOutOfBoundsException : public exception {

			string msg;

			public:

				ArrayIndexOutOfBoundsException() : msg("Array Index Out of Bounds!") {};

				ArrayIndexOutOfBoundsException(string message) : msg(message) {}

				string what() {
					return msg;
				}

				void printMessage() {
					cout << "Exception! " << what() << endl;
				}

		};

		CustomArray() : arr{1, 2, 3, 4, 5} {}

		int getElementAtIndex(int index) {

			if (index < 0 || index > 4)
				throw ArrayIndexOutOfBoundsException();

			return arr[index];

		}

};

class Fraction {

	int numerator;
	int denominator;

	public:

		class DivisionByZeroException : public exception {

			string msg;

			public:

				DivisionByZeroException() : msg("Divided by Zero!") {}

				DivisionByZeroException(string message) : msg(message) {}

				string what() {
					return msg;
				}

		};

		Fraction(float num, float den) : numerator(num), denominator(den) {}

		Fraction operator/(const Fraction& other) {

			int newNum = this->numerator * other.denominator;
			int newDen = this->denominator * other.numerator;

			if (newDen == 0)
				throw DivisionByZeroException();

			return Fraction(newNum, newDen);

		}

		friend ostream& operator<<(ostream& out, Fraction f) {

			out << f.numerator << "/" << f.denominator;

			return out;

		}

};

int main() {

	int b = 0;
	float c = 0;

	try {

		if (b == 1)
			throw b;

		else if (c == 0)
			throw c;

		else
			cout << "No exception to throw!" << endl;

	} catch (int x) {
		
		cout << "Exception! Integer Thrown of value: " << x << endl;
		
	} catch (float x) {

		cout << "Exception! Float Thrown of value: " << x << endl;

	}

	cout << endl;

	try {

		cout << "First Call: " << add(b, c) << endl;
		cout << "Second Call: " << add(b / c, b) << endl;

	} catch (std::exception e) {

		cout << "Exception! " << e.what() << endl;

	}

	CustomArray arr;
	int index;

	cout << endl;
	cout << "Enter Index of Array: ";
	cin >> index;

	try {
		cout << "Value: " << arr.getElementAtIndex(index) << endl;
	} catch (CustomArray::ArrayIndexOutOfBoundsException e) {
		e.printMessage();
	}

	Fraction one(1, 5), two(2, 3), three(0, 1);

	try {

		cout << endl;
		cout << "First Fraction: " << (one / two) << endl;
		cout << "Second Fraction: " << (two / three) << endl;

	} catch (Fraction::DivisionByZeroException e) {
		cout <<  "Exception! " << e.what() << endl;
	}

	return 0;

}