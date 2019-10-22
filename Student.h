//student class header file;
#include<iostream>
#include<string>
using namespace std;
class Student
{
	private:
		string student_name;	//student name;
		int roll_no;			//institute roll no;
		int registration_no;	//institute registration no;
		string department;		//department of the student;
		string college_name;	//institute name;
		float cgpa;				//academic cgpa;
	public:
		//constructor of student class;
		Student(const string student_name = "ABC", const int roll_no = 100, const int registration_no = 1710027,
		const string department = "CSE", const float cgpa = 9.5, const string college_name = "IIT KGP");
		void setDetails(const string student_name, const int roll_no, const int registration_no,
			const string department, const float cgpa, const string college_name);
		void print() const;
};
