#include <string>
#include <iostream>
#include "Student.h"
#include "Exceptions.h"
#include "Check.h"

Student::Student() 
{
	semester = 1;
	performance = new int[5];
	for (int i = 0; i < 5; i++)
	{
		performance[i] = NULL;
	}
}

int Student::getSemester()
{
	return semester;
}

Student::Student(const std::string& i_lastNameInitials, const std::string& i_specialty, const std::string& i_groupNumber, const int i_semester, int* const i_performance)
{
	if (!(isLastNameInitials(i_lastNameInitials) && isCorrectSpecialty(i_specialty) && isCorrectNumber(i_groupNumber) && i_semester >= 1 && i_semester <= 8))
	{
		throw StudentException();
	}
	lastNameInitials = i_lastNameInitials;
	specialty = i_specialty;
	groupNumber = i_groupNumber;
	semester = i_semester;
	performance = new int[5];
	for (int i = 0; i < 5; i++)
	{
		if (i_performance[i] < 0 || i_performance[i] > 10)
		{
			throw StudentException();
		}
		performance[i] = i_performance[i];
	}
}

Student::Student(const Student& student)
{
	lastNameInitials = student.lastNameInitials;
	specialty = student.specialty;
	groupNumber = student.groupNumber;
	semester = student.semester;
	performance = new int[5];
	for (int i = 0; i < 5; i++)
	{
		performance[i] = student.performance[i];
	}
}

Student::~Student()
{
	if (performance != nullptr)
	{
		delete[] performance;
	}
}

int Student::getSumPerformance()
{
	int sum = 0;
	for (int i = 0; i < 5; i++)
	{
		sum += performance[i];
	}
	return sum;
}

Student Student::operator+(const int right)
{
	performance += right;
	return *this;
}

Student operator-(Student& student, int right)
{
	student.performance -= right;
	return student;
}

bool Student::operator>(Student& student2)
{
	return this->getSumPerformance() > student2.getSumPerformance();
}

bool operator<(Student& student1, Student& student2)
{
	return student1.getSumPerformance() > student2.getSumPerformance();
}

bool operator==(Student& student1, Student& student2)
{
	return student1.getSumPerformance() == student2.getSumPerformance();
}

Student& Student::operator=(Student& student)
{
	lastNameInitials = student.lastNameInitials;
	specialty = student.specialty;
	groupNumber = student.groupNumber;
	semester = student.semester;
	for (int i = 0; i < 5; i++)
	{
		performance[i] = student.performance[i];
	}
	return *this;
}

Student& Student::operator++()
{
	semester++;
	return *this;
}

Student& operator++(Student& student, int)
{
	static Student& temp(student);
	student.semester++;
	return temp;
}

std::ostream& operator<< (std::ostream& out, Student& student)
{
	out << "Имя: " << student.lastNameInitials << std::endl;
	out << "Специальность: " << student.specialty << std::endl;
	out << "Номер группы: " << student.groupNumber << std::endl;
	out << "Семестр: " << student.semester << std::endl;
	out << "Успеваемость: ";
	for (int i = 0; i < 5; i++)
	{
		out << student.performance[i] << ' ';
	}
	out << std::endl;
	return out;
}

std::istream& operator>> (std::istream& in, Student& student)
{
	std::string temp;
	in >> student.lastNameInitials;
	for (int i = 0; i < 2; i++)
	{
		in >> temp;
		student.lastNameInitials += ' ' + temp;
	}
	in >> student.specialty;
	in >> student.groupNumber;
	in >> student.semester;
	for (int i = 0; i < 5; i++)
	{
		in >> student.performance[i];
	}
	return in;
}

std::string& Student::getSpecialty()
{
	return specialty;
}

std::string& Student::getGroupNumber()
{
	return groupNumber;
}

std::string& Student::getName()
{
	return lastNameInitials;
}

void Student::setPerformance(int i, int value)
{
	if (value > -1 && value < 11)
	{
		performance[i] = value;
	}
	else
	{
		throw "Некорректное значение";
	}
}