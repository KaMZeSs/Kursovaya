#pragma once
#include "Document.h"

Document::Document(long Size, string Date, string Owner, int FontSize, string Color)
{
	this->File::Size = Size;
	this->Date = Date;
	this->Owner = Owner;
	this->FontSize = FontSize;
	this->FontColor = Color;
}

Document::Document()
{
	FontSize = 10;
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
}

void Document::SetColor(string col)
{
	FontColor = col;
}

string Document::GetColor()
{
	return FontColor;
}

int Document::GetFont()
{
	return FontSize;
}

bool operator + (Document& Doc1, Document& Doc2)
{
	for (int i = 0, max = Doc2.Content.size(); i < max; i++)
		Doc1.Content.push_back(Doc2.Content[i]);
	return true;
}

bool operator << (Document & Doc, Table & Tab)
{
	Doc.Content = Tab.GetTableContent();
	Doc.NumOfColumns = Tab.GetNumOfColumns();
	Doc.Table::Size = Tab.GetSize();
	Doc.MaxInCol = Tab.GetMaxInCol();
	return true;
}

vector<string> Document::Read()
{
	vector<string> v;
	for (int i = 0, max = this->Content.size(); i < max; i++)
		v.push_back(this->Content[i]);
	return v;
}

void Document::operator--(int)
{
	Content.pop_back();
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
	str.clear();
	if (!Doc.is_open()) return -1;

	while (!Doc.eof())
	{
		str.clear();
		getline(Doc, str);
		Content.push_back(str);
		length += Content.back().length();
		if (str == "<=>") break;
	}
	while (!Doc.eof())
	{
		str.clear();
		getline(Doc, str);
		TableContent.push_back(str);
	}
	return 0;
}

bool Document::Update(string Path)
{
	int length = 0;
	string str = Path;
	str += Name;
	remove(str.c_str());
	ofstream Doc(str);
	if (!Doc.is_open()) return false;
	for (int i = 0, max = Content.size(); i < max; i++)
	{
		Doc << Content[i] << endl;
		length += Content[i].length();
	}
	File::Size = length;
	length = 0;
	char t = 60;
	Doc << t; t++; Doc << t; t++; Doc << t << endl;
	for (int i = 0, max = TableContent.size(); i < max; i++)
	{
		Doc << TableContent[i] << endl;
	}
	Table::Size = TableContent.size();
	Doc.close();
	return true;
}