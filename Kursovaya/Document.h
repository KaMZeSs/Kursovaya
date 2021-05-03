#pragma once
#include "File.h"
#include "Table.h"

class Document : public File, public Table
{
private:
	int FontSize;
	int TablePos;
	string FontColor;
public:
	Document(long Size, string Date, string Owner, int FontSize, string Color);
	Document();
	Document(string TOwner, int Font, string Color, string TName);
	~Document();
	void SetColor(string);
	string GetColor();
	int GetColorInt(vector<string>);
	int GetFont();
	void SetTablePos(int);
	int GetTablePos();
	bool SetFontSize(int);
	virtual vector<string> Read();
	virtual void operator ++ () {};
	friend bool operator + (Document&, Document&);
};