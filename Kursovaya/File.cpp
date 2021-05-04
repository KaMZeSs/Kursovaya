#pragma once
#include "File.h"

File::File()
{
	Size = 0;
	Content.push_back("");
}

File::File(long Size, string Date, string Owner)
{
	this->Size = Size;
	this->Date = Date;
	this->Owner = Owner;
}

void File::Write(string buffer)
{
	Content.push_back(buffer);
}

bool File::Update(string Path)
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
	Doc.close();
	Size = length;
	return true;
}

void File::Write()
{
	system("cls");
	cout << Name << endl << endl;
	for (int i = 0, max = Content.size() - 1; i < max; i++)
		cout << Content[i] << endl;
	cout << Content.back();
	char key = 0;
	while (key != 27)
	{
		key = _getch();
		if (key == 8)
		{
			if (Content.front().length() == 0) continue;
			if (Content.back().length() == 0) Content.pop_back();
			else Content.back().erase(Content.back().size() - 1);
			system("cls");
			cout << Name << endl << endl;
			for (int i = 0, max = Content.size() - 1; i < max; i++)
				cout << Content[i] << endl;
			cout << Content.back();
			continue;
		}
		if (key == 13)
		{
			Content.push_back("");
			cout << endl;
			continue;
		}
		if (key != 27)
		{
			Content.back() += key;
			cout << key;
		}
	}
	Size = 0;
	for (int i = 0, max = Content.size(); i < max; i++) Size += Content[i].length();
}

void File::SetName(string TName)
{
	Name = TName;
}

string File::GetOwner()
{
	return Owner;
}

string File::GetDate()
{
	return Date;
}

void File::SetDate()
{
	time_t rawtime;
	time(&rawtime);
	Date = ctime(&rawtime);
	Date.erase(Date.length() - 1);
}

void File::SetDate(string D)
{
	Date = D;
}

void File::SetOwner(string User)
{
	Owner = User;
}

int File::GetFileSize()
{
	return Size;
}

void File::ProcessSize()
{
	Size = 0;
	for (int i = 0, max = Content.size(); i < max; i++) Size += Content[i].length();
}

string File::GetName()
{
	return Name;
}

int File::ReadFromFile(string Path)
{
	int length = 0;
	string str = Path;
	str += Name;
	ifstream Doc(str);
	if (!Doc.is_open()) return -1;
	for (int i = 0; !Doc.eof(); i++)
	{
		str.clear();
		getline(Doc, str);
		Content.push_back(str);
		length += Content[i].length();
	}
	Size = length;
	return 0;
}