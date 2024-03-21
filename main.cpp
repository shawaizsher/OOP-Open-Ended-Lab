#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

class Course;
class Teacher;

class Student
{
	private:
		string studentID;
		string name;
		string email;
		list<Course*> coursesEnrolled;
		
	public:
		Student(string studentID, string name, string email): studentID(studentID), name(name), email(email) {}
		
		
		
};


class Course
{
	 private:
	 	string courseCode;
	 	string courseName;
	 	Teacher* teacher;
	 	
	 	list<Student*> studentsEnrolled;
	 	int maxCapacity;
	 	
	 	
	 	
	 public:
	 	
	 	Course(string courseCode, string courseName, Teacher* teacher, int maxCapacity) : courseCode(courseCode), courseName(courseName), teacher(teacher), maxCapacity(maxCapacity) {}
	 
	 	void addStudent(Student* student)
	 	{	
	 		if (studentsEnrolled.size() < maxCapacity) 
			{
       			studentsEnrolled.push_back(student);
        
        		student->enrolCourse(this);
        		cout << "Student " << student->getName() << " enrolled in course " << courseName << endl;
    		} 
			else
			{
        		cout << "Course " << courseName << " has reached its maximum capacity." << endl;
    		}
	 	}	
	 
	 	void removeStudent(Student* student)
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
	 
	 	void viewStudents(Student* student)
	 	{
	 		cout << "Students enrolled in course " << courseName << ":" << endl;
    
    		for (auto student : studentsEnrolled) 
			{
        		cout << "Student ID: " << student->getStudentID() << ", Name: " << student->getName() << ", Email: " << student->getEmail() << endl;
    		}
		}
};
int main()
{
     return 0;
}
