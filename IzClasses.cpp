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
void printTable(char** headers, char*** values, int nColumns, int nStrings);
void printBorder(std::ostream& in, const int len);
void printEmptyString(std::ostream& in, const int* columns, const int nColumns, const int tableLen);
void printFilledString(std::ostream& in, const int* columns, MyVector<char*>& columnsInfo, const int tableLen);
void printTableHeader(std::ostream& in, const int* columns, MyVector<char*>& columnsInfo, const int tableLen);
char*** reduceSpecs(MyVector<Student>& students);
void strToCString(std::string& in, char* out);
char* codeFromNumber(char* groupNumber);
char* intToCStr(int x);
int cStrToInt(char* cstr);
int intLen(int number);
char digToCStr(int x);

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
    char*** specsCodes = reduceSpecs(students);

    int nOfStrings = cStrToInt(specsCodes[0][0]);
    specsCodes++;
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

    //printTable(headers, values);

    return 0;
}

void printTable(char** headers, char*** values, int nColumns, int nStrings, int* lenColumns)
{
    const int codeColumnLen = 31;
    const int specColumnLen = 61;
    const int columns[] = { codeColumnLen, specColumnLen };
   /* const int nColumns = sizeof(columns) / sizeof(columns[0]);*/
    const int tableLen = codeColumnLen + specColumnLen + nColumns + 1;



    /*printTableHeader(in, columns, )*/


}

//void printTableHeader(std::ostream& in, const int* columns, const int tableLen)
//{
//    printBorder(std::cout, tableLen);
//    printEmptyString(std::cout, columns, columnsInfo.getArrayLen(), tableLen);
//
//    std::string testSpec = "Специальность";
//    std::string testCode = "Код";
//    MyVector<char*> columnInfo;
//    char* cTestSpec = new char[testSpec.length() + 1];
//    char* cTestCode = new char[testCode.length() + 1];
//    strToCString(testSpec, cTestSpec);
//    strToCString(testCode, cTestCode);
//    columnInfo.push_back(cTestCode);
//    columnInfo.push_back(cTestSpec);
//
//    printFilledString(std::cout, columns, columnInfo, tableLen);
//}

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

void printFilledString(std::ostream& in, const int* columns, MyVector<char*>& columnsInfo, const int tableLen)
{
    std::cout << '-';
    int emptySpace = 0;
    int emptySpace1 = 0;
    int emptySpace2 = 0;
    int infoLen = 0;
    int nColumns = columnsInfo.getArrayLen();
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

char*** reduceSpecs(MyVector<Student>& students)
{
    MyVector<char**> specs;
    char** stringNOfStrings = new char* [2];
    char* nOfStrings = new char[1000];
    specs.push_back(stringNOfStrings);

    char* codeTemp;
    char* cspec;
    char** tempString = new char* [2];
    bool isCodeIn;

    for (int i = 0; i < students.getArrayLen(); i++)
    {
        std::string spec = students[i].getSpecialty();
        cspec = new char[spec.length() + 1];
        strToCString(spec, cspec);
        strToCString(students[i].getGroupNumber(), tempString[0]);
        codeTemp = codeFromNumber(tempString[0]);
        tempString[1] = cspec;

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
        return specs.toDynamic();
    }
}

void strToCString(std::string& in, char* out)
{
    int i;
    out = new char[in.length() + 1];
    for (i = 0; i < in.length(); i++)
    {
        out[i] = in[i];
    }
    out[i] = 0;
}

char* codeFromNumber(char* groupNumber)
{
    int pos = sizeof(strstr(groupNumber, "/") - groupNumber);
    char* newString = new char[pos + 1];
    newString[pos] = 0;

    for (int i = 0; i < pos; i++)
    {
        newString[i] = groupNumber[i];
    }
    newString[pos] = 0;
    return newString;
}

char* intToCStr(int x)
{
    int len = intLen(x);
    char* cInt = new char[len + 1];
    cInt[len] = 0;
    int dig;

    for (int i = 0; i < len; i++)
    {
        dig = x % 10;
        cInt[len - 1 - i] = static_cast<char>(digToCStr(dig));
        x /= 10;
    }
    return cInt;
}

char digToCStr(int x)
{
    switch (x)
    {
    case 0:
        return 48;
    case 1:
        return 49;
    case 2:
        return 50;
    case 3:
        return 51;
    case 4:
        return 52;
    case 5:
        return 53;
    case 6:
        return 54;
    case 7:
        return 55;
    case 8:
        return 56;
    case 9:
        return 57;
    default:
        break;
    }
}

int cStrToInt(char* cstr)
{
    int sum = 0;
    int len = strlen(cstr);

    for (int i = 0; i < len; i++)
    {
        sum += (static_cast<int>(cstr[i]) - 48) * pow(10, len - 1 - i);
    }
    return sum;
}

int intLen(int number)
{
    int size = 1;
    while (number / 10 != 0)
    {
        number /= 10;
        size++;
    }
    return size;
}