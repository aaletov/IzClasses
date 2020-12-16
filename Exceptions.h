#pragma once
#include <string>

class FileException
{
private:
    const std::string s_error = "������ �������� �����";
public:
    FileException();
    const char* getError();
};

class StrException
{
private:
    const std::string s_error = "������� ��� ������ ��� ��������� ������������ ������";
public:
    StrException();
    const char* getError();
};

class StudentException
{
private:
    const std::string s_error = "������������ ������� ������";
public:
    StudentException();
    const char* getError();
};
