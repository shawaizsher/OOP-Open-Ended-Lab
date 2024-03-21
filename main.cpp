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

    void assignCourse(Course* course);
    void removeCourse(Course* course);
    void viewCourses();
    void addCourse(Course* course);
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