#pragma once
#include <string>

char* intToCStr(int x);
int cStrToInt(char* cstr);
int intLen(int number);
char digToCStr(int x);
void strToCString(std::string& in, char*& out);
void strToCString(const std::string& in, char* out);

void strToCString(std::string& in, char*& out)
{
    int i;
    for (i = 0; i < in.length(); i++)
    {
        out[i] = in[i];
    }
    out[i] = 0;
}

void strToCString(const std::string& in, char* out)
{
    int i;
    for (i = 0; i < in.length(); i++)
    {
        out[i] = in[i];
    }
    out[i] = 0;
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
        throw - 1;
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