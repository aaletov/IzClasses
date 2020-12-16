#pragma once
#include "Student.h"
#include "MyVector.h"

void openAllStudents(const std::string& PATH, MyVector<Student>& myVector);
Student openNewStudent(std::ifstream& in);
void getStringBeforeSpace(std::ifstream& in, std::string& str);
int getIntBeforeSpace(std::ifstream& in);
void checkStudent(Student& student);