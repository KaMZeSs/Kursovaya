#pragma once
#include "File.h"
#include "Table.h"

class Document : public File, public Table
{
private:
	int FontSize;
	string FontColor;
	bool isTable;
public:
	Document(long Size, string Date, string Owner, int FontSize, string Color);
	Document();
	Document(string TOwner, int Font, string Color, string TName);
	~Document();
	void SetColor(string);
	string GetColor();
	int GetColorInt(vector<string>);
	int GetFont();
	bool SetFontSize(int);
	virtual int ReadFromFile(string);
	virtual vector<string> Read();
	friend bool operator + (Document&, Document&); // Оставить таблицу первого
	friend bool operator << (Document&, Table&);
	virtual void operator --(int) {};
};