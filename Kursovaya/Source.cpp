#pragma once
#include "libs.h"
#include "Image.h"
#include "Program.h"

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
		App.CreateSaveFile();
		system("cls");
		App.ViewMenu(1, 8);
		cout << App.GetMenu(21) << endl << endl << App.GetMenu(35) << endl << App.GetMenu(28) << endl << App.GetMenu(15) << endl << App.GetMenu(17) << endl;
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
		case 'o':
			App.Options();
			break;
		case 's':
			if (!App.ListAllInFile()) { cout << App.GetMenu(42); _getch(); }
			break;
		case 'p':
			App.SecretOptions();
			break;
		}
	}
	return 0;
}