#pragma once
#include "libs.h"

class Table
{
private:
	string TName;
protected:
	int NumOfColumns;
	int Size;
	vector<int> MaxInCol;
	vector<string> TableContent;
public:
	Table();
	Table(int);
	~Table();
	string GetTName();
	void SetTName(string);
	void Work();
	void ReadTable(bool key = false);
	vector<string> GetTableContent();
	bool Update(string);
	bool ReadFromFile(string);
	void SetMax();
	vector<int> GetMaxInCol();
	int GetSize();
	void SetSize(int);
	int GetNumOfColumns();
	void SetNumOfColumns(int);
	void operator -- (int);
};