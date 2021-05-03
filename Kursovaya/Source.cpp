#pragma once
#include "libs.h"
#include "Image.h"
#include "Program.h"

void ListAll(Program & App);

int main()
{
	//setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Program App;

	for (char key = 0; key != 13;)
	{
		App.ShowTitle();
		if ((key = _getch()) == 9) App++;
	}

	for (char key = 0; key != 27;)
	{
		system("cls");
		App.ViewMenu(1, 8);
		cout << App.GetMenu(15) << endl << App.GetMenu(17) << endl;
		key = _getch();
		switch (tolower(key))
		{
		case 9:
			App++;
			continue;
		case '1':
			App.AddFiles();
			break;
		case '2':
			break;
		case '3':
			ListAll(App);
			break;
		case '4':
			App.ReadDocImg();
			break;
		case '5':
			break;
		case '6':
			break;
		case '7':
			break;
		case '8':
			break;
		case 's':
			App << '5';
			break;
		}
	}
	system("pause");
	return 0;
}

void ListAll(Program & App)
{
	char key = 0;
	while (key != 27)
	{
		system("cls");
		App.ListDocs();
		cout << endl;
		App.ListImages();
		cout << endl;
		App.ListTables();
		cout << endl << endl << App.GetMenu(13) << endl << App.GetMenu(16) << endl;
		key = _getch();
		if (key == 9) App++;
	}
}