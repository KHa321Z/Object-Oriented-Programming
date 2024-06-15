#include <iostream>

using namespace std;

class Date {

	int Day;
	int Month;
	int Year;

	public:

		Date() : Day(1), Month(1), Year(1926) {

			cout << "Default Constructor Called!" << endl;

		};

		Date(int day, int month, int year) : Day(day), Month(month), Year(year) {

			cout << "Overloaded Function Called!" << endl;

		};

		~Date() {

			cout << "Destructor Called!" << endl;

		};

		void setDay(int day) {
			Day = day;
		};
		
		void setMonth(int month) {
			Month = month;
		};
		
		void setYear(int year) {
			Year = year;
		};

		int getDay() {
			return Day;
		};
		
		int getMonth() {
			return Month;
		};
		
		int getYear() {
			return Year;
		};

		void Input() {

			cout << "Enter Day: ";
			cin >> Day;
			cout << "Enter Month: ";
			cin >> Month;
			cout << "Enter Year: ";
			cin >> Year;

		}

		void Print() {

			cout << Day << "/" << Month << "/" << Year << endl;

		}

		int Compare(Date otherDate) {

			if (Year < otherDate.Year)
				return -1;
			
			else if (Year > otherDate.Year)
				return 1;

			else if (Month < otherDate.Month)
				return -1;
			
			else if (Month > otherDate.Month)
				return 1;
			
			else if (Day < otherDate.Day)
				return -1;

			else if (Day > otherDate.Day)
				return 1;

			else 
				return 0;

		}

		Date IncrementMonth() {

			Date newDate(Day, Month + 1, Year);

			if (newDate.Month > 12)
				newDate.Month %= 12, newDate.Year++;

			return newDate;

		}

};

int main() {

	Date date1;
	date1.Print();

	Date independanceDay(14, 8, 1947);
	independanceDay.Print();

	date1.Input();
	date1.Print();

	Date xmasDay;
	xmasDay.Print();
	xmasDay.setDay(25);
	xmasDay.setMonth(12);
	xmasDay.setYear(2018);
	cout << "Day: " << xmasDay.getDay() << endl;
	cout << "Month: " << xmasDay.getMonth() << endl;
	cout << "Year: " << xmasDay.getYear() << endl;

	Date temp;
	temp = xmasDay;
	temp.Print();

	cout << xmasDay.Compare(temp) << endl;

	date1.Print();
	date1.IncrementMonth().Print();

	return 0;

}