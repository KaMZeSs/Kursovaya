#pragma once
#include "Document.h"

Document::Document()
{
	FontSize = 10;
	Content.push_back("");
	cout << "asdasd" << endl;
}

Document::~Document()
{
	if (remove(Name.c_str()) != 0) cout << "Ошибка удаления файла" << endl;
	//counter--;
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

int Document::GetColorInt()
{
	string str, c = FontColor;
	int col = 7;
	ifstream Doc("Config/colors.txt");
	if (!Doc.is_open())
	{
		cout << "Файл не открыт" << endl;
		system("pause");
		exit(-1);
	}
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	while (!Doc.eof())
	{
		getline(Doc, str);
		if (str.find(c) != string::npos)
		{
			col = str[0];
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