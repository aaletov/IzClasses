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

MemException::MemException()
{
}

const char* MemException::getError()
{
    return s_error.c_str();
}
