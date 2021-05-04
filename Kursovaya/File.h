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
	virtual int ReadFromFile(string);
	void Write(string buffer);
	void Write();
	bool Update(string);
	void SetName(string TName);
	string GetOwner();
	string GetName();
	string GetDate();
	void SetDate();
	void SetDate(string);
	void SetOwner(string);
	int GetFileSize();
	virtual void operator --(int) = 0;
};