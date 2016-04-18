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
		printAtCenter("�������", headline);

		setCursorAt(0, 3);
		techData.print("��'�:            �������: �����:   ����:          г����:   ");
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
					language = "���������     ";
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
					language = "���������     ";
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
					level = "������    ";
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
					level = "�������  ";
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
					level = "��������  ";
				}
			}

			stats.print(name + score + letters + language + level);
		}
	

	setCursorAt(0, cursor.Y + 2);
	techData.print("Press any key to exit");

	_getch();

	return new StartView;
}