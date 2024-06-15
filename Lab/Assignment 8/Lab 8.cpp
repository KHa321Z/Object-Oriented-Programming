#include <iostream>

using namespace std;

class Person {

	private:

		string first_name;
		string last_name;

	protected:

		int age;

	public:

		Person(string f_name, string l_name, int a) : first_name(f_name), last_name(l_name), age(a) {
		
			cout << "Person() Called..." << endl;

		}

		~Person() {

			cout << "~Person() Called..." << endl;

		}

		void setFirstName(string f_name) {
			this->first_name = f_name;
		}

		string getFirstName() {
			return this->first_name;
		}

		void setLastName(string l_name) {
			this->last_name = l_name;
		}

		string getLastName() {
			return this->last_name;
		}

		void setAge(int age) {
			this->age = age;
		}

		int getAge() {
			return this->age;
		}

		void printInformation() {

			cout << this->first_name << " " << this->last_name << " is " << this->age << " years old";

		}

};

class Student : public Person {

	protected:

		float cgpa;

	public:

		Student(string f_name, string l_name, int age, float gpa) : Person(f_name, l_name, age), cgpa(gpa) {
		
			cout << "Student() Called..." << endl;

		}

		~Student() {

			cout << "~Student() Called..." << endl;

		}

		void setCGPA(float gpa) {
			this->cgpa = gpa;
		}

		float getCGPA() {
			return this->cgpa;
		}

		void printStudent() {

			this->printInformation();

			cout << ", his cgpa is " << this->cgpa;

		}

};

class Undergraduate : public Student {

	protected:

		string fyp_name;

	public:

		Undergraduate(string f_name, string l_name, int age, float gpa, string project_name) : Student(f_name, l_name, age, gpa), fyp_name(project_name) {
		
			cout << "Undergraduate() Called..." << endl;

		}

		~Undergraduate() {

			cout << "~Undergraduate() Called..." << endl;

		}

		void setFYPName(string project_name) {
			this->fyp_name = project_name;
		}

		string getFYPName() {
			return this->fyp_name;
		}

		void printUndergraduate() {

			cout << this->getFirstName() << " " << this->getLastName() << " is a undergraduate student, his cgpa is " << this->getCGPA() << " and his final year topic is titled " << this->fyp_name;

		}

};

class Graduate : public Student {

	protected:

		string thesis_topic;

	public:

		Graduate(string f_name, string l_name, int age, float gpa, string topic_name) : Student(f_name, l_name, age, gpa), thesis_topic(topic_name) {

			cout << "Graduate() Called..." << endl;

		}

		~Graduate() {

			cout << "~Graduate() Called..." << endl;

		}

		void setThesisTopic(string topic_name) {
			this->thesis_topic = topic_name;
		}

		string getThesisTopic() {
			return this->thesis_topic;
		}

		void printGraduate() {

			cout << this->getFirstName() << " " << this->getLastName() << " is a graduate student, his cgpa is " << this->getCGPA() << " and his thesis topic is " << this->thesis_topic;

		}

};

class Faculty : public Person {

	private:

		int course_count;
		int extension_no;

	public:

		Faculty(string f_name, string l_name, int age, int cc, int number) : Person(f_name, l_name, age), course_count(cc), extension_no(number) {}

		void setCourseCount(int cc) {
			this->course_count = cc;
		}

		int getCourseCount() {
			return this->course_count;
		}

		void setExtNumber(int number) {
			this->extension_no = number;
		}

		int getExtNumber() {
			return this->extension_no;
		}

		void printFaculty() {

			cout << "Faculty Member Name: " << this->getFirstName() << " " << this->getLastName() << ", Age: " << this->getAge() << ", Number of Courses: " << this->course_count << ", Ext. " << this->extension_no;

		}

};

int main() {

	Student s("Ted", "Thompson", 22, 3.91);
	Faculty f("Richard", "Karp", 45, 2, 420);

	/*
	Output for Exercise 5:

	Person() Called...
	Student() Called...
	Undergraduate() Called...
	Person() Called...
	~Person() Called...
	~Undergraduate() Called...
	~Student() Called...
	~Person() Called...
	*/

	s.printStudent();
	cout << endl;
	f.printFaculty();
	cout << endl;

	Undergraduate u("Ted", "Thompson", 22, 3.91, "The Event Locator");
	Graduate g("Arnold", "Gates", 25, 3.01, "Distributed Algorithms");

	u.printUndergraduate();
	cout << endl;
	g.printGraduate();
	cout << endl;

	u.printStudent();
	cout << endl;

	/*
	Exercise 6:
	The code will not compile as first_name and last_name are private members and cannot be accessed from the Student class

	Exercise 9:
	The code will give errors on both protected and private inheritances since the printStudent() method of the Student class will not be accessible outside of the class since it will be protected and private respectively
	*/

}