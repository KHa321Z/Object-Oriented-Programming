#include <iostream>

using namespace std;

class Course {

    private:

        string ID;
        string teacherID;
        string title;

    public:

        Course(string tit="Default", string id="") : title(tit), ID(id) {}

        void setTeacherID(string id) {
            this->teacherID = id;
        }

        void display() {
            cout << "Title: " << this->title << " ID: " << this->ID << " Teacher ID: " << this->teacherID << endl;
        }

};

class Teacher {

    private:

        string ID;
        string name;
        Course** courses;
        int courseCount;

    public:

        Teacher(string id="", string naam="default") : ID(id), name(naam), courses(0), courseCount(0) {}

        void addCourse(Course &course) {

            course.setTeacherID(this->ID);
            Course **temp = new Course* [++courseCount];

            for (int i = 0; i < courseCount - 1; i++)
                temp[i] = this->courses[i];

            temp[courseCount - 1] = &course;

            delete[] this->courses;
            
            this->courses = temp;

        }

        void display() {

            cout << "Teacher ID: " << this->ID << " Name: " << this->name << endl;
            cout << "Courses Taught:" << endl;

            for (int i = 0; i < courseCount; i++)
                courses[i]->display();

        }

};

int main() {

    Course c1("Programming Fundamentals", "CS101");
    Course c2("Data Structures", "CS201");
    Course c3("Algorithms", "CS301");
    Course c4("Object Oreinted Programming", "CS401");

    Teacher t1("T1", "Mr. A");
    Teacher t2("T2", "Mr. B");
    t1.addCourse(c1);
    t1.addCourse(c2);
    t2.addCourse(c3);
    t2.addCourse(c4);
    t1.display();
    cout << endl;
    t2.display();
    cout << endl;

    return 0;

}