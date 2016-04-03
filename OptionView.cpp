#pragma once

#include <conio.h>

#include "FieldView.h"
#include "OptionView.h"
#include "ConsoleProperties.h"

using namespace std;

OptionView::OptionView()
	:menuCurrent(0)
{
	menu.push_back(MenuItem("English", CONSOLE_WIDTH / 5, 2));
	menu.push_back(MenuItem("Ukrainian", 3 * CONSOLE_WIDTH / 5, 2));
	menu.push_back(MenuItem("Easy", CONSOLE_WIDTH / 5, CONSOLE_HEIGHT/3 + 2));
	menu.push_back(MenuItem("Medium", CONSOLE_WIDTH / 5 + CONSOLE_WIDTH / 4, CONSOLE_HEIGHT/3 + 2));
	menu.push_back(MenuItem("Hard", CONSOLE_WIDTH / 5 + (CONSOLE_WIDTH / 4)*2, CONSOLE_HEIGHT/3 + 2));
	menu.push_back(MenuItem("Back to menu", CONSOLE_WIDTH / 6, CONSOLE_HEIGHT - 2));
	menu.push_back(MenuItem("Start game", 4 * CONSOLE_WIDTH / 6, CONSOLE_HEIGHT - 2));
	menu[0].chosen = true;
}

View* OptionView::handle() 
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
			case 75: // left
				menu[menuCurrent].chosen = false;
				--menuCurrent;

				if (menuCurrent == -1)
				{
					menuCurrent = 6;
				}

				menu[menuCurrent].chosen = true;

				drawMenu();
				break;
			case 77: //right
				menu[menuCurrent].chosen = false;

				++menuCurrent;

				if (menuCurrent == 7)
				{
					menuCurrent = 0;
				}

				menu[menuCurrent].chosen = true;

				drawMenu();

				break;
			}
			break;
		case VK_RETURN:
			switch (menuCurrent)
			{
			case 0:
				options.setLanguage(Language::ENGLISH); 
				break;
			case 1:
				options.setLanguage(Language::UKRAINIAN);
				break;
			case 2:
				options.setDifficulty(Difficulty::EASY);
				break;
			case 3:
				options.setDifficulty(Difficulty::MIDDLE);
				break;
			case 4:
				options.setDifficulty(Difficulty::HARD);
				break;
			case 5:
				current = new StartView;
				finish = true;
				break;
			case 6:
				current = new FieldView;
				finish = true;
			}
			break;
		}
	}

	return current;
}

void OptionView::draw()
{
	clear();

	drawBackground(0, 0, CONSOLE_WIDTH*FONT_WIDTH, CONSOLE_HEIGHT*FONT_HEIGHT, RGB(0, 100, 200));

	setCursorAt(0, 1);
	printAtCenter("Language:", headline);

	setCursorAt(CONSOLE_WIDTH / 2, CONSOLE_HEIGHT / 3);
	printAtCenter("Difficulty:", headline);

	drawMenu();
}

void OptionView::drawMenu()
{
	for (size_t i = 0; i < 7; ++i)
	{
		setCursorAt(menu[i].x, menu[i].y);

		if (menu[i].chosen)
		{
			menuActive.print(menu[i].text);
		}
		else
		{
			menuPassive.print(menu[i].text);
		}
	}
}