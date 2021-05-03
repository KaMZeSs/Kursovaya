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
	vector<string> Front_page;
	vector<string> Config;
	vector<string> ListLocalisation;
	vector<string> Errors;
	vector<string> Menu; 
	vector<string> Other;
	vector<string> Colors;
	vector<Document> Documents;
	vector<Image> Images;
	vector<Table> Tables;
public:
	Program();
	~Program();
	void ChangeColor(int);
	string GetConfig(int);
	void ViewMenu(int, int);
	string GetMenu(int);
	string GetLocal();
	void ShowTitle();
	void Error();
	void AddFiles();
	void CreateDocImg(File*);
	void ListDocs();
	void ListImages();
	void ListTables();
	void SetUser();
	string GetUser();
	vector<string> GetListColors();
	void operator ++ (int);
};

Program& operator << (Program&, char); //смена цвета