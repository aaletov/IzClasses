#include <iostream>
#include <fstream>
#include <iomanip>
#include "Student.h"
#include "MyVector.h"
#include "InsertSort.h"
#include "Utils.h"
#include "Table.h"
#include "Open.h"
#include "Exceptions.h"

void getSpecsSet(MyVector<Student>& students, MyVector<MyVector<MyVector<char>>>& specsCodes);
void specsToMatrix(MyVector<MyVector<MyVector<char>>>& specsCodes, char***& info);
std::string codeFromNumber(std::string& groupNumber);
void studentsToMatrix(MyVector<Student>& students, char***& studInfo);
void formHeadersRow(const std::string fields[], char**& headers, int nColumns);

int main()
{
    setlocale(LC_ALL, "RUS");
    std::cout << "Введите название файла" << std::endl;
    std::string PATH;
    std::cin >> PATH;
    const std::string OUT_PATH = "out.txt";
    std::ofstream out;
    out.open(OUT_PATH, std::ios::out);
    const int lenCodeColumns[] = { 31, 61 };
    const int nCodeColumns = 2;

    // Пункт 3

    MyVector<Student> students;

    openAllStudents(PATH, students);

    // Пункт 5

    sort(students, students.getArrayLen());
    
    int nStudColumns = 5;

    std::string fields[] = { "Имя", "Специальность", "Группа", "Семестр", "Успеваемость" };

    char** studHeaders = nullptr;
    formHeadersRow(fields, studHeaders, nStudColumns);

    char*** studInfo = nullptr;
    studentsToMatrix(students, studInfo);

    int* columnsStudLen = new int[5];
    for (int i = 0; i < 5; i++)
    {
        columnsStudLen[i] = 20;
    }
    columnsStudLen[1] = 30;

    Table studTable(studHeaders, studInfo, 5, columnsStudLen, students.getArrayLen());
    studTable.printTable(out);

    // Пункт 6

    MyVector<MyVector<MyVector<char>>> specsCodes;
    getSpecsSet(students, specsCodes);

    const int nColumns = 2;
    std::string strHeaders[] = { "Специальность", "Код" };
    char** headers;
    formHeadersRow(strHeaders, headers, nColumns);
    
    char*** info;
    specsToMatrix(specsCodes, info);

    int* columnsLen = new int[nColumns];
    columnsLen[0] = 50;
    columnsLen[1] = 50;

    Table codes(headers, info, nColumns, columnsLen, specsCodes.getArrayLen());
    codes.printTable(out);
    out.close();

    return 0;
}

void specsToMatrix(MyVector<MyVector<MyVector<char>>>& specsCodes, char***& info)
{
    info = new char** [specsCodes.getArrayLen()];
    for (int i = 0; i < specsCodes.getArrayLen(); i++)
    {
        info[i] = new char* [specsCodes[i].getArrayLen()];
        for (int j = 0; j < specsCodes[i].getArrayLen(); j++)
        {
            info[i][j] = new char[specsCodes[i][j].getArrayLen() + 1];
            info[i][j] = specsCodes[i][j].getDynamic();
            info[i][j][specsCodes[i][j].getArrayLen()] = 0;
        }
    }
}

void formHeadersRow(const std::string fields[], char**& headers, int nColumns)
{
    headers = new char*[nColumns];
    for (int i = 0; i < nColumns; i++)
    {
        headers[i] = new char[fields[0].length() + 1];
        strToCString(fields[i], headers[i]);
    }
}

void studentsToMatrix(MyVector<Student>& students, char***& studInfo)
{
    const int nStudColumns = 5;
    studInfo = new char** [students.getArrayLen()];
    std::string& tempStudString = students[0].getName();
    int tempStudInt;

    for (int i = 0; i < students.getArrayLen(); i++)
    {
        studInfo[i] = new char* [nStudColumns];

        tempStudString = students[i].getName();
        studInfo[i][0] = new char[tempStudString.length() + 1];
        strToCString(tempStudString, studInfo[i][0]);

        tempStudString = students[i].getSpecialty();
        studInfo[i][1] = new char[tempStudString.length() + 1];
        strToCString(tempStudString, studInfo[i][1]);

        tempStudString = students[i].getGroupNumber();
        studInfo[i][2] = new char[tempStudString.length() + 1];
        strToCString(tempStudString, studInfo[i][2]);

        tempStudInt = students[i].getSemester();
        studInfo[i][3] = new char[intLen(tempStudInt) + 1];
        strcpy(studInfo[i][3], intToCStr(tempStudInt));

        tempStudInt = students[i].getSumPerformance();
        studInfo[i][4] = new char[intLen(tempStudInt) + 1];
        strcpy(studInfo[i][4], intToCStr(tempStudInt));
    }
}

void getSpecsSet(MyVector<Student>& students, MyVector<MyVector<MyVector<char>>>& specsCodes)
{
    bool isCodeIn = false;

    for (int i = 0; i < students.getArrayLen(); i++)
    {
        MyVector<MyVector<char>> toFind(2);
        std::string& tempSpec = students[i].getSpecialty();
        std::string& tempNumber = students[i].getGroupNumber();
        std::string tempCode = codeFromNumber(tempNumber);
        
        for (int j = 0; j < tempSpec.length(); j++)
        {
            toFind[0].push_back(tempSpec[j]);
        }

        

        for (int j = 0; j < tempCode.length(); j++)
        {
            toFind[1].push_back(tempCode[j]);
        }

        isCodeIn = specsCodes.contains(toFind);
        
        if (isCodeIn)
        {
            continue;
        }
        else
        {
            specsCodes.push_back(toFind);
        }
    }
}

std::string codeFromNumber(std::string& groupNumber)
{
    int pos = groupNumber.find('/');
    std::string code = groupNumber.substr(0, pos);
    return code;
}
