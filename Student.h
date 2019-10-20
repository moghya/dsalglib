#include<iostream>
#include<string>
using namespace std;
class Student
{
	private:
		string student_name;
		int roll_no;
		int registration_no;
		string department;
		float cgpa;
	public:
		Student(const string student_name = "ABC", const int roll_no = 100, const int registration_no = 1710027,
		const string department = "CSE", const float cgpa = 9.5);
		void setDetails(const string student_name, const int roll_no, const int registration_no,
			const string department, const float cgpa);
		void print() const;
};
