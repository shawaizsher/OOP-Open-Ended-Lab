#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<list>

using namespace std;

class Student;
class Teacher ;
class Course
{

    string courseCode;
    string courseName;
    Teacher* teacher;
    list<Student*> studentsEnrolled;
    int maxCapacity;

public:
    Course(string courseCode, string courseName, Teacher* teacher, int maxCapacity)  : courseCode(courseCode), courseName(courseName), teacher(teacher), maxCapacity(maxCapacity) {}

    void addStudent(Student* student);
    void removeStudent(Student* student);
    void viewStudents() const;

    const string& getCode() const { return courseCode; }
    const string& getName() const { return courseName; }

    friend class Student; // so that private members can be acccessed
};

class Student 
{

    string studentID;
    string name;
    string email;
    list<Course*> coursesEnrolled;

public:
    Student(string s, string n, string e) : studentID(s), name(n), email(e) {}

    bool enrollCourse(Course* course);
    void dropCourse(Course* course);
    void viewCourses() const;

    string getName() const { return name; }
    string getID() const { return studentID; }
    string getEmail() const { return email; }
};

class Teacher
 {
private:
    string teacherID;
    string name;
    string email;
    vector<Course*> coursesTaught;

public:
    Teacher(string teacherID, string name, string email) : teacherID(teacherID), name(name), email(email) {}

    void assignCourse(Course* course);
    void removeCourse(Course* course);
    void viewCourses() const;

    const string& getID() const { return teacherID; }
};


// definition of course class members
void Course::addStudent(Student* student)
 {
    if (studentsEnrolled.size() < maxCapacity) 
	{
        studentsEnrolled.push_back(student);
        student->enrollCourse(this);
        cout << "Student " << student->getName() << " enrolled in course " << courseName << endl;
    } else
	{
        cout << "Course " << courseName << " has reached its maximum capacity." << endl;
    }
}

void Course::removeStudent(Student* student)
{
    auto it = find(studentsEnrolled.begin(), studentsEnrolled.end(), student);
    if (it != studentsEnrolled.end())
	 {
        studentsEnrolled.erase(it);
        student->dropCourse(this);
        cout << "Student " << student->getName() << " removed from course " << courseName << endl;
    } 
	else 
	{
        cout << "Student " << student->getName() << " is not enrolled in course " << courseName << endl;
    }
}

void Course::viewStudents() const
{
    cout << "Students enrolled in course " << courseName << ":" << endl;
    for (auto student : studentsEnrolled)
	{
        cout << "Student ID: " << student->getID() << ", Name: " << student->getName() << ", Email: " << student->getEmail() << endl;
    }
}

bool Student::enrollCourse(Course* course)
{
    if (course->studentsEnrolled.size() < course->maxCapacity)
	 {
        coursesEnrolled.push_back(course);
        course->studentsEnrolled.push_back(this);
        return true;
    } 
	else 
	{
        return false;
    }
}

void Student::dropCourse(Course* course)
{
    auto it = find(coursesEnrolled.begin(), coursesEnrolled.end(), course);
    if (it != coursesEnrolled.end()) 
	{
        coursesEnrolled.erase(it);
        course->studentsEnrolled.erase(find(course->studentsEnrolled.begin(), course->studentsEnrolled.end(), this));
    }
}

void Student::viewCourses() const 
{
    if (coursesEnrolled.empty()) 
	{
        cout << "You are not enrolled in any courses." << endl;
    } 
	else
	 {
        cout << "Enrolled Courses:" << endl;
        for (const auto& course : coursesEnrolled) 
		{
            cout << "Course Code: " << course->getCode() << ", Course Name: " << course->getName() << endl;
        }
    }
}

void Teacher::assignCourse(Course* course)
{
    coursesTaught.push_back(course);
}

void Teacher::removeCourse(Course* course)
{
    auto it = find(coursesTaught.begin(), coursesTaught.end(), course);
    if (it != coursesTaught.end()) 
	{
        coursesTaught.erase(it);
    }
}

void Teacher::viewCourses() const 
{
    if (coursesTaught.empty())
	 {
        cout << "You are not teaching any courses at this time." << endl;
    } else
	 {
        cout << "Courses taught:" << endl;
        for (const auto& course : coursesTaught) 
		{
            cout << "Course Code: " << course->getCode() << ", Course Name: " << course->getName() << endl;
        }
    }
}

int main() 
{
    return 0;
}
