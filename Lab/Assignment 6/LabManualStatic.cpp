#include<iostream>
#include<fstream>
using namespace std;

class Helper {

	public:
		static int StringLenght(char* str) {

			//Write Yourself
			// This function should return lenght of str

			int len;

			for (len = 0; *(str + len); len++);

			return len;

		}

		static void StringCopy(char*& dest, char*& src) {

			//Deep Copies src into dest.

			for (int i = 0; *(src + i); i++)
				*(dest + i) = *(src + i);

		}

		static char* GetStringFromBuffer(char* str) {

			//Write Yourself
			//This function should allocate required memory on heap, 
			//copy string in this memory using StringCopy and return newly created cstring.

			int length = StringLenght(str);
			char* newStr = new char [length + 1] {};

			StringCopy(newStr, str);

			return newStr;

		}

};

class Car {

	private:
		inline static int totalCars = 0;	// initialize it to zero yourself
		int model;
		char* make;
		char* name;
		char* color;

	public:
		Car() {

			model = 0;
			color = make = name = 0;
			totalCars++;

		}

		~Car() {

			totalCars--;

			cout << "Destroying ";
			PrintListView();

			//Deallocate memory yourself
			delete[] make;
			delete[] name;
			delete[] color;

		}

		//Write Getter of totalCars yourself
		static int GetTotalCars() {

			return totalCars;

		}

		void ReadDataFromFile(ifstream& fin) {

			char temp[20] {};

			fin >> model;
			fin >> temp;

			//This is how we call static functions without object		
			make = Helper::GetStringFromBuffer(temp);

			//Set rest of the values yourself.
			fin >> temp;
			name = Helper::GetStringFromBuffer(temp);

			fin >> temp;
			color = Helper::GetStringFromBuffer(temp);

		}

		void PrintListView() {

			cout << model << " " << make << " " << name << " " << color << endl;
	
		}

		void PrintDetailView() {
		
			cout << "Car Information:" << endl;
			cout << "Model:\t" << model << endl;
			cout << "Make:\t" << make << endl;
			cout << "Name:\t" << name << endl;
			cout << "Color:\t" << color << endl;
		
		}

		void Input() {

			//Do not consume one extra byte on heap
			//Use only one temp buffer

			char temp[20];
			
			cout << "Enter New Car Information:" << endl;
			cout << "Enet Model:\t";
			cin >> model;

			cout << "Enet Make:\t";
			cin >> temp;

			make = Helper::GetStringFromBuffer(temp);

			cout << "Enet Name:\t";
			cin >> temp;

			name = Helper::GetStringFromBuffer(temp);

			cout << "Enet Color:\t";
			cin >> temp;

			color = Helper::GetStringFromBuffer(temp);

		}

};

Car* ReadDataFromFile(const char* fileName) {

	ifstream fin;
	int totalCars = 0;
	char buffer[80];

	fin.open(fileName);
			
	if (fin.is_open()) {

		fin >> totalCars;
		//cout << totalCars;
		fin.getline(buffer, 80, '\n');	//We are not saving comment
		//cout << buffer << endl;

		int i = 0;
		Car* carsList = new Car[totalCars];

		while (!fin.eof())
			carsList[i++].ReadDataFromFile(fin);

		fin.close();

		return carsList;

	} else
		return 0;

}

int main()
{
	//Comment all the code. Then uncomment it line by line. 
	//Implement/add functionality for uncommented line. 
	//Execute and verify result with output.
	Car* carsList = ReadDataFromFile("CarsData.txt");
	int count = 0;

	if (carsList != 0) {

		count = Car::GetTotalCars();	//Calling static function
		cout << "Total Number of Cars in System:\t" << count << endl;

		//Test one Print at a time.
		cout << "\nCars List:\n\n";

		{
			for (int i = 0; i < count; i++)
				carsList[i].PrintListView();
		}

		//Comment above printing and Test Printing 2
		/*cout << "\nCars List:\n\n";

		{
			Car temp = carsList[0];
			temp.PrintListView();

			for (int i = 1; i < count; i++) {
				temp = carsList[i];
				temp.PrintListView();
			}
		}*/

		if (carsList)
			delete[] carsList;

	}

	cout << "Total Number of Cars in System:\t" << Car::GetTotalCars() << endl << endl << endl;

	Car testCar;
	testCar.Input(); // Take car data from user
	testCar.PrintDetailView();

	cout << "Total Number of Cars in System:\t" << testCar.GetTotalCars() << endl << endl << endl;

}
