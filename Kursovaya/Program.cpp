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

	for (int i = 0; !Doc.eof() && i < 18; i++)
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
	Doc.open(Config[15].c_str());					//������
	if (!Doc.is_open()) Error();
	for (int i = 0; !Doc.eof() && i < 16; i++)
	{
		getline(Doc, str);
		if (str.length() == 0) Error();
		Colors.push_back(str);
	}

	if (!OpenSaveFile()) SetUser();
	else (*this) << Color.c_str()[0];
	(*this)++; (*this)++;
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
	Other.clear();

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
	Doc.open(ListLocalisation[0].c_str());					//������
	if (!Doc.is_open()) Error();
	for (int i = 0; !Doc.eof(); i++)
	{
		getline(Doc, str);
		if (str.length() == 0) Error();
		Errors.push_back(str);
	}

	Doc.close();
	Doc.open(ListLocalisation[1].c_str());					//��������� ��������
	if (!Doc.is_open()) Error();
	for (int i = 0; !Doc.eof(); i++)
	{
		getline(Doc, str);
		Front_page.push_back(str);
	}

	Doc.close();
	Doc.open(ListLocalisation[2].c_str());					//����
	if (!Doc.is_open()) Error();
	for (int i = 0; !Doc.eof(); i++)
	{
		getline(Doc, str);
		if (str.length() == 0) Error();
		Menu.push_back(str);
	}
	Doc.close();

	Doc.open(ListLocalisation[3].c_str());					//������
	if (!Doc.is_open()) Error();
	for (int i = 0; !Doc.eof(); i++)
	{
		getline(Doc, str);
		if (str.length() == 0) Error();
		Other.push_back(str);
	}

	Doc.close();
}

ostream& operator << (ostream & out, Program & App)
{
	char key = 0;
	while (key != 27)
	{
		system("cls");
		App.ListDocs();
		cout << endl << endl;
		App.ListImages();
		cout << endl << endl;
		App.ListTables();
		cout << endl << endl << App.GetMenu(13) << endl << App.GetMenu(16) << endl;
		key = _getch();
		if (key == 9) App++;
	}
	return out;
}

void operator << (Program & Pr, char a)
{
	string str = Pr.GetConfig(14);
	str += 32;
	str += a;
	system(str.c_str());
}

