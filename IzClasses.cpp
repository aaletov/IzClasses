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

void reduceSpecs(MyVector<Student>& students, MyVector<MyVector<MyVector<char>>>& specsCodes);
std::string codeFromNumber(std::string& groupNumber);

template<typename T>
void vectorToArray(MyVector<T> inVector, T* array)
{
    try
    {
        for (int i = 0; i < inVector.getArrayLen(); i++)
        {
            array[i] = inVector;
        }
    }
    catch (std::exception&)
    {
        throw MemException();
    }
    
}

template<typename T>
void copyDynamic(T* in, T* out)
{
    std::is_pointer<T>(in);
}

//int main()
//{
//    std::string ree = "ree";
//
//    char** cRee = new char*[2];
//    cRee[0] = new char[ree.length() + 1];
//
//    strToCString(ree, cRee[0]);
//    ree = "eeR";
//    std::cout << cRee[0];
//
//    return 0;
//}

int main()
{
    setlocale(LC_ALL, "RUS");
    const std::string PATH = "students.txt";
    const std::string OUT_PATH = "out.txt";
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

    // Пункт 5
    
    int nStudColumns = 5;

    const std::string fields[] = { "Имя", "Специальность", "Группа", "Семестр", "Успеваемость" };

    char** studHeaders = new char* [nStudColumns];

    for (int i = 0; i < nStudColumns; i++)
    {
        studHeaders[i] = new char[fields[0].length() + 1];
        strToCString(fields[i], studHeaders[i]);
    }

    char*** studInfo = new char** [students.getArrayLen()];
    std::string& tempStudString = students[0].getName();
    int tempStudInt;

    for (int i = 0; i < students.getArrayLen(); i++)
    {
        studInfo[i] = new char* [nStudColumns];

        tempStudString = students[i].getName();
        studInfo[i][0] = new char [tempStudString.length() + 1];
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

    int* columnsStudLen = new int[5];
    for (int i = 0; i < 5; i++)
    {
        columnsStudLen[i] = 20;
    }
    columnsStudLen[1] = 30;

    Table studTable(studHeaders, studInfo, 5, columnsStudLen, students.getArrayLen());
    studTable.printTable(std::cout);
    
    // Пункт 6

    MyVector<MyVector<MyVector<char>>> specsCodes;
    reduceSpecs(students, specsCodes);

    std::string codeHeaderString = "Специальность";
    std::string specHeaderString = "Код";
    char* codeHeader = new char[codeHeaderString.length() + 1]; 
    char* specHeader = new char[specHeaderString.length() + 1]; 
    strToCString(codeHeaderString, codeHeader);
    strToCString(specHeaderString, specHeader);
    char** headers = new char* [nCodeColumns];
    headers[0] = codeHeader;
    headers[1] = specHeader;

    char*** info = new char** [specsCodes.getArrayLen()];
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

    int* columnsLen = new int[2];
    columnsLen[0] = 50;
    columnsLen[1] = 50;

    Table codes(headers, info, 2, columnsLen, specsCodes.getArrayLen());
    codes.printTable(std::cout);

    return 0;
}

void reduceSpecs(MyVector<Student>& students, MyVector<MyVector<MyVector<char>>>& specsCodes)
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
