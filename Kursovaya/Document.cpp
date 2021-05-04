#pragma once
#include "Document.h"

Document::Document()
{
	FontSize = 10;
	isTable = false;
}

Document::~Document()
{

}

Document::Document(string TOwner, int Font, string Color, string TName)
{
	Owner = TOwner;
	FontColor = Color;
	Name = TName;
	FontSize = Font;
	File::Size = 0;
	time_t rawtime;
	time(&rawtime);
	Date = ctime(&rawtime);
	isTable = false;
}

void Document::SetColor(string col)
{
	FontColor = col;
}

string Document::GetColor()
{
	return FontColor;
}

int Document::GetColorInt(vector<string> list)
{
	string str = FontColor;
	int col = 7;
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].find(str) != string::npos) 
		{
			col = i; 
			break;
		}
	}
	return col;
}

int Document::GetFont()
{
	return FontSize;
}

bool operator + (Document& Doc1, Document& Doc2)
{
	for (int i = 0, max = Doc2.Content.size(); i < max; i++)
		Doc1.Content.push_back(Doc2.Content[i]);
	return 1;
}

vector<string> Document::Read()
{
	vector<string> v;
	for (int i = 0, max = this->Content.size(); i < max; i++)
		v.push_back(this->Content[i]);
	return v;
}

bool Document::SetFontSize(int num)
{
	if (num > 0)
	{
		FontSize = num;
		return true;
	}
	else
		return false;
}

int Document::ReadFromFile(string Path)
{
	int length = 0;
	bool table = false;
	string str = Path;
	str += Name;
	ifstream Doc(str);
	if (!Doc.is_open()) return -1;
	for (int i = 0; !Doc.eof() && !table; i++)
	{
		str.clear();
		getline(Doc, str);
		Content.push_back(str);
		length += Content.back().length();
		table = (str.find(23) != string::npos);
	}
	while (!Doc.eof())
	{
		getline(Doc, str);
		TableContent.push_back(str);
		str.clear();
		Table::Size++;
	}

	File::Size = length;
	return 0;
}