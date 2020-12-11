#include "TableRow.h"
#include <iostream>
#include <iomanip>

TableRow::TableRow()
{
	info = new char*[1];
	nColumns = 1;
	columnsLen = new int[1];
}

TableRow::TableRow(char** info, int nColumns, int* columnsLen)
{
	this->info = new char* [nColumns];
	for (int i = 0; i < nColumns; i++)
	{
		this->info[i] = new char[strlen(info[i]) + 1];
		strcpy(this->info[i], info[i]);
	}

	this->nColumns = nColumns;
	
	this->columnsLen = new int[nColumns];
	for (int i = 0; i < nColumns; i++)
	{
		this->columnsLen[i] = columnsLen[i];
	}
}

TableRow::TableRow(const TableRow& rvalue)
{
	this->nColumns = rvalue.nColumns;

	this->columnsLen = new int[nColumns];
	for (int i = 0; i < rvalue.nColumns; i++)
	{
		this->columnsLen[i] = rvalue.columnsLen[i];
	}

	info = new char* [rvalue.nColumns];

	for (int i = 0; i < rvalue.nColumns; i++)
	{
		info[i] = new char[strlen(rvalue.info[i]) + 1];
		for (int j = 0; j < strlen(rvalue.info[i]) + 1; j++)
		{
			info[i][j] = rvalue.info[i][j];
		}
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

TableRow::~TableRow()
{
	delete[] columnsLen;
	for (int i = 0; i < nColumns; i++)
	{
		delete[] info[i];
	}
	delete[] info;
}

TableRow& TableRow::operator=(TableRow& rvalue)
{
	info = new char* [rvalue.nColumns];
	nColumns = rvalue.nColumns;
	columnsLen = new int[rvalue.nColumns];

	for (int i = 0; i < nColumns; i++)
	{
		columnsLen[i] = rvalue.columnsLen[i];
	}

	for (int i = 0; i < rvalue.nColumns; i++)
	{
		info[i] = new char[strlen(rvalue.info[i]) + 1];
		for (int j = 0; j < strlen(rvalue.info[i]) + 1; j++)
		{
			info[i][j] = rvalue.info[i][j];
		}
	}
	return *this;
}