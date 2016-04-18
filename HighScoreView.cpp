#pragma once

#include "HighScoreView.h"
#include "ConsoleProperties.h"
#include "StartView.h"

#include <conio.h>

void HighScoreView::draw()
{
	clear();
}

View* HighScoreView::handle()
{
	setCursorAt(0, 1);

	if (options.getLanguage() == Language::ENGLISH)
	{
		printAtCenter("HIGH SCORES", headline);

		setCursorAt(0, 3);
		techData.print("Name:            Score:   Letters: Language:      Level:    ");
	}
	else
	{
		printAtCenter("РЕКОРДИ", headline);

		setCursorAt(0, 3);
		techData.print("Ім'я:            Рахунок: Букви:   Мова:          Рівень:   ");
	}

		for (size_t i = 0; i < options.getRecords().size(); ++i)
		{
			setCursorAt(0, 5 + i);

			vector<Player> buffer = options.getRecords();

			string name = toString(buffer[i].nickname) + string(17 - toString(buffer[i].nickname).size(), ' ');
			string score = toString(buffer[i].score) + string(9 - toString(buffer[i].score).size(), ' ');
			string letters = toString(buffer[i].numLetters) + string(9 - toString(buffer[i].numLetters).size(), ' ');
			string language;
			string level;

			if (buffer[i].langUsed == Language::ENGLISH)
			{
				if (options.getLanguage() == Language::ENGLISH)
				{
					language = "English        ";
				}
				else
				{
					language = "Англійська     ";
				}
			}
			else
			{
				if (options.getLanguage() == Language::ENGLISH)
				{
					language = "Ukrainian      ";
				}
				else
				{
					language = "Українська     ";
				}
			}

			if (buffer[i].topLevel == Difficulty::EASY)
			{
				if (options.getLanguage() == Language::ENGLISH)
				{
					level = "Easy      ";
				}
				else
				{
					level = "Легкий    ";
				}
			}
			else if (buffer[i].topLevel == Difficulty::MIDDLE)
			{
				if (options.getLanguage() == Language::ENGLISH)
				{
					level = "Medium    ";
				}
				else
				{
					level = "Середній  ";
				}
			}
			else
			{
				if (options.getLanguage() == Language::ENGLISH)
				{
					level = "Hard      ";
				}
				else
				{
					level = "Складний  ";
				}
			}

			stats.print(name + score + letters + language + level);
		}
	

	setCursorAt(0, cursor.Y + 2);
	techData.print("Press any key to exit");

	_getch();

	return new StartView;
}