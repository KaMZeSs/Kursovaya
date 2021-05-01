#pragma once
#include "libs.h"

class Table
{
private:
	string TName;
protected:
	void AddLine();
	int NumOfLines;
	int NumOfColumns;
	vector<string> cont;
public:
	Table() {};
	Table(int, int) {};
	~Table() {};
	string GetTName();
	void CreateTable();
	void ReadTable();
	void ChangeTable();
	void operator += (vector<string>); //AddLine
};