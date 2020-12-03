#include <iostream>
#include <fstream>
#include <iomanip>  
#include "Student.h"
#include "MyVector.h"
#include "Bogosort.h"

void openAllStudents(const std::string& PATH, MyVector<Student>& myVector);
Student openNewStudent(const std::string& PATH);
void getStringBeforeSpace(std::ifstream& in, std::string& str);
int getIntBeforeSpace(std::ifstream& in);
void printSpecTable(MyVector<Student>& students);
void printTable(MyVector<Student>& students);
void printBorder(std::ostream& in, const int len);
void printEmptyString(std::ostream& in, const int* columns, const int nColumns, const int tableLen);
void printFilledString(std::ostream& in, const int* columns, MyVector<char*>& columnsInfo, const int nColumns, const int tableLen);
void reduceSpecs(MyVector<Student>& students, MyVector<char*>& specs);
void strToCString(std::string& in, char* out);

class FileException
{
private:
    const std::string s_error = "Ошибка открытия файла";
public:
    FileException()
    {
    }
    const char* getError()
    {
        return s_error.c_str();
    }
};

class StrException
{
private:
    const std::string s_error = "Считаны все строки";
public:
    StrException()
    {
    }
    const char* getError()
    {
        return s_error.c_str();
    }
};

int main()
{
    setlocale(LC_ALL, "RUS");
    const std::string PATH = "students.txt";
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
    printTable(students);

    return 0;
}

void openAllStudents(const std::string& PATH, MyVector<Student>& myVector)
{
    try
    {
        int i = 0;
        while (true)
        {
            myVector.push_back(openNewStudent(PATH));
            i++;
        }
    }
    catch (StrException& err)
    {
        std::cout << err.getError() << std::endl << std::endl;
    }
    catch (FileException& err)
    {
        std::cout << err.getError() << std::endl << std::endl;
    }
}

Student openNewStudent(const std::string& PATH)
{
    static int alreadyRead = 0;
    static std::ifstream in;
    std::string str = "";
    std::string lastName;
    std::string initials1;
    std::string initials2;
    std::string specialty;
    std::string groupNumber;
    int semester;
    int* performance = new int[5];

    if (alreadyRead == 0)
    {
        in.open(PATH, std::ios::in);
        if (in.fail())
        {
            throw FileException();
        }
    }

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

void printTable(MyVector<Student>& students)
{
    const int codeColumnLen = 31;
    const int specColumnLen = 61;
    const int columns[] = { codeColumnLen, specColumnLen };
    const int nColumns = sizeof(columns) / sizeof(columns[0]);
    const int tableLen = codeColumnLen + specColumnLen + nColumns + 1;

    MyVector<char*> specs;
    reduceSpecs(students, specs);

    printBorder(std::cout, tableLen);
    printEmptyString(std::cout, columns, nColumns, tableLen);

    std::string testSpec = "Специальность";
    std::string testCode = "Код";
    MyVector<char*> columnInfo;
    char* cTestSpec = new char[testSpec.length() + 1];
    char* cTestCode = new char[testCode.length() + 1];
    strToCString(testSpec, cTestSpec);
    strToCString(testCode, cTestCode);
    columnInfo.push_back(cTestCode);
    columnInfo.push_back(cTestSpec);

    printFilledString(std::cout, columns, columnInfo, nColumns, tableLen);
}

void printBorder(std::ostream& in, const int len)
{
    for (int i = 0; i < len; i++)
    {
        std::cout << '-';
    }
    std::cout << std::endl;
}

void printEmptyString(std::ostream& in, const int* columns, const int nColumns, const int tableLen)
{
    std::cout << '-';
    for (int i = 0; i < nColumns; i++)
    {
        std::cout << std::setw(columns[i] + 1);
        std::cout << '-';
    }
    std::cout << std::endl;
}

void printFilledString(std::ostream& in, const int* columns, MyVector<char*>& columnsInfo, const int nColumns, const int tableLen)
{
    std::cout << '-';
    int emptySpace = 0;
    int emptySpace1 = 0;
    int emptySpace2 = 0;
    int infoLen = 0;
    for (int i = 0; i < nColumns; i++)
    {
        infoLen = strlen(columnsInfo[i]);
        emptySpace = columns[i] - infoLen;
        emptySpace1 = emptySpace - emptySpace / 2;
        if (emptySpace % 2 == 0)
        {
            emptySpace2 = emptySpace1;
        }
        else
        {
            emptySpace2 = emptySpace - emptySpace1;
        }
        std::cout << std::setw(infoLen + emptySpace1);
        std::cout << columnsInfo[i];
        std::cout << std::setw(emptySpace2 + 1);
        std::cout << '-';
    }
    std::cout << std::endl;
}

void reduceSpecs(MyVector<Student>& students, MyVector<char*>& specs)
{
    for (int i = 0; i < students.getArrayLen(); i++)
    {
        std::string spec = students[i].getSpecialty();
        char* cstr = new char[spec.length() + 1];
        strToCString(spec, cstr);
        if (specs.contains(cstr))
        {
            continue;
        }
        else
        {
            specs.push_back(cstr);
        }
    }
}

void strToCString(std::string& in, char* out)
{
    int i;
    for (i = 0; i < in.length(); i++)
    {
        out[i] = in[i];
    }
    out[i] = 0;
}
