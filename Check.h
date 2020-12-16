#pragma once
#include <string>

bool isFloatingPoint(const std::string str);
bool isDigit(const char ch);
bool isSign(const char str);
bool isInteger(std::string str);
bool isOrder(std::string str);
bool isMantissa(std::string str);
std::string openNewString(const std::string& PATH);
void skipStrings(std::ifstream& in, int n);
bool isCapitalizedRusWord(const std::string& lastName);
bool isCorrectInitial(std::string& initial);
bool isCorrectNumber(const std::string& number);
bool isRusLetter(char a);
bool isRusCapitalLetter(char a);
bool isLastNameInitials(const std::string& str);
bool isCorrectSpecialty(std::string str);
bool isRusWord(std::string str);