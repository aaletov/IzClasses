#pragma once
#include <string>

class Student
{
private:
	std::string lastNameInitials;
	std::string specialty;
	std::string groupNumber;
	int semester;
	int* performance;
public:
	Student();
	int getSemester();
	Student(const std::string& i_lastNameInitials, const std::string& i_specialty, const std::string& i_groupNumber, const int i_semester, int* const i_performance);
	Student(const Student& student);
	~Student();
	int getSumPerformance();
	std::string& getSpecialty();
	std::string& getGroupNumber();
	std::string& getName();
	Student operator+(const int right);
	friend Student operator-(Student& student, int right);
	bool operator>(Student& student2);
	friend bool operator<(Student& student1, Student& student2);
	friend bool operator==(Student& student1, Student& student2);
	Student& operator=(Student& student);
	Student& operator++();
	friend Student& operator++(Student& student, int);
	friend std::ostream& operator<< (std::ostream& out, Student& student);
	friend std::istream& operator>> (std::istream& in, Student& student);
};

