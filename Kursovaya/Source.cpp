#pragma once
#include "libs.h"
#include "Image.h"
#include "Program.h"

int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	Program App;

	for (char key = ' '; key != 13;)
	{
		App.ShowTitle();
		if ((key = _getch()) == 9) App++;
	}

	for (char key = ' '; key != 27;)
	{
		system("cls");
		App.ViewMenu(1, 7);
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
			break;
		case '4':
			break;
		case '5':
			break;
		case '6':
			break;
		case '7':
			break;
		case 's':
			App << '5';
			break;
		}
	}
	system("pause");
	return 0;
}