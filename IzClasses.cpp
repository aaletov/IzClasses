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
//    int* lengths = new int[2];
//    lengths[0] = 1;
//    lengths[1] = 1;
//
//    MyVector<MyVector<MyVector<int>>> test;
//
//    int testValue = 5;
//    MyVector<int> testRow;
//    for (int i = 0; i < 5; i++)
//    {
//        testRow.push_back(i);
//    }
//
//    MyVector<MyVector<int>> testMatrix;
//
//    for (int i = 0; i < 5; i++)
//    {
//        MyVector<int> testRow;
//        for (int j = 0; j < 5; j++)
//        {
//            int temp = i * 10 + j;
//            testRow.push_back(temp);
//        }
//
//        testMatrix.push_back(testRow);
//    }
//
//    std::cout << testValue << std::endl;
//
//    for (int i = 0; i < testRow.getArrayLen(); i++)
//    {
//        std::cout << testRow[i] << std::endl;
//    }
//
//    for (int i = 0; i < testMatrix.getArrayLen(); i++)
//    {
//        for (int j = 0; j < testMatrix[i].getArrayLen(); j++)
//        {
//            std::cout << testMatrix[i][j] << ' ';
//        }
//        std::cout << std::endl;
//    }
//
//    int** testDyn = new int*[testMatrix.getArrayLen()];
//
//    for (int i = 0; i < testMatrix.getArrayLen(); i++)
//    {
//        testDyn[i] = new int[testMatrix[i].getArrayLen()];
//        testDyn[i] = testMatrix[i].getDynamic();
//    }
//
//    for (int i = 0; i < testMatrix.getArrayLen(); i++)
//    {
//        for (int j = 0; j < testMatrix[i].getArrayLen(); j++)
//        {
//            std::cout << testDyn[i][j] << ' ';
//        }
//        std::cout << std::endl;
//    }
//}

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

    MyVector<MyVector<MyVector<char>>> specsCodes;
    reduceSpecs(students, specsCodes);

    for (int i = 0; i < specsCodes.getArrayLen(); i++)
    {
        for (int j = 0; j < specsCodes[i].getArrayLen(); j++)
        {
            for (int u = 0; u < specsCodes[i][j].getArrayLen(); u++)
            {
                std::cout << specsCodes[i][j][u];
            }
            std::cout << ' ';
        }
        std::cout << std::endl;
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
