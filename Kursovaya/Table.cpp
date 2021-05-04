#pragma once
#include "Table.h"

Table::Table()
{
	NumOfColumns = 0;
}

Table::Table(int Column)
{
	MaxInCol.resize(NumOfColumns = Column, 0);
}

Table::~Table()
{
	TableContent.clear();
}

string Table::GetTName()
{
	return TName;
}

void Table::SetTName(string Name)
{
	TName = Name;
}

void Table::Work()
{
	system("cls");

	this->ReadTable(true);

	TableContent.push_back("");

	char key = 0;
	while (key != 27)
	{
		key = _getch();

		if (key == 8)
		{
			if (TableContent.back().length() == 0)
			{
				if (TableContent.size() == 1) continue;
				TableContent.pop_back();
			}
			else
			{
				TableContent.back().pop_back();
			}
			system("cls");
			SetMax();
			ReadTable(true);
			continue;
		}

		if (key == 13)
		{
			system("cls");
			SetMax();
			ReadTable();
			TableContent.push_back("");
			continue;
		}

		if (key == 27)
		{
			if (TableContent.back().size() == 0)
			{
				TableContent.pop_back();
			}
			int a = TableContent.size() % NumOfColumns;
			if (a != 0)
			{
				while (a != 0)
				{
					TableContent.pop_back();
					a--;
				}
			}
			break;
		}

		if (TableContent.back().size() == 40) continue;
		TableContent.back() += key;
		cout << key;
	}

	Size = TableContent.size();

	SetMax();
}

void Table::ReadTable(bool key)
{
	if (TableContent.size() == 0 || (TableContent.size() == 1 && TableContent[0].length() == 0))
	{
		cout << TName << endl;
		return;
	}

	SetMax();

	char line_1 = 45, line_2 = 124;
	int line_1_len = 1;

	for (int i = 0; i < MaxInCol.size(); i++)
		line_1_len += MaxInCol[i] + 1;

	string line;
	line.resize(line_1_len, line_1);

	cout << TName << endl << line << endl;
	for (int i = 0, j = 0; i < TableContent.size(); i++, j++)
	{
		string str = TableContent[i];
		if (key) // ≈сли мен¤ю таблицу
		{
			if (i != TableContent.size() - 1)  //≈сли не послелн¤¤ ¤чейка
			{
				str.resize(MaxInCol[j], 32);
			}
			else // ≈сли последн¤¤ ¤чейка
			{
				cout << line_2 << str;
				return;
			}
		}
		else  // ≈сли не мен¤ю таблицу
		{
			str.resize(MaxInCol[j], 32);
		}
		cout << line_2 << str;
		if (j == NumOfColumns - 1) // ≈сли последний столбец
		{
			j = -1;
			cout << line_2 << endl << line << endl;
		}
	}
	if (TableContent.size() % NumOfColumns != 0) cout << line_2;
}

void Table::SetMax()
{
	MaxInCol.clear();
	MaxInCol.resize(this->NumOfColumns, 0);
	for (int i = 0, j = 0; i < TableContent.size(); i++, j++)
	{
		int len = TableContent[i].size();
		if (len > MaxInCol[j]) MaxInCol[j] = len;
		if (j == NumOfColumns - 1) j = -1;
	}
}

int Table::GetSize()
{
	return Size;
}

void Table::SetSize(int a)
{
	Size = a;
}

int Table::GetNumOfColumns()
{
	return NumOfColumns;
}

void Table::SetNumOfColumns(int a)
{
	NumOfColumns = a;
}

void Table::operator--(int)
{
	TableContent.resize(TableContent.size() - NumOfColumns);
}

bool Table::Update(string Path)
{
	string str = Path;
	str += TName;
	ofstream Doc(str);
	if (!Doc.is_open()) return false;
	for (int i = 0; i < TableContent.size(); i++)
	{
		Doc << TableContent[i] << endl;
	}
	Doc.close();
	return true;
}

bool Table::ReadFromFile(string Path)
{
	string FPath = Path;
	FPath += TName;
	ifstream Doc(FPath);
	if (!Doc.is_open()) return false;
	string str;
	Size = 0;
	while (!Doc.eof())
	{
		getline(Doc, str);
		TableContent.push_back(str);
		str.clear();
		Size++;
	}
	if (TableContent.back().size() == 0) TableContent.pop_back();
	return true;
}