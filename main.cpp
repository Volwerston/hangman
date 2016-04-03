#include <iostream>
#include <conio.h>

#include "View.h"
#include "StartView.h"
#include "ConsoleProperties.h"
#include "SideBar.h"
#include "FieldView.h";
#include "Options.h"
#include "OptionView.h"

using namespace std;

int main()
{
	setConsoleProperties();

	View* game = new StartView;

	while (game != nullptr)
	{
		game->draw();

		View* current = game->handle();

		if (current != game)
		{
			delete game;
			game = current;
		}
	}

	_getch();
	return 0;
}