#pragma once

#include <conio.h>

#include "ResultView.h"
#include "StartView.h"
#include "ConsoleProperties.h"

using namespace std;

ResultView::ResultView(Player pl)
	:p(pl)
{
}

void ResultView::draw()
{
	clear();
}

View* ResultView::handle()
{
	setCursorAt(2, 2);

	if (options.getLanguage() == Language::ENGLISH)
	{
		printAtCenter("GAME OVER", headline);

		setCursorAt(CONSOLE_WIDTH / 5, 4);
		stats.print("Enter your name: ");
	}
	else
	{
		printAtCenter("ГРУ ЗАВЕРШЕНО", headline);

		setCursorAt(CONSOLE_WIDTH / 5, 4);
		stats.print("Введіть ваше ім'я: ");
	}

	setCursorAt(cursor.X, cursor.Y);

	string name = getUserTextInput(15);

	Player toReturn = this->p;
	toReturn.nickname = name;

	options.addPlayer(toReturn);

	if (options.getLanguage() == Language::ENGLISH)
	{
		setCursorAt(CONSOLE_WIDTH / 5, 6);
		stats.print("Your result was added to our database");
		setCursorAt(CONSOLE_WIDTH / 5, 8);
		stats.print("Press any key to continue");
	}
	else
	{
		setCursorAt(CONSOLE_WIDTH / 5, 6);
		stats.print("Ваш результат додано в список рекордів");
		setCursorAt(CONSOLE_WIDTH / 5, 8);
		stats.print("Натисніть будь-яку клавішу для продовження");
	}

	_getch();

	return new StartView;
}