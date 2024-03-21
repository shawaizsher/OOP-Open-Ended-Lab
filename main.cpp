#include<iostream>      
#include<fstream>
#include<vector>
#include<algorithm>
#include<list>

using namespace std;

class Course; 

class Student 
{
	
  
};

class Teacher 
{
    string teacherID;
    string name;
    string email;
    vector<Course*> coursesTaught;
    vector<Course*> coursesAdded;

public:
    Teacher(string teacherID, string name, string email) : teacherID(teacherID), name(name), email(email) {}


    void assignCourse(Course* course)
    {
    	coursesTaught.push_back(course);
	}
	
    void removeCourse(Course* course)
    {
    	auto it = find(coursesTaught.begin(),courseTaught.end(),course)
    	if(it != coursesTaught.end())
    	{
    		coursesTaught.erase(it);
		}
	}
    void viewCourses() const 
    {
    	if(coursesTaught.empty()) // if no courses are being taught by the teacher
    	{
    		cout << "You are not teaching any course at this time " << endl; 
		}
		else
		{
			cout << "->Courses taught: " << endl ;
			for(const auto &course : courseTaught)
			{
				cout << "Course code: " << course->getCode() << ", Course Name: " << course->courseName << ", " << course->teacherID << "," << course->maxCapacity << endl ;
			}
		}
	}
    const string& getID() const 
	{
        return teacherID;
    }
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
	
}