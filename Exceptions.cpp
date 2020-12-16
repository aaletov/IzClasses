#include "Exceptions.h"

FileException::FileException()
{
}

const char* FileException::getError()
{
    return s_error.c_str();
}

StrException::StrException()
{
}

const char* StrException::getError()
{
    return s_error.c_str();
}

StudentException::StudentException()
{
}

const char* StudentException::getError()
{
    return s_error.c_str();
}