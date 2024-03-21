#include<iostream>
#include<vector>
#include<algorithm>
#include<list>
#include<chrono>
#include<thread>
#include<limits>
#include<fstream> 
#include <sstream>
using namespace std;

class Course;

class Student {
    string studentID;
    string name;
    string email;


public:
    list<Course*> coursesEnrolled;
    Student(string s, string n, string e) : studentID(s), name(n), email(e) {}

    bool enrollCourse(Course* course);
    void dropCourse(Course* course);
    void viewCourses() const;

    string getName() const { return name; }
    string getID() const { return studentID; }
    string getEmail() const { return email; }
};

class Teacher {
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

    string const getID() const { return teacherID; }
    string getName() const { return name; }
    string getEmail() const { return email; }
};

class Course {
    string courseCode;
    string courseName;

    list<Student*> studentsEnrolled;


public:
    Teacher* teacher;
    int maxCapacity;
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

bool teacherLogin(vector<Teacher*>& teachers);
bool studentLogin(vector<Student*>& students);
void teacherRegister(vector<Teacher*>& teachers);
void studentRegister(vector<Student*>& students);
void studentMenu(Student* student, vector<Course*>& courses);
void teacherMenu(Teacher* teacher, vector<Course*>& courses);

bool Student::enrollCourse(Course* course) {
    if (course->studentsEnrolled.size() < course->maxCapacity) {
        coursesEnrolled.push_back(course);
        course->studentsEnrolled.push_back(this);
        return true;
    }
    else {
        return false;
    }
}

void Student::dropCourse(Course* course) {
    auto it = find(coursesEnrolled.begin(), coursesEnrolled.end(), course);
    if (it != coursesEnrolled.end()) {
        coursesEnrolled.erase(it);
        course->studentsEnrolled.erase(find(course->studentsEnrolled.begin(), course->studentsEnrolled.end(), this));
    }
}

void Student::viewCourses() const {
    if (coursesEnrolled.empty()) {
        cout << "You are not enrolled in any courses." << endl;
    }
    else {
        cout << "Enrolled Courses:" << endl;
        for (const auto& course : coursesEnrolled) {
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

void Teacher::viewCourses() const {
    if (coursesTaught.empty()) {
        cout << "You are not teaching any courses at this time." << endl;
    }
    else {
        cout << "Courses taught:" << endl;
        for (const auto& course : coursesTaught) {
            cout << "Course Code: " << course->getCode() << ", Course Name: " << course->getName() << endl;
        }
    }
}

void Teacher::addCourse(const string& code, const string& name, int maxCapacity) {
    Course* newCourse = new Course(code, name, this, maxCapacity);
    coursesTaught.push_back(newCourse);
}

void Course::addStudent(Student* student) {
    if (studentsEnrolled.size() < maxCapacity) {
        studentsEnrolled.push_back(student);
        student->enrollCourse(this);
        cout << "Student " << student->getName() << " enrolled in course " << courseName << endl;
    }
    else {
        cout << "Course " << courseName << " has reached its maximum capacity." << endl;
    }
}

void Course::removeStudent(Student* student)
{
    auto it = find(studentsEnrolled.begin(), studentsEnrolled.end(), student);
    if (it != studentsEnrolled.end()) {
        studentsEnrolled.erase(it);
        student->dropCourse(this);
        cout << "Student " << student->getName() << " removed from " << courseName << endl;
    }
    else {
        cout << "Student " << student->getName() << " is not enrolled in course " << courseName << endl;
    }
}

void Course::viewStudents() const {
    cout << "Students enrolled in course " << courseName << ":" << endl;
    for (auto student : studentsEnrolled) {
        cout << "Student ID: " << student->getID() << ", Name: " << student->getName() << ", Email: " << student->getEmail() << endl;
    }
}

bool teacherLogin(vector<Teacher*>& teachers) {
    string id;
    cout << "Enter teacher ID: ";
    cin >> id;
    for (auto teacher : teachers) {
        if (teacher->getID() == id) {
            return true;
        }
    }
    return false;
}

bool studentLogin(vector<Student*>& students)
{
    string id;
    cout << "Enter student ID: ";
    cin >> id;
    for (auto student : students)
    {
        if (student->getID() == id)
        {
            return true;
        }
    }
    return false;
}

void teacherRegister(vector<Teacher*>& teachers)
{
    string id, name, email;
    cout << "Enter teacher ID: ";
    cin >> id;
    cout << "Enter teacher name: ";
    cin >> name;
    cout << "Enter teacher email: ";
    cin >> email;
    Teacher* newTeacher = new Teacher(id, name, email);
    teachers.push_back(newTeacher);
}

void studentRegister(vector<Student*>& students)
{
    string id, name, email;
    cout << "Enter student ID: ";
    cin >> id;
    cout << "Enter student name: ";
    cin >> name;
    cout << "Enter student email: ";
    cin >> email;
    Student* newStudent = new Student(id, name, email);
    students.push_back(newStudent);
}

void studentMenu(Student* student, vector<Course*>& courses)
{
    student->viewCourses();
    while (true) {
        cout << "Student Menu:" << endl;
        cout << "1. Enroll in a Course" << endl;
        cout << "2. Drop a Course" << endl;
        cout << "3. View Enrolled Courses" << endl;
        cout << "4. Logout" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string code;
            cout << "Enter the course code to enroll: ";
            cin >> code;
            Course* courseToEnroll = nullptr;
            for (auto course : courses) {
                if (course->getCode() == code) {
                    courseToEnroll = course;
                    break;
                }
            }
            if (courseToEnroll) {
                if (student->enrollCourse(courseToEnroll)) {
                    cout << "Enrolled in course: " << courseToEnroll->getName() << endl;
                }
                else {
                    cout << "Failed to enroll. The course is full or already enrolled." << endl;
                }
            }
            else {
                cout << "Course with code " << code << " not found." << endl;
            }
            break;
        }
        case 2: {
            string code;
            cout << "Enter the course code to drop: ";
            cin >> code;
            Course* courseToDrop = nullptr;
            for (auto course : student->coursesEnrolled) {
                if (course->getCode() == code) {
                    courseToDrop = course;
                    break;
                }
            }
            if (courseToDrop) {
                student->dropCourse(courseToDrop);
                cout << "Dropped course: " << courseToDrop->getName() << endl;
            }
            else {
                cout << "You are not enrolled in a course with code " << code << "." << endl;
            }
            break;
        }
        case 3:
            student->viewCourses();
            break;
        case 4:
            cout << "Logging out..." << endl;
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void teacherMenu(Teacher* teacher, vector<Course*>& courses)
{
    while (true)
    {
        cout << "Teacher Menu" << endl;
        cout << "1. Assign Course" << endl;
        cout << "2. Remove Course" << endl;
        cout << "3. View Courses" << endl;
        cout << "4. Logout" << endl;
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "Available Courses:" << endl;
            for (int i = 0; i < courses.size(); ++i)
            {
                cout << i + 1 << ". " << courses[i]->getName() << endl;
            }
            cout << "Choose a course to assign (1-" << courses.size() << "): ";
            int courseChoice;
            cin >> courseChoice;
            if (courseChoice >= 1 && courseChoice <= courses.size()) {
                Course* selectedCourse = courses[courseChoice - 1];
                teacher->assignCourse(selectedCourse);
            }
            else {
                cout << "Invalid course choice." << endl;
            }
            break;
        }
        case 2:

        case 3:
            teacher->viewCourses();
            break;
        case 4:
            cout << "Logging out..." << endl;
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}


void loadStudents(const string& studentFile, vector<Student*>& students) {
    ifstream studentFileStream(studentFile);

    if (studentFileStream.is_open()) {
        string line;
        while (getline(studentFileStream, line)) {
            stringstream ss(line);
            string id, name, email;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, email, ',');
            students.push_back(new Student(id, name, email));
        }
        studentFileStream.close();
        cout << "Student data loaded successfully." << endl;
    }
    else {
        cout << "Error: Unable to open student file for loading data." << endl;
    }
}

void loadTeachers(const string& teacherFile, vector<Teacher*>& teachers) {
    ifstream teacherFileStream(teacherFile);

    if (teacherFileStream.is_open()) {
        string line;
        while (getline(teacherFileStream, line)) {
            stringstream ss(line);
            string id, name, email;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, email, ',');
            teachers.push_back(new Teacher(id, name, email));
        }
        teacherFileStream.close();
        cout << "Teacher data loaded successfully." << endl;
    }
    else {
        cout << "Error: Unable to open teacher file for loading data." << endl;
    }
}

void loadCourses(const string& courseFile, vector<Course*>& courses, const vector<Teacher*>& teachers) {
    ifstream courseFileStream(courseFile);

    if (courseFileStream.is_open()) {
        string line;
        while (getline(courseFileStream, line)) {
            stringstream ss(line);
            string code, name, teacherID;
            int maxCapacity;
            getline(ss, code, ',');
            getline(ss, name, ',');
            getline(ss, teacherID, ',');
            ss >> maxCapacity;

            Teacher* teacherPtr = nullptr;
            for (const auto& teacher : teachers) {
                if (teacher->getID() == teacherID) {
                    teacherPtr = teacher;
                    break;
                }
            }

            if (teacherPtr != nullptr) {
                courses.push_back(new Course(code, name, teacherPtr, maxCapacity));
            }
            else {
                cout << "Error: No matching teacher found for course " << code << endl;
            }
        }
        courseFileStream.close();
        cout << "Course data loaded successfully." << endl;
    }
    else {
        cout << "Error: Unable to open course file for loading data." << endl;
    }
}

void loadData(const string& studentFile, const string& teacherFile, const string& courseFile,
    vector<Teacher*>& teachers, vector<Student*>& students, vector<Course*>& courses) {
    loadStudents(studentFile, students);
    loadTeachers(teacherFile, teachers);
    loadCourses(courseFile, courses, teachers);
}


void saveData(const string& studentFile, const string& teacherFile, const string& courseFile,
    const vector<Teacher*>& teachers, const vector<Student*>& students, const vector<Course*>& courses) {
    ofstream studentFileStream(studentFile);
    ofstream teacherFileStream(teacherFile);
    ofstream courseFileStream(courseFile);

    if (!studentFileStream.is_open() || !teacherFileStream.is_open() || !courseFileStream.is_open()) {
        cout << "Error: Unable to open one or more files for saving data." << endl;
        return;
    }

    // Save students
    for (const auto student : students) {
        studentFileStream << student->getID() << ',' << student->getName() << ',' << student->getEmail() << '\n';
    }
    cout << "Student data saved successfully." << endl;

    // Save teachers
    for (const auto teacher : teachers)
	{
        teacherFileStream << teacher->getID() << ',' << teacher->getName() << ',' << teacher->getEmail() << '\n';
    }
    cout << "Teacher data saved successfully." << endl;

    for (const auto course : courses) {
        courseFileStream << course->getCode() << ',' << course->getName() << ','
            << course->teacher->getID() << ',' << course->maxCapacity << '\n';
    }
    cout << "Course data saved successfully." << endl;

    // Flush and close file streams
    studentFileStream.flush();
    teacherFileStream.flush();
    courseFileStream.flush();

    studentFileStream.close();
    teacherFileStream.close();
    courseFileStream.close();
}


int main()
{
    vector<Teacher*> teachers;
    vector<Student*> students;
    vector<Course*> courses;


    loadData("student.txt", "teacher.txt", "course.txt", teachers, students, courses);


    Course* course1 = new Course("CP101", "Computer Programming", nullptr, 30);
    Course* course2 = new Course("DSA201", "Data Structures and Algorithms", nullptr, 25);
    Course* course3 = new Course("LA301", "Linear Algebra", nullptr, 20);

    courses.push_back(course1);
    courses.push_back(course2);
    courses.push_back(course3);


    while (true)
    {
        
        cout << "Welcome to the Course Management System!" << endl;
        cout << "1. Teacher Login" << endl;
        cout << "2. Student Login" << endl;
        cout << "3. Teacher Register" << endl;
        cout << "4. Student Register" << endl;
        cout << "5. Exit" << endl;
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (teacherLogin(teachers))
            {
                teacherMenu(teachers.back(), courses);
                cout << "Teacher login successful!" << endl;
            }
            else {
                cout << "Teacher login failed!" << endl;
            }
            break;
        case 2:
            if (studentLogin(students))
            {
                studentMenu(students.back(), courses);
                cout << "Student login successful!" << endl;
            }
            else {
                cout << "Student login failed!" << endl;
            }
            break;
        case 3:
            teacherRegister(teachers);
            break;
        case 4:
            studentRegister(students);
            break;
        case 5:
            cout << "Exiting program..." << endl;
            saveData("student.txt", "teacher.txt", "course.txt", teachers, students, courses);
            for (auto teacher : teachers)
            {
                delete teacher;
            }
            for (auto student : students)
            {
                delete student;
            }
            for (auto course : courses)
            {
                delete course;
            }
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}