#pragma once
#include "libs.h"

class File
{
protected:
	long Size;
	string Date;
	string Owner;
	vector<string> Content;
	string Name;
public:
	File();
	File(long Size, string Date, string Owner);
	virtual vector<string> Read() = 0;
	ostream& operator >> (ostream& out)
	{
		system("cls");
		for (int i = 0, max = Content.size(); i < max; i++)
			cout << Content[i] << endl;
		return out;
	}
	void Write(string buffer);
	void Write();
	bool Update(string);
	void SetName(string TName);
	string GetOwner();
	string GetName();
	string GetDate();
	void SetDate();
	void SetOwner(string);
	int GetFileSize();
};