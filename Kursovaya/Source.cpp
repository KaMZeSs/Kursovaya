#pragma once
#include "libs.h"
#include "Image.h"
#include "Program.h"

void ListAll(Program & App);

int main()
{
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
		cout << App.GetMenu(21) << endl << endl << App.GetMenu(15) << endl << App.GetMenu(17) << endl;
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
			App.OpenFile();
			break;
		case '3':
			cout << App;
			break;
		case '4':
			App.ReadDocImg();
			break;
		case '5':
			App.RemoveFile();
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