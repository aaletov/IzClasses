#pragma once
#include <fstream>

class TableRow
{
private:
	char** info;
	int nColumns;
	int* columnsLen;
	void printCellString(std::ostream& out, int column);
	void printEmptyCellString(std::ostream& out, int column);
public:
	TableRow();
	TableRow(char** info, int nColumns, int* columnsLen);
	void printRow(std::ostream& out);
};

