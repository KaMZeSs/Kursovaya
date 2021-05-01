#pragma once
#include "File.h"

File::File()
{
	Size = 0;
	cout << "asdasd" << endl;
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

/*void File::Read()
{
	ifstream Doc(Path);
	string str;
	if(!Doc.is_open())
	{
		cout << "���� �� ������" << endl;
		system("pause");
		exit(-1);
	}
	getline(Doc, str, '\0');
}*/

bool File::Update(string Path)
{
	int length = 0;
	string str = Path;
	str += Name;
	ofstream Doc(str);
	string s;
	if (!Doc.is_open()) exit(1);
	for (int i = 0, max = Content.size(); i < max; i++)
	{
		Doc << Content[i] << endl;
		length += Content[i].length();
	}
	Doc.close();
	Size = length;
	return true;
}

/*ostream & operator << (ostream &output, File &Doc)
{
	string str = Doc.Read();
	cout << str << endl;
	return output;
}*/



void File::Write()
{
	system("cls");
	cout << Name << endl;
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
			cout << Name << endl;
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
}

void File::SetName(string TName)
{
	Name = TName;
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
}

void File::SetOwner(string User)
{
	Owner = User;
}

string File::GetName()
{
	return Name;
}