#include <iostream>
#include <fstream>
#include <iomanip>
#include "Student.h"
#include "MyVector.h"
#include "InsertSort.h"
#include "Utils.h"
#include "Table.h"
#include "Open.h"

MyVector<char**>& reduceSpecs(MyVector<Student>& students);
void codeFromNumber(char* groupNumber, char* code);

int main()
{
    setlocale(LC_ALL, "RUS");
    const std::string PATH = "students.txt";
    const int lenCodeColumns[] = { 31, 61 };
    const int nCodeColumns = 2;
    // Пункт 3
    MyVector<Student> students;

    openAllStudents(PATH, students);
    // Пункт 5
    sort(students, students.getArrayLen());
    // Пункт 4
    std::cout << "Лучший студент:" << std::endl << students[students.getArrayLen() - 1] << std::endl << std::endl;
    std::cout << "Отсортированный список:" << std::endl << std::endl;
    for (int i = 0; i < students.getArrayLen(); i++)
    {
        std::cout << students[i] << std::endl;
    }


    // Пункт 6
    MyVector<char**>& specsCodes = reduceSpecs(students);

    int nOfStrings = cStrToInt(specsCodes[0][0]);
    
    for (int i = 0; i < nOfStrings; i++)
    {
        std::cout << "Code: " << specsCodes[i][0] << std::endl;
        std::cout << "Spec: " << specsCodes[i][1] << std::endl;
    }


    std::string codeHeaderString = "Код";
    std::string specHeaderString = "Специальность";
    char* codeHeader = new char[codeHeaderString.length() + 1]; 
    char* specHeader = new char[specHeaderString.length() + 1]; 
    strToCString(codeHeaderString, codeHeader);
    strToCString(specHeaderString, specHeader);
    char** headers = new char* [nCodeColumns];
    headers[0] = codeHeader;
    headers[1] = specHeader;

    return 0;
}

MyVector<char**>& reduceSpecs(MyVector<Student>& students)
{
    MyVector<char**> specs;

    char** stringNOfStrings = new char* [2];
    char* nOfStrings = new char[1000];
    specs.push_back(stringNOfStrings);

    char* tempCode;
    int tempLength;
    std::string buf;
    char** tempString = new char* [2];
    bool isCodeIn;

    for (int i = 0; i < students.getArrayLen(); i++)
    {
        buf = students[i].getGroupNumber();
        tempLength = buf.length();
        tempCode = new char[tempLength];
        tempString[0] = new char[tempLength];
        strToCString(buf, tempCode);
        codeFromNumber(tempCode, tempString[0]);

        buf = students[i].getSpecialty();
        tempLength = buf.length();
        tempString[1] = new char[tempLength];
        strToCString(buf, tempString[1]);

        isCodeIn = false;
        for (int j = 0; j < specs.getArrayLen(); j++)
        {
            if (specs[j][0] == tempString[0])
            {
                isCodeIn = true; 
                break;
            }
        }

        if (isCodeIn)
        {
            continue;
        }
        else
        {
            specs.push_back(tempString);
        }
        nOfStrings = intToCStr(specs.getArrayLen());
        return specs;
    }
}

void codeFromNumber(char* groupNumber, char* code)
{
    int pos = sizeof(strstr(groupNumber, "/") - groupNumber) / sizeof(groupNumber[0]);

    std::cout << pos << std::endl;

    for (int i = 0; i < pos; i++)
    {
        code[i] = groupNumber[i];
    }
    code[pos] = 0;
}
