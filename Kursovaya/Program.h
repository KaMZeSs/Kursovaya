#pragma once
#include "libs.h"
#include "Document.h"
#include "Image.h"

class Program
{
private:
	//static int counter;
	string local;
	string User;
	string Color;
	vector<string> Front_page;
	vector<string> Config;
	vector<string> ListLocalisation;
	vector<string> Errors;
	vector<string> Menu; 
	vector<string> Other;
	vector<string> Colors;
	vector<string> Save;
	vector<Document> Documents;
	vector<Image> Images;
	vector<Table> Tables;
public:
	Program();
	~Program();
	string GetConfig(int);
	void ViewMenu(int, int);
	string GetMenu(int);
	string GetLocal();
	void SetUser();
	void ShowTitle();
	void Error();
	void AddFiles();
	void ListDocs();
	void ListImages();
	void ListTables();
	void ReadDocImg();
	void RemoveFile();
	void OpenFile();
	bool CreateSaveFile();
	bool OpenSaveFile();
	void Options();
	string GetUser();
	vector<string> GetListColors();
	void operator ++ (int);
	friend ostream& operator << (ostream &, Program &);
	friend void operator << (Program&, char); // смена цвета
};