void Program::AddFiles()
{
	char key = 0;
	string path;
	while (!(key >= '1' && key <= '3'))
	{
		Document Doc;
		Image Img;
		Table Tab;
		system("cls");
		ViewMenu(9, 11);
		cout << GetMenu(13) << endl << GetMenu(16) << endl;
		key = _getch();
		string str;
		int num;
		bool exist = false;
		switch (key)
		{
		case 9:
			(*this)++;
			break;
		case 27: 
			return;
		case '1':
			do
			{
				exist = false;
				cout << Menu[18];
				cin >> str;
				for (int i = 0; i < Documents.size(); i++)
					if (Documents[i].GetName() == str)
						exist = true;
				if (exist)
				{
					cout << Other[21] << endl;
				}
			} 
			while (exist);
			Doc.SetName(str);
			cout << Other[0];
			cin >> str;
			Doc.SetColor(str);
			cout << Other[2];
			cin >> num;
			while (!cin.good() || num <= 0)
			{
				cout << Errors[5];
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> num;
			}
			Doc.SetFontSize(num);
			Doc.SetDate();
			Doc.SetOwner(User);
			Doc.Write();
			if (Doc.File::Update(Config[key - 48]))
			{
				Documents.push_back(Doc);
			}
			else
			{
				cout << Errors[6] << endl; // �� ������� ������� ��������
			}
			break;
		case '2':
			do
			{
				exist = false;
				cout << Menu[18];
				cin >> str;
				for (int i = 0; i < Images.size(); i++)
					if (Images[i].GetName() == str)
						exist = true;
				if (exist)
				{
					cout << Other[21] << endl;
				}
			}
			while (exist);
			Img.SetName(str);
			Img.SetDate();
			Img.SetOwner(User);
			Img.Write();
			Img.SetDimensions();
			if (Img.Update(Config[key - 48]))
			{
				Images.push_back(Img);
			}
			else
			{
				cout << Errors[6] << endl; // �� ������� ������� ��������
			}
			break;
		case '3':
			do
			{
				exist = false;
				cout << Menu[18];
				cin >> str;
				for (int i = 0; i < Tables.size(); i++)
					if (Tables[i].GetTName() == str)
						exist = true;
				if (exist)
				{
					cout << Other[21] << endl;
				}
			} 
			while (exist);
			cout << Other[1];
			cin >> num;
			while (!cin.good() || num <= 0)
			{
				cout << Errors[5];
				cin.clear();
				cin.ignore(1000, '\n');
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
			break;
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

void Program::ReadDocImg()
{
	File* F;
	for (char key = 0; key != 27;)
	{
		system("cls");
		int counter = 0;
		cout << Other[3] << endl;
		for (int i = 0, max = Documents.size(); i < max; i++, counter++)
		{
			cout << endl << Other[4] << counter << endl;
			cout << Other[9] << Documents[i].GetName() << endl;
		}
		cout << Other[5] << endl;
		for (int i = 0, max = Images.size(); i < max; i++, counter++)
		{
			cout << endl << Other[6] << counter << endl;
			cout << Other[9] << Images[i].GetName() << endl;
		}
		
		cout << endl << Other[18] << endl;
		cout << GetMenu(13) << endl << GetMenu(16) << endl;

		int NumDocs = 0;
		int NumImgs = 0;

		key = _getch();
		switch (key)
		{
		case 9:
			(*this)++;
			continue;
		case 13:
			if (Documents.empty() && Images.empty())
			{
				cout << endl << Other[20] << endl;
				cout << Menu[20] << endl;
				_getch();
				break;
			}
			int NumOfFiles = 0;
			if (Documents.empty())
			{
				NumImgs = NumOfFiles = Images.size();
			}
			else if (Images.empty())
			{
				NumDocs = NumOfFiles = Documents.size();
			}
			else
			{
				NumOfFiles = Documents.size() + Images.size();
				NumImgs = Images.size();
				NumDocs = Documents.size();
			}
			int num;
			cout << Other[19];
			cin >> num;
			while (!cin.good() || (num < 0 && num >= NumOfFiles))
			{
				cout << Errors[5];
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> num;
			}
			if (num < Documents.size()) F = &Documents[num];
			else F = &Images[num - NumDocs];
			do
			{
				system("cls");
				vector<string> v = F->Read();
				cout << F->GetName() << endl << endl;
				for (int i = 0, max = v.size(); i < max; i++) cout << v[i] << endl;
				cout << endl << endl << Menu[14];
				char key = _getch();
			} 
			while (key != 13);
			break;
		}
	}
}

void Program::RemoveFile()
{
	string str;
	int max = 0;
	for (char key = 0; key != 27;)
	{
		str.clear();
		system("cls"); 
		cout << Menu[22] << endl << Menu[23] << endl << Menu[24] << endl << endl;
		cout << Menu[13] << endl << Menu[16] << endl;

		key = _getch();
		switch (key)
		{
		case 9:
			(*this)++;
			continue;
		case 27:
			return;
		case '1':
			if (Documents.empty())
			{
				cout << Other[20] << endl;
				cout << Menu[20] << endl;
				_getch();
				continue;
			}
			else
			{
				cout << Other[3] << endl;
				max = Documents.size();
				for (int i = 0; i < max; i++)
				{
					cout << endl << Other[4] << i << endl;
					cout << Other[9] << Documents[i].GetName() << endl;
				}
			}
			break;
		case '2':
			if (Images.empty())
			{
				cout << Other[20] << endl;
				cout << Menu[20] << endl;
				_getch();
				continue;
			}
			else
			{
				cout << Other[5] << endl;
				max = Images.size();
				for (int i = 0; i < max; i++)
				{
					cout << endl << Other[6] << i << endl;
					cout << Other[9] << Images[i].GetName() << endl;
				}
			}
			break;
		case '3':
			if (Tables.empty())
			{
				cout << Other[20] << endl;
				cout << Menu[20] << endl;
				_getch();
				continue;
			}
			else
			{
				max = Tables.size();
				cout << Other[7] << endl;
				for (int i = 0; i < max; i++)
				{
					cout << endl << Other[8] << i << endl;
					cout << Other[9] << Tables[i].GetTName() << endl;
				}
			}
			break;
		}
		str += Config[key - 48];

		int num;
		cout << Other[19];
		cin >> num;
		while (!cin.good() || !(num >= 0 && num < max))
		{
			cout << Errors[5];
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> num;
		}

		switch (key)
		{
		case '1':
			str += Documents[num].GetName();
			Documents.erase(Documents.begin() + num);
			break;
		case '2':
			str += Images[num].GetName();
			Images.erase(Images.begin() + num);
			break;
		case '3':
			str += Tables[num].GetTName();
			Tables.erase(Tables.begin() + num);
			break;
		}
		remove(str.c_str());
	}
}

void Program::OpenFile()
{
	int max = 0;
	for (char key = 0; key != 27;)
	{
		system("cls");
		cout << Menu[25] << endl << Menu[26] << endl << Menu[27] << endl << endl;
		cout << Menu[13] << endl << Menu[16] << endl;

		key = _getch();
		switch (key)
		{
		case 9:
			(*this)++;
			continue;
		case 27:
			return;
		case '1':
			if (Documents.empty())
			{
				cout << Other[20] << endl;
				cout << Menu[20] << endl;
				_getch();
				continue;
			}
			else
			{
				cout << Other[3] << endl;
				max = Documents.size();
				for (int i = 0; i < max; i++)
				{
					cout << endl << Other[4] << i << endl;
					cout << Other[9] << Documents[i].GetName() << endl;
				}
			}
			break;
		case '2':
			if (Images.empty())
			{
				cout << Other[20] << endl;
				cout << Menu[20] << endl;
				_getch();
				continue;
			}
			else
			{
				cout << Other[5] << endl;
				max = Images.size();
				for (int i = 0; i < max; i++)
				{
					cout << endl << Other[6] << i << endl;
					cout << Other[9] << Images[i].GetName() << endl;
				}
			}
			break;
		case '3':
			if (Tables.empty())
			{
				cout << Other[20] << endl;
				cout << Menu[20] << endl;
				_getch();
				continue;
			}
			else
			{
				max = Tables.size();
				cout << Other[7] << endl;
				for (int i = 0; i < max; i++)
				{
					cout << endl << Other[8] << i << endl;
					cout << Other[9] << Tables[i].GetTName() << endl;
				}
			}
			break;
		}

		int num;
		cout << Other[19];
		cin >> num;
		while (!cin.good() || !(num >= 0 && num < max))
		{
			cout << Errors[5];
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> num;
		}

		switch (key)
		{
		case '1':
			Documents[num].Write();
			break;
		case '2':
			Images[num].Write();
			break;
		case '3':
			Tables[num].Work();
			break;
		}
	}
}

bool Program::CreateSaveFile()
{
	string lineBetweenSame = Config[16];
	string lineBetweenDiff = Config[17];

	Save.clear();

	Save.push_back(local);
	Save.push_back(User);
	Save.push_back(Color);

	if (Documents.size() > 0)
	{
		Save.push_back(Config[1]);
		for (int i = 0; i < Documents.size(); i++)
		{
			Save.push_back(Documents[i].GetName());
			Save.push_back(Documents[i].GetDate());
			Save.push_back(to_string(Documents[i].GetFont()));
			Save.push_back(Documents[i].GetColor());
			Save.push_back(to_string(Documents[i].GetNumOfColumns()));
			if (i == Documents.size() - 1) { Save.push_back(lineBetweenDiff); }
			else Save.push_back(lineBetweenSame);
		}
	}
	if (Images.size() > 0)
	{
		Save.push_back(Config[2]);
		for (int i = 0; i < Images.size(); i++)
		{
			Save.push_back(Images[i].GetName());
			Save.push_back(Images[i].GetDate());
			if (i == Images.size() - 1) { Save.push_back(lineBetweenDiff); }
			else Save.push_back(lineBetweenSame);
		}
	}
	if (Tables.size() > 0)
	{
		Save.push_back(Config[3]);
		for (int i = 0; i < Tables.size(); i++)
		{
			Save.push_back(Tables[i].GetTName());
			Save.push_back(to_string(Tables[i].GetNumOfColumns()));
			if (i == Tables.size() - 1) { Save.push_back(lineBetweenDiff); }
			else Save.push_back(lineBetweenSame);
		}
	}

	int lenChecker = 0;
	for (int i = 0; i < Save.size(); i++)
	{
		lenChecker += Save[i].length();
	}

	Save.insert(Save.begin(), to_string(lenChecker));

	ifstream Doc(Config[0]);
	if (!Doc.is_open()) return false;
	string str;
	getline(Doc, str);
	Doc.close();

	remove(str.c_str());

	ofstream SaveFile(str);
	if (!SaveFile.is_open()) return false;
	for (int i = 0; i < Save.size(); i++)
	{
		SaveFile << Save[i] << endl;
	}
	return true;
}

bool Program::OpenSaveFile()
{
	string lineBetweenSame = Config[16];
	string lineBetweenDiff = Config[17];

	ifstream Doc(Config[0]);
	if (!Doc.is_open()) return false;
	string str;
	getline(Doc, str);
	Doc.close();
	int SizeOfFile;
	
	Doc.open(str);
	if (!Doc.is_open()) return false;
	string s;
	getline(Doc, s);
	SizeOfFile = stoi(s);
	int lenChecker = 0;
	while (!Doc.eof())
	{
		s.clear();
		getline(Doc, s);
		lenChecker += s.length();
	}
	Doc.close();

	if (lenChecker != SizeOfFile) return false;

	Doc.open(str);
	if (!Doc.is_open()) return false;
	getline(Doc, s);
	s.clear();
	getline(Doc, local);
	getline(Doc, User);
	getline(Doc, Color);

	string check;
	
	getline(Doc, check);
	
	string Name, Date, Font, Color, NumOfCol;

	string line;

	if (check == Config[1])
	{
		for (int i = 0; !Doc.eof(); i++)
		{
			Document T;
			Name.clear(); Date.clear(); Font.clear(); Color.clear(); NumOfCol.clear(); line.clear();
			getline(Doc, Name);
			getline(Doc, Date);
			getline(Doc, Font);
			getline(Doc, Color);
			getline(Doc, NumOfCol);
			getline(Doc, line);
			
			if (Font.length() == 0 || NumOfCol.length() == 0) continue;
			T.SetName(Name);
			T.SetDate(Date);
			T.SetFontSize(stoi(Font));
			T.SetColor(Color);
			T.SetNumOfColumns(stoi(NumOfCol));
			T.ReadFromFile(Config[1]);
			Documents.push_back(T);
			T.~Document();

			if (line == lineBetweenDiff)
			{
				break;
			}
			else if (line != lineBetweenSame)
			{
				return false;
			}
		}
		getline(Doc, check);
	}

	if (check == Config[2])
	{
		for (int i = 0; !Doc.eof(); i++)
		{
			Image T;
			Name.clear(); Date.clear(); Font.clear(); Color.clear(); NumOfCol.clear(); line.clear();
			getline(Doc, Name);
			getline(Doc, Date);
			getline(Doc, line);

			T.SetName(Name);
			T.SetDate(Date);
			T.ReadFromFile(Config[2]);
			T.SetDimensions();
			Images.push_back(T);
			T.~Image();

			if (line == lineBetweenDiff)
			{
				break;
			}
			else if (line != lineBetweenSame)
			{
				return false;
			}
		}
		getline(Doc, check);
	}

	if (check == Config[3])
	{
		for (int i = 0; !Doc.eof(); i++)
		{
			Table T;
			Name.clear(); Date.clear(); Font.clear(); Color.clear(); NumOfCol.clear(); line.clear();
			getline(Doc, Name);
			getline(Doc, NumOfCol);
			getline(Doc, line);

			T.SetTName(Name);
			T.SetNumOfColumns(stoi(NumOfCol));
			T.ReadFromFile(Config[3]);
			T.SetMax();
			Tables.push_back(T);
			T.~Table();

			if (line == lineBetweenDiff)
			{
				break;
			}
			else if (line != lineBetweenSame)
			{
				return false;
			}
		}
	}
	return true;
}

void Program::Options()
{
	char color = 0;
	for (char key = 0; key != 27;)
	{
		system("cls");
		cout << Menu[29] << endl << Menu[30] << endl << endl << Menu[16] << endl;
		key = _getch();
		switch (tolower(key))
		{
		case 9:
			(*this)++;
			continue;
		case '1':
			system("cls");
			for (int i = 22; i < 31; i++) cout << Other[i] << endl;
			for (; color < '1' || color > '9';)
			{
				color = _getch();
				if (color < '1' || color > '9')
				{
					cout << Errors[5];
				}
			}
			(*this) << color;
			Color = color;
			color = 0;
			break;
		case '2':
			system("cls");
			cout << Menu[31];
			string str;
			bool exp = true;
			while (exp)
			{
				cin >> str;
				ofstream Doc(str);
				if (Doc.is_open()) exp = false;
				else Doc.close();
				if (exp) { cout << Errors[6] << endl << Errors[5]; cin.clear(); }
			}
			remove(Config[0].c_str());
			ofstream Doc(Config[0]);
			Doc << str;
			break;
		}
	}
}
