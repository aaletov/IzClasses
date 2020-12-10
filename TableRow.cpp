#include "TableRow.h"
#include <iostream>
#include <iomanip>

TableRow::TableRow()
{
}

TableRow::TableRow(char** info, int nColumns, int* columnsLen)
{
	this->info = new char* [nColumns];
	for (int i = 0; i < nColumns; i++)
	{
		this->info[i] = new char[strlen(info[i])];
		strcpy(this->info[i], info[i]);
	}

	this->nColumns = nColumns;
	
	this->columnsLen = new int[nColumns];
	for (int i = 0; i < nColumns; i++)
	{
		this->columnsLen[i] = columnsLen[i];
	}
}

void TableRow::printRow(std::ostream& out)
{
	for (int i = 0; i < nColumns; i++)
	{
		out << '-';
		printEmptyCellString(out, i);
	}

	out << std::endl;

	for (int i = 0; i < nColumns; i++)
	{
		out << '-';
		printCellString(out, i);
	}

	out << std::endl;

	for (int i = 0; i < nColumns; i++)
	{
		out << '-';
		printEmptyCellString(out, i);
	}

	out << std::endl;
}

void TableRow::printCellString(std::ostream& out, int column)
{
	int emptySpace = 0;
	int emptySpace1 = 0;
	int emptySpace2 = 0;
	int infoLen = 0;

	infoLen = strlen(info[column]);
	emptySpace = columnsLen[column] - infoLen;
	emptySpace1 = emptySpace - emptySpace / 2;
	if (emptySpace % 2 == 0)
	{
		emptySpace2 = emptySpace1;
	}
	else
	{
		emptySpace2 = emptySpace - emptySpace1;
	}

	out << std::setw(infoLen + emptySpace1);
	out << info[column];
	out << std::setw(emptySpace2 + 1);
	out << '-';
}

void TableRow::printEmptyCellString(std::ostream& out, int column)
{
	out << std::setw(columnsLen[column] + 1);
	out << '-';
}