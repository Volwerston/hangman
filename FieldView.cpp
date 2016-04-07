#pragma once

#include <Windows.h>
#include <conio.h>

#include "FieldView.h"
#include "ConsoleProperties.h"

using namespace std;

void FieldView::draw()
{
	clear();

	makeSettings();

	info.draw();

	setCursorAt(30, 0);
	techData.print("INSERT A SYMBOL: ");

	setCursorAt(CONSOLE_WIDTH / 10, CONSOLE_HEIGHT / 2);

	for (size_t i = 0; i < sizeOfWord; ++i)
	{
		word[i].draw();
	}

	setCursorAt(cursor.X, 2*CONSOLE_HEIGHT / 3 - 1);
	printAtCenter("Used letters: ", headline);
	
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 10; ++j)
		{
			if (usedLetter[i][j].active)
			{
				usedLetter[i][j].draw();
			}
			else
			{
				break;
			}
		}
	}
	

	// make _getch() for a letter ('s gonna be so funny)
}

FieldView::Letter::Letter(char _let, bool _gue, int _l, int _t, int _w, int _h)
	: letter(_let),
	active(_gue),
	left(_l),
	top(_t),
	width(_w),
	height(_h)
{
}

bool FieldView::allGuessed()
{
	bool all = true;

	for (size_t i = 0; i < sizeOfWord; ++i)
	{
		if (!word[i].active)
		{
			all = false;
			break;
		}
	}

	return all;
}

void FieldView::makeSettings()
{
	options.loadDictionary();

	if (options.getLevel() == Difficulty::EASY)
	{
		info.life = 40;
	}
	else if (options.getLevel() == Difficulty::MIDDLE)
	{
		info.life = 35;
	}
	else
	{
		info.life = 30;
	}

	string currWord = options.chooseWord();

	sizeOfWord = currWord.size();

	for (size_t i = 0; i < sizeOfWord; ++i)
	{
		word[i].letter = currWord[i];
		//word[i].active = true;
	}
}

void FieldView::Letter::draw()
{

	SelectObject(hdc, GetStockObject(DC_PEN));
	SelectObject(hdc, GetStockObject(DC_BRUSH));

	SetDCBrushColor(hdc, RGB(255, 255, 255));
	SetDCPenColor(hdc, RGB(0, 0, 0));

	GetClientRect(hwnd, &rect);
	Rectangle(hdc, left, top,left + width, top + height);

	if (active)
	{
		setCursorAt((left + width / 2) / FONT_WIDTH, (top + height / 2) / FONT_HEIGHT);
		letterPrint.print(letter);
	}
}

void FieldView::addUsed(char let)
{
	bool found = false;

	for (size_t i = 0; i < numOfUsed; ++i)
	{
		if (usedLetter[i / 10][i % 10].letter == let)
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		usedLetter[numOfUsed / 10][numOfUsed % 10].letter = let;
		usedLetter[numOfUsed / 10][numOfUsed % 10].active = true;
		++numOfUsed;

		bool isRight = false;

		for (size_t i = 0; i < sizeOfWord; ++i)
		{
			if (let == word[i].letter)
			{
				isRight = true;
				break;
			}
		}

		if (!isRight)
		{
			if (options.level == Difficulty::EASY)
			{
				info.life -= 3;
			}
			else if (options.level == Difficulty::MIDDLE)
			{
				info.life -= 2;
			}
			else
			{
				--info.life;
			}
		}
	}

		usedLetter[(numOfUsed-1)/10][(numOfUsed-1) % 10].draw();
}

Result FieldView::getResult()
{
	Result res = Result::DEFEAT;
	bool finished = false;

	while (!finished)
	{
		setCursorAt(50, 0);

		int input = _getch();

		cout << char(input) << endl;

		bool found = false;

		for (size_t i = 0; i < sizeOfWord; ++i)
		{
			if (word[i].letter == toupper(char(input)))
			{
				found = true;

				if (!word[i].active)
				{
					++info.numOfLetters;
					word[i].active = true;
					word[i].draw();
					addUsed(toupper(char(input)));
				}
			}
		}

		if (found == false)
		{

			for (size_t i = 0; i < options.langTemplate.size(); ++i)
			{
				if (options.langTemplate[i] == toupper(input))
				{
					addUsed(toupper(char(input)));
					break;
				}
			}
		}

		info.draw();

		if (allGuessed())
		{
			cout << "You won" << endl;
			info.life += 3;
			res = Result::VICTORY;
			finished = true;
		}
		else if (info.life <= 0)
		{
			cout << "Defeat" << endl;
			res = Result::DEFEAT;
			finished = true;
		}
	}

	return res;
}

View* FieldView::handle()
{
	Result res = getResult();

	while (res != Result::DEFEAT)
	{
		info.numOfLetters = 0;
		
		if (options.level == Difficulty::EASY)
		{
			++info.score;
		}
		else if (options.level == Difficulty::MIDDLE)
		{
			info.score += 2;
		}
		else
		{
			info.score += 3;
		}

		info.draw();
		Difficulty cur = options.getLevel();
		string currWord = options.chooseWord();
		Difficulty cur1 = options.getLevel();

		if (cur != cur1)
		{
			drawBackground(word[0].left - 1, word[0].top - 1,
				options.numOfWords * 51, word[0].top + 51, RGB(0, 100, 200));
		}

		if (currWord == "")
		{
			cout << "All words are guessed!" << endl;
			res = Result::DEFEAT;
		}
		else
		{
			sizeOfWord = currWord.size();

			for (size_t i = 0; i < sizeOfWord; ++i)
			{
				word[i].letter = currWord[i];
				word[i].active = true;
				word[i].draw();
			}

			numOfUsed = 0;

			for (size_t i = 0; i < numOfUsed; ++i)
			{
				usedLetter[i / 10][i % 10].letter = ' ';
				usedLetter[i / 10][i % 10].active = false;
			}

			drawBackground(0, 2 * FONT_HEIGHT*CONSOLE_HEIGHT / 3, CONSOLE_WIDTH*FONT_WIDTH, CONSOLE_HEIGHT*FONT_HEIGHT,
				RGB(0, 100, 200));


			res = getResult();
		}
	}

	return nullptr;
}