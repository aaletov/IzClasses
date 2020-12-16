#include <iostream>
#include <fstream>
#include <string>
#include "Exceptions.h"
#include "Check.h"

bool isInteger(std::string str)
{
    if (str.empty())
    {
        return true;
    }
    if (isDigit(str[0]) && isInteger(str.erase(0, 1)))
    {
        return true;
    }
    return false;
}

bool isDigit(const char ch)
{
    if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4'
        || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9')
    {
        return true;
    }
    return false;
}

bool isCorrectNumber(const std::string& number)
{
    int length = number.length();
    std::string temp1;
    std::string temp2;
    int pos = number.find('/');
    temp1 = number.substr(0, pos);
    temp2 = number.substr(pos + 1, length - pos);
    
    if (isInteger(temp1) && isInteger(temp2) && temp2.find('/') == std::string::npos)
    {
        return true;
    }

    return false;
}

bool isCorrectInitial(std::string& initial)
{
    if (initial.length() == 2 && isRusCapitalLetter(initial[0]) && initial[1] == '.')
    {
        return true;
    }
    return false;
}

bool isCapitalizedRusWord(const std::string& lastName)
{
    if (!isRusCapitalLetter(lastName[0]))
    {
        return false;
    }

    std::string temp = lastName;
    temp.erase(0, 1);
    return isRusWord(temp);
}

bool isRusWord(std::string str)
{
    for (int i = 1; i < str.length(); i++)
    {
        if (!isRusLetter(str[i]))
        {
            return false;
        }
    }
    return true;
}

bool isRusLetter(char a)
{
    if (static_cast<int>(a) >= -32 && static_cast<int>(a) <= -1)
    {
        return true;
    }
    return false;
}

bool isRusCapitalLetter(char a)
{
    if (static_cast<int>(a) >= -64 && static_cast<int>(a) <= -33)
    {
        return true;
    }
    return false;
}

bool isLastNameInitials(const std::string& str)
{
    std::string lastNameInitials = str;
    int length = lastNameInitials.length() - 1;
    int pos1 = lastNameInitials.find(' ');
    std::string lastName = lastNameInitials.substr(0, pos1);
    lastNameInitials.erase(0, pos1 + 1);
    int pos2 = lastNameInitials.find(' ');
    std::string initial1 = lastNameInitials.substr(0, pos2);
    lastNameInitials.erase(0, pos2 + 1);
    std::string initial2 = lastNameInitials;
    
    if (isCapitalizedRusWord(lastName) && isCorrectInitial(initial1) && isCorrectInitial(initial2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isCorrectSpecialty(std::string str)
{
    int pos = str.find('_');
    if (pos == -1)
    {
        if (isCapitalizedRusWord(str))
        {
            return true;
        }
    }
    else
    {
        if (isRusWord(str.substr(0, pos)))
        {
            str.erase(0, pos + 1);
            return isRusWord(str);
        }
    }
    return false;
}