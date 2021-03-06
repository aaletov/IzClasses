#include "Table.h"
#include "TableRow.h"

Table::Table(char**& headers, char***& info, int nColumns, int*& columnsLen, int nRows)
{
	this->nRows = nRows;
	TableRow tempRow(headers, nColumns, columnsLen);
	this->headers = tempRow;
	this->tableRows = new TableRow[nRows];

	for (int i = 0; i < nRows; i++)
	{
		TableRow tempRow(info[i], nColumns, columnsLen);
		this->tableRows[i] = tempRow;
	}

	for (int i = 0; i < nColumns; i++)
	{
		this->tableLen += columnsLen[i];
	}
	tableLen += nColumns + 1;
}

void Table::printTable(std::ostream& out)
{
	printBorder(out);

	headers.printRow(out);
	
	printBorder(out);

	for (int i = 0; i < nRows; i++)
	{
		tableRows[i].printRow(out);
		printBorder(out);
	}
}

void Table::printBorder(std::ostream& out)
{
	for (int i = 0; i < tableLen; i++)
	{
		out << '-';
	}

	out << std::endl;
}

Table::~Table() 
{
	if (tableRows != nullptr)
	{
		delete[] tableRows;
	}
}