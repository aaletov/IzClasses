#pragma once
#include <string>

class FileException
{
private:
    const std::string s_error = "Ошибка открытия файла";
public:
    FileException();
    const char* getError();
};

class StrException
{
private:
    const std::string s_error = "Считаны все строки или встречена некорректная строка";
public:
    StrException();
    const char* getError();
};

class StudentException
{
private:
    const std::string s_error = "Некорректные входные данные";
public:
    StudentException();
    const char* getError();
};
