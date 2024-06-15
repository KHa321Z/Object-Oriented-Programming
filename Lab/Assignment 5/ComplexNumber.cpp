#include <iostream>
#include <math.h>

#include "ComplexNumber.h"

using namespace std;

ComplexNumber::ComplexNumber() : real(new int{ 0 }), imaginary(new int{ 0 }) {

	cout << "Constructor Called with Real = " << *real << " and Imaginary = " << *imaginary << endl;

}

ComplexNumber::ComplexNumber(int r = 0, int i = 0) : real(new int { r }), imaginary(new int { i }) {

	cout << "Constructor Called with Real = " << *real << " and Imaginary = " << *imaginary << endl;

}

ComplexNumber::ComplexNumber(const ComplexNumber& otherNumber) {

	real = new int { *otherNumber.real };
	imaginary = new int { *otherNumber.imaginary };

	cout << "Copy Constructor Called with Real = " << *real << " and Imaginary = " << *imaginary << endl;

}

ComplexNumber::~ComplexNumber() {

	delete real;
	delete imaginary;

}

void ComplexNumber::Input() {

	cout << "Enter Real Part of Complex Number: ";
	cin >> *real;
	cout << "Enter Imaginary Part of Complex Number: ";
	cin >> *imaginary;

}

void ComplexNumber::Output() {

	cout << *real << " + " << *imaginary << "i";

}

float ComplexNumber::Magnitude() {

	return sqrt(pow(*real, 2) + pow(*imaginary, 2));

}