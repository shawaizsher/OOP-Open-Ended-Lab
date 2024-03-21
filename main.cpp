#include<iostream>      
#include<fstream>
#include<vector>
#include<algorithm>
#include<list>

using namespace std;

class Course;  // declaration here 

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
    void addCourse(Course* course);
    {
    	
	}
    const string& getID() const 
	{
        return teacherID;
    }
};

class Course 
{
    
};


void Teacher::assignCourse() 
{
    
}

void Teacher::removeCourse()
{
   
}

void Teacher::viewCourses()
{
   
}

void Teacher::addCourse() 
{
	
}


int main()
{
	
}