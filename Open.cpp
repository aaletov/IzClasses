#include "Student.h"
#include "MyVector.h"
#include "Exceptions.h"
#include "Open.h"
#include <iostream>
#include <fstream>

void getStringBeforeSpace(std::ifstream& in, std::string& str)
{
    in >> str;
    if (str.empty())
    {
        in.close();
        throw StrException();
    }
}

int getIntBeforeSpace(std::ifstream& in)
{
    int n;
    in >> n;
    if (in.fail())
    {
        in.close();
        throw StrException();
    }
    return n;
}

void openAllStudents(const std::string& PATH, MyVector<Student>& myVector)
{
    std::ifstream in;
    try
    {
        in.open(PATH, std::ios::in);
        if (in.fail())
        {
            throw FileException();
        }
        int i = 0;
        while (true)
        {
            Student temp = openNewStudent(in);
            myVector.push_back(temp);
            i++;
        }
    }
    catch (StrException& err)
    {
        in.close();
        std::cout << err.getError() << std::endl << std::endl;
    }
    catch (FileException& err)
    {
        in.close();
        std::cout << err.getError() << std::endl << std::endl;
    }
    catch (StudentException& err)
    {
        in.close();
        std::cout << err.getError() << std::endl << std::endl;
    }
}

Student openNewStudent(std::ifstream& in)
{
    static int alreadyRead = 0;
    std::string str = "";
    std::string lastName;
    std::string initials1;
    std::string initials2;
    std::string specialty;
    std::string groupNumber;
    int semester;
    int* performance = new int[5];

    getStringBeforeSpace(in, lastName);
    getStringBeforeSpace(in, initials1);
    getStringBeforeSpace(in, initials2);
    getStringBeforeSpace(in, specialty);
    getStringBeforeSpace(in, groupNumber);
    semester = getIntBeforeSpace(in);
    for (int i = 0; i < 5; i++)
    {
        performance[i] = getIntBeforeSpace(in);
    }
    std::string lastNameInitials = lastName + ' ' + initials1 + ' ' + initials2;
    alreadyRead++;
    return Student(lastNameInitials, specialty, groupNumber, semester, performance);
}

