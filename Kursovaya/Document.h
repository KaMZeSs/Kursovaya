#pragma once
#include "File.h"
#include "Table.h"

class Document : public File, public Table
{
private:
	int FontSize;
	string FontColor;
public:
	Document(long Size, string Date, string Owner, int FontSize, string Color);
	Document();
	Document(string TOwner, int Font, string Color, string TName);
	~Document();
	void SetColor(string);
	string GetColor();
	int GetFont();
	bool SetFontSize(int);
	int ReadFromFile(string);
	bool Update(string);
	virtual vector<string> Read();
	friend bool operator + (Document&, Document&); // Оставить таблицу первого
	friend bool operator << (Document&, Table&);
	virtual void operator ++(int);
};