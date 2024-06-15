#include <iostream>

using namespace std;

class Student {

	private:

		char name[50];
		char rollNo[8];
		float cgpa;

	public:

		Student(const char* rollNo = "11L1111", const char* name = "ABC", float cgpa = 2.00) : cgpa(cgpa) {
		
			for (int i = 0; ; i++) {

				*(this->rollNo + i) = *(rollNo + i);

				if (*(rollNo + i) == '\0')
					break;

			}

			for (int i = 0; ; i++) {

				*(this->name + i) = *(name + i);

				if (*(name + i) == '\0')
					break;

			}
		
		}

		void Print() {

			cout << this->name << " (" << this->rollNo << ")";

		}

		float getCGPA() {

			return this->cgpa;

		}

		bool operator== (const Student& otherStudent) {

			for (int i = 0; ; i++) {

				if (*(this->name + i) != *(otherStudent.name + i))
					return false;

				if (*(this->name + i) == '\0')
					break;

			}

			return true;

		}

		bool operator== (const char* otherStudentName) {

			for (int i = 0; ; i++) {

				if (*(this->name + i) != *(otherStudentName + i))
					return false;

				if (*(this->name + i) == '\0')
					break;

			}

			return true;

		}

};

class Society {

	private:

		int currentMembersCount;
		char name[50];
		Student* president;
		Student* members[5];

	public:

		Society(const char* name = "NerD GathererS") : currentMembersCount(0), president(0), members() {
		
			for (int i = 0; ; i++) {

				*(this->name + i) = *(name + i);

				if (*(name + i) == '\0')
					break;

			}

		}

		void PrintInfo() {

			cout << "Society Name: " << this->name << endl;
			cout << "President: ";

			if (this->president)
				this->president->Print();
			else
				cout << "Not Available";

			cout << endl;

			for (int i = 0; i < 5; i++) {

				cout << "Member " << i + 1 << ": ";

				if (*(this->members + i))
					(*(this->members + i))->Print();
				else
					cout << "Not Available";

				cout << endl;

			}

		}

		void AppointPresident(Student &pres) {

			if (this->president && pres.getCGPA() < 3.00)
				pres.Print(), cout << " cannot be appointed as President. President Position is NOT Vacant and CGPA Criteria not met." << endl;

			else if (this->president)
				pres.Print(), cout << " cannot be appointed as President. President Position is NOT Vacant." << endl;

			else if (pres.getCGPA() < 3.00)
				pres.Print(), cout << " cannot be appointed as President. CGPA Criteria not met." << endl;

			else
				this->president = &pres, pres.Print(), cout << " has been appointed as President." << endl;

		}

		void AddMember(Student* mem) {

			if (mem != this->president) {

				if (this->currentMembersCount < 5) {

					bool found = false;

					for (int i = 0; i < this->currentMembersCount; i++)
						if (*mem == *(this->members[i]))
							found = true;

					if (!found) {

						this->members[this->currentMembersCount++] = mem;

						mem->Print();
						cout << " has been added to Members list successfully." << endl;

					} else
						mem->Print(), cout << " already exists in Members list." << endl;

				} else
					mem->Print(), cout << " cannot be added to Members list. Member position is NOT vacant." << endl;

			} else
				cout << "President cannot be added in Members list." << endl;

		}

		void SuspendMember(const char* name) {

			int found = -1;

			for (int i = 0; i < this->currentMembersCount; i++)
				if (*(this->members[i]) == name)
					found = i;

			if (found != -1) {
				
				this->members[found]->Print(), cout << " has been suspended from " << this->name << " society." << endl;

				for (int i = found; i < this->currentMembersCount - 1; i++)
					this->members[i] = this->members[i + 1];
			
			} else
				cout << name << " is not found in the Members list." << endl;

		}

};

int main() {

	Student s1("12L1111", "Hashim Amla", 3.99);
	Student s2("13L1121", "Virat Kohli", 3.45);
	Student s3("13L1126", "Quinton de Kock", 2.98);
	Student s4("14L1361", "Joe Root", 2.99);
	Student s5("14L1124", "Martin Guptil", 3.09);
	Student s6("15L1314", "Rohit Sharma", 3.19);

	Society sports("sports");
	sports.PrintInfo();
	
	cout << endl;

	sports.AppointPresident(s3);
	sports.AppointPresident(s1);
	sports.AppointPresident(s2);

	cout << endl << endl << endl;

	Student s7("15L1334", "Robert Elen", 2.19);
	sports.AddMember(&s3);
	sports.AddMember(&s2);
	sports.AddMember(&s3);
	sports.AddMember(&s1);
	sports.AddMember(&s4);
	sports.AddMember(&s5);
	sports.AddMember(&s6);
	sports.AddMember(&s7);

	cout << endl;

	sports.PrintInfo();

	cout << endl << endl << endl;
	sports.SuspendMember("abc");
	sports.SuspendMember("Martin Guptil");

	cout << endl << endl << endl;
	Society ieee("IEEE");
	ieee.AppointPresident(s5);
	cout << endl;
	ieee.PrintInfo();

	return 0;

}