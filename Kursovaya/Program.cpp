#pragma once
#include "Program.h"

void Program::Error()
{
	cerr << Config[13];
	system("pause");
	exit(-1);
}

Program::Program()
{
	ifstream Doc("Config/MainData.txt");
	string str;

	if (!Doc.is_open())
	{
		cerr << "Error" << endl;
		system("pause");
		exit(-1);
	}

	for (int i = 0; !Doc.eof() && i < 16; i++)
	{
		getline(Doc, str);
		if (str.length() == 0)
		{
			cout << "Error";
			system("pause");
			exit(-1);
		}
		Config.push_back(str);
	}

	local = Config[9];
	local.erase(0, 21);
	local.erase(7, 4);
	(*this)++;

	Doc.close();
	Doc.open(Config[15].c_str());					//Ошибки
	if (!Doc.is_open()) Error();
	for (int i = 0; !Doc.eof() && i < 16; i++)
	{
		getline(Doc, str);
		if (str.length() == 0) Error();
		Colors.push_back(str);
	}

	system("cls");
	SetUser();
}

Program::~Program()
{

}

string Program::GetConfig(int num)
{
	return Config[num];
}

void Program::ViewMenu(int begin, int end)
{
	for (int i = begin; i <= end; i++)
		cout << Menu[i] << endl;
}

string Program::GetLocal()
{
	return local;
}

void Program::ShowTitle()
{
	system("cls");
	int max = Front_page.size();
	for (int i = 0; i < max; i++)
		cout << Front_page[i] << endl;
}

string Program::GetMenu(int line)
{
	return Menu[line];
}

void Program::operator ++ (int)
{
	int changer = 9;
	string str;
	ifstream Doc;

	if (strstr(Config[changer].c_str(), local.c_str()))
		changer = 10;


	ListLocalisation.clear();
	Errors.clear();
	Front_page.clear();
	Menu.clear();

	local = Config[changer];
	local.erase(0, 21);
	local.erase(7, 4);

	Doc.open(Config[changer]);
	if (!Doc.is_open()) Error();
	for (int i = 0; !Doc.eof() && i < 13; i++)
	{
		getline(Doc, str);
		if (str.length() == 0) Error();
		ListLocalisation.push_back(str);
	}

	Doc.close();
	Doc.open(ListLocalisation[0].c_str());					//Ошибки
	if (!Doc.is_open()) Error();
	for (int i = 0; !Doc.eof() && i < 7; i++)
	{
		getline(Doc, str);
		if (str.length() == 0) Error();
		Errors.push_back(str);
	}

	Doc.close();
	Doc.open(ListLocalisation[1].c_str());					//Титульная страница
	if (!Doc.is_open()) Error();
	for (int i = 0; !Doc.eof() && i < 12; i++)
	{
		getline(Doc, str);
		Front_page.push_back(str);
	}

	Doc.close();
	Doc.open(ListLocalisation[2].c_str());					//Меню
	if (!Doc.is_open()) Error();
	for (int i = 0; !Doc.eof() && i < 22; i++)
	{
		getline(Doc, str);
		if (str.length() == 0) Error();
		Menu.push_back(str);
	}
	Doc.close();

	Doc.open(ListLocalisation[3].c_str());					//Другое
	if (!Doc.is_open()) Error();
	for (int i = 0; !Doc.eof() && i < 18; i++)
	{
		getline(Doc, str);
		if (str.length() == 0) Error();
		Other.push_back(str);
	}

	Doc.close();
}

Program& operator << (Program& Pr, char a)
{
	string str = Pr.GetConfig(14);
	str += 32;
	str += a;
	system(str.c_str());
	return Pr;
}

void Program::AddFiles()
{
	char key = 0;
	string path;
	while (!(key >= '1' && key <= '3'))
	{
		Document Doc;
		Image Img;
		File* F;
		system("cls");
		ViewMenu(8, 10);
		cout << GetMenu(13) << endl << GetMenu(16) << endl;
		key = _getch();
		if (key == 9) (*this)++;
		if (key == 27) return;
		if (key == '1' || key == '2')
		{
			if (key == '1')	F = &Doc;
			else F = &Img;
			string str;
			cout << Menu[18];
			cin >> str;
			F->SetName(str);

			if (key == '1')
			{
				cout << Other[0] << endl;
				string str;
				cin >> str;
				Doc.SetColor(str);
				int num;
				cout << Other[2] << endl;
				cin >> num;
				while (!cin.good() || num <= 0)
				{
					cout << Errors[5] << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					cin >> num;
				}
				Doc.SetFontSize(num);
			}

			CreateDocImg(F);
			if (F->Update(Config[key - 48]))
			{
				if (key == '1') Documents.push_back(Doc);
				else Images.push_back(Img);
			}
			else
			{
				cout << Errors[6] << endl; // Не удалось создать документ
			}
		}
		if (key == '3')
		{
			string str;
			cout << Menu[18];
			cin >> str;
			int num;
			cout << Other[1];
			cin >> num;
			while (!cin.good() || num <= 0)
			{
				cout << Errors[5] << endl;
				cin.clear();
				cin.ignore(1000,'\n');
				cin >> num;
			}
			Table Tab(num);
			Tab.SetTName(str);
			Tab.Work();
			if (Tab.Update(Config[key - 48]))
			{
				Tables.push_back(Tab);
			}
			else
			{
				cout << Errors[6] << endl;
			}
		}
	}
}

void Program::SetUser()
{
	cout << this->GetMenu(19);
	cin >> User;
}
string Program::GetUser()
{
	return User;
}

vector<string> Program::GetListColors()
{
	return Colors;
}

void Program::CreateDocImg(File* Doc)
{
	Doc->SetDate();
	Doc->SetOwner(User);
	Doc->Write();
}

void Program::ListDocs()
{
	cout << Other[3] << endl;
	for (int i = 0, max = Documents.size(); i < max; i++)
	{
		cout << endl << Other[4] << i << endl;
		cout << Other[9] << Documents[i].GetName() << endl;
		cout << Other[10] << Documents[i].GetOwner() << endl;
		cout << Other[11] << Documents[i].GetDate() << endl;
		cout << Other[12] << Documents[i].GetFileSize() << endl;
		cout << Other[13] << Documents[i].GetFont() << endl;
		cout << Other[14] << Documents[i].GetColor() << endl;

	}
}

void Program::ListImages()
{
	cout << Other[5] << endl;
	for (int i = 0, max = Images.size(); i < max; i++)
	{
		cout << endl << Other[6] << i << endl;
		cout << Other[9] << Images[i].GetName() << endl;
		cout << Other[10] << Images[i].GetOwner() << endl;
		cout << Other[11] << Images[i].GetDate() << endl;
		cout << Other[12] << Images[i].GetFileSize() << endl;
		cout << Other[15] << Images[i].GetHeight() << endl;
		cout << Other[16] << Images[i].GetWidth() << endl;
	}
}

void Program::ListTables()
{
	cout << Other[7] << endl;
	for (int i = 0, max = Tables.size(); i < max; i++)
	{
		cout << endl << Other[8] << i << endl;
		cout << Other[9] << Tables[i].GetTName() << endl;
		cout << Other[12] << Tables[i].GetSize() << endl;
		cout << Other[17] << Tables[i].GetNumOfColumns() << endl;
	}
}