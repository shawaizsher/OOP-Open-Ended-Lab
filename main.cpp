#include<iostream>
#include<vector>
#include<algorithm>
#include<list>
#include<chrono>
#include<thread>
#include<limits>
using namespace std;

class Course;

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
    string teacherID;
    string name;
    string email;
    vector<Course*> coursesTaught;

public:
    Teacher(string teacherID, string name, string email) : teacherID(teacherID), name(name), email(email) {}

    void assignCourse(Course* course);
    void removeCourse(Course* course);
    void viewCourses() const;
    void addCourse(const string& code, const string& name, int maxCapacity);

    string const getID() const {return teacherID;}
};

class Course
{
    string courseCode;
    string courseName;
    Teacher* teacher;
    list<Student*> studentsEnrolled;
    int maxCapacity;

public:
    Course(string courseCode, string courseName, Teacher* teacher, int maxCapacity)
        : courseCode(courseCode), courseName(courseName), teacher(teacher), maxCapacity(maxCapacity) {}

    void addStudent(Student* student);
    void removeStudent(Student* student);
    void viewStudents() const;

    const string& getCode() const { return courseCode; }
    const string& getName() const { return courseName; }

    friend class Student;
    friend class Teacher;
};

vector<Teacher> teachers;
vector<Student> students;

bool teacherLogin();
bool studentLogin();
void teacherRegister();
void studentRegister();

bool Student::enrollCourse(Course* course)
{
    if (course->studentsEnrolled.size() < course->maxCapacity) 
	{
        coursesEnrolled.push_back(course);
        course->studentsEnrolled.push_back(this);
        return true;
    } else 
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
    } 
	else 
	{
        cout << "Courses taught:" << endl;
        for (const auto& course : coursesTaught) 
		{
            cout << "Course Code: " << course->getCode() << ", Course Name: " << course->getName() << endl;
        }
    }
}

void Teacher::addCourse(const string& code, const string& name, int maxCapacity) 
{
    Course* newCourse = new Course(code, name, this, maxCapacity);
    coursesTaught.push_back(newCourse);
}

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
        cout << "Student " << student->getName() << " removed from " << courseName << endl;
    } else
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

void returnToMainMenu()
 {
    cout << "\nReturning to the main menu..." << endl;
    this_thread::sleep_for(chrono::seconds(3));
}

void studentMenu(const Student& student) {
    cout << "\nWelcome, " << student.getName() << "!" << endl;
    cout << "1. View enrolled courses" << endl;
    cout << "2. Enroll in a new course" << endl;
    cout << "3. Drop a course" << endl;
    cout << "4. Logout" << endl;
    cout << "Choose an option: ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            student.viewCourses();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            returnToMainMenu();
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
    }
}

void teacherMenu(const Teacher& teacher)
 {
    cout << "\nWelcome, " << teacher.getID() << "!" << endl;
    cout << "1. View courses taught" << endl;
    cout << "2. Add a new course" << endl;
    cout << "3. Remove a course" << endl;
    cout << "4. Logout" << endl;
    cout << "Choose an option: ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            teacher.viewCourses();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            returnToMainMenu();
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
    }
}

bool teacherLogin() {
    string id;
    cout << "Enter teacher ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (const auto& teacher : teachers)
	 {
        if (teacher.getID() == id) {
            cout << "Login successful!" << endl;
            this_thread::sleep_for(chrono::seconds(3));
            return true;
        }
    }
    cout << "Teacher not found!" << endl;
    returnToMainMenu();
    return false;
}

bool studentLogin() {
    string id;
    cout << "Enter student ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (const auto& student : students) {
        if (student.getID() == id) {
            cout << "Login successful!" << endl;
            this_thread::sleep_for(chrono::seconds(3));
            return true;
        }
    }
    cout << "Student not found!" << endl;
    returnToMainMenu();
    return false;
}

void teacherRegister() {
    string id, name, email;
    cout << "Enter teacher ID: ";
    cin >> id;
    cout << "Enter teacher name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter teacher email: ";
    cin >> email;
    Teacher newTeacher(id, name, email);
    teachers.push_back(newTeacher);
    cout << "Teacher registered successfully!" << endl;
    cout << "\n->Going to main menu in a moment...." << endl;
    this_thread::sleep_for(chrono::seconds(3));
}

void studentRegister() {
    string id, name, email;
    cout << "Enter student ID: ";
    cin >> id;
    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter student email: ";
    cin >> email;
    Student newStudent(id, name, email);
    students.push_back(newStudent);
    cout << "Student registered successfully!" << endl;

    cout << "\n-> Going to main menu in a moment...." << endl;
    this_thread::sleep_for(chrono::seconds(3));
}

int main() {
    do {
        system("cls");
        cout << "University Management Portal" << endl;
        cout << "==============================" << endl;
        cout << "1. Login as Student" << endl;
        cout << "2. Login as Teacher" << endl;
        cout << "--------------------------" << endl;
        cout << "3. Register as Student" << endl;
        cout << "4. Register as Teacher" << endl;
        cout << "==============================" << endl;
        cout << "-> Enter option: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                bool loggedIn = false;
                while (!loggedIn) {
                    cout << "Student Login:" << endl;
                    if (studentLogin()) {
                        loggedIn = true;
                        studentMenu(students.back());
                    } else {
                        cout << "Login failed. Try again." << endl;
                    }
                }
            }
            break;
            case 2: {
                bool loggedIn = false;
                while (!loggedIn) {
                    cout << "Teacher Login:" << endl;
                    if (teacherLogin()) {
                        loggedIn = true;
                        teacherMenu(teachers.back());
                    } else {
                        cout << "Login failed. Try again." << endl;
                    }
                }
            }
            break;
            case 3:
                studentRegister();
                break;
            case 4:
                teacherRegister();
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (true);
    return 0;
}
