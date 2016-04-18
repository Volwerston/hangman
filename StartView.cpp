#pragma once

#include <string>
#include <cmath>
#include <conio.h>

#include "StartView.h"
#include "ConsoleProperties.h"
#include "OptionView.h"
#include "SideBar.h"
#include "FieldView.h"
#include "HighScoreView.h"

using namespace std;

void StartView::drawMenu()
{
	string bufferLeft;
	string bufferRight;

	for (size_t i = 0; i < 4; ++i)
	{
		// some ugly positioning stuff that makes things look  beautiful :)

		bufferLeft = string((CONSOLE_WIDTH / 3 - menu[i].text.length()) / 2, ' ');
		bufferRight = string(((CONSOLE_WIDTH / 3 - menu[i].text.length()) / 2) + menu[i].text.length() % 2, ' ');

		setCursorAt(2 * CONSOLE_WIDTH / 4, (CONSOLE_HEIGHT / 6)*(i + 1));

		if (menu[i].chosen == true)
		{
			menuActive.print(bufferLeft + menu[i].text + bufferRight);
		}
		else
		{
			menuPassive.print(bufferLeft + menu[i].text + bufferRight);
		}
	}
}

View* StartView::handle()
{
	bool finish = false;
	int c;

	View* current = this;

	while (!finish)
	{
		c = _getch();
		switch (c)
		{
		case 224:
			switch (_getch())
			{
			case 72:
				if (menuCurrent > 0)
				{
					menu[menuCurrent].chosen = false;
					--menuCurrent;
					menu[menuCurrent].chosen = true;

					drawMenu();
				}
				break;
			case 80:
				if (menuCurrent < 3)
				{
					menu[menuCurrent].chosen = false;
					++menuCurrent;
					menu[menuCurrent].chosen = true;

					drawMenu();
				}
				break;
			}
			break;
		case VK_RETURN:
			Action currentAct = Action(menuCurrent);

			switch (currentAct)
			{
			case Action::START:
				current = new FieldView;
				finish = true;
				break;
			case Action::OPTIONS:
				current = new OptionView;
				finish = true;
				break;
			case Action::HIGH_SCORES:
				current = new HighScoreView;
				finish = true;
				break;
			case Action::EXIT:
				current = nullptr;
				finish = true;
			}
			break;
		}
	}

	return current;
}

void StartView::draw()
{
	clear();
	setCursorAt(CONSOLE_WIDTH / 3, 0);

	if (options.getLanguage() == Language::ENGLISH)
	{
		headline.print("WELCOME TO HANGMAN");
	}
	else
	{
		headline.print("Â²ÒÀÞ Â ÃÐ² HANGMAN");
	}

	drawMenu();
}
