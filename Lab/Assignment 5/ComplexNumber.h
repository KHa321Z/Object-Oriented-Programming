#pragma once

class ComplexNumber
{

	private:
		int* real; //Integer will be saved on heap
		int* imaginary; //Data will be saved on heap

	public:
		ComplexNumber();
		ComplexNumber(int, int); /*Constructor with Default arguments,
		allocate memory properly and display Constructor Called message with
		data.*/
		ComplexNumber(const ComplexNumber&);
		~ComplexNumber(); /*Deallocate memory properly and Display
		Destructor Called message with data.*/
		void Input(); //Takes input from user
		void Output(); //Properly display Complex number like a+bi
		float Magnitude(); //Calculates magnitude of a complex number

};