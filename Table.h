#pragma once
#include "TableRow.h"

class Table
{
private:
	TableRow* tableRows;
	TableRow headers;
	int tableLen;
	int nRows;
	void printBorder(std::ostream& out);
public:
	Table(char**& headers, char***& info, int nColumns, int*& columnsLen, int nRows);
	void printTable(std::ostream& out);
	~Table();
};

