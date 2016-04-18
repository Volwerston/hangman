#pragma once

#include <Windows.h>
#include <conio.h>
#include <cctype>

#include "FieldView.h"
#include "ConsoleProperties.h"
#include "ResultView.h"

using namespace std;


char getUkrCapital(char ch)
{
	char toReturn;
	switch (ch)
	{
	case 'à':
		toReturn = 'À';
		break;
	case 'á':
		toReturn = 'Á';
		break;
	case 'â':
		toReturn = 'Â';
		break;
	case 'ã':
		toReturn = 'Ã';
		break;
	case 'ä':
		toReturn = 'Ä';
		break;
	case 'å':
		toReturn = 'Å';
		break;
	case 'º':
		toReturn = 'ª';
		break;
	case 'æ':
		toReturn = 'Æ';
		break;
	case 'ç':
		toReturn = 'Ç';
		break;
	case 'è':
		toReturn = 'È';
		break;
	case '³':
		toReturn = '²';
		break;
	case '¿':
		toReturn = '¯';
		break;
	case 'é':
		toReturn = 'É';
		break;
	case 'ê':
		toReturn = 'Ê';
		break;
	case 'ë':
		toReturn = 'Ë';
		break;
	case 'ì':
		toReturn = 'Ì';
		break;
	case 'í':
		toReturn = 'Í';
		break;
	case 'î':
		toReturn = 'Î';
		break;
	case 'ï':
		toReturn = 'Ï';
		break;
	case 'ð':
		toReturn = 'Ð';
		break;
	case 'ñ':
		toReturn = 'Ñ';
		break;
	case 'ò':
		toReturn = 'Ò';
		break;
	case 'ó':
		toReturn = 'Ó';
		break;
	case 'ô':
		toReturn = 'Ô';
		break;
	case 'õ':
		toReturn = 'Õ';
		break;
	case 'ö':
		toReturn = 'Ö';
		break;
	case '÷':
		toReturn = '×';
		break;
	case 'ø':
		toReturn = 'Ø';
		break;
	case 'ù':
		toReturn = 'Ù';
		break;
	case 'ü':
		toReturn = 'Ü';
		break;
	case 'þ':
		toReturn = 'Þ';
		break;
	case 'ÿ':
		toReturn = 'ß';
		break;
	default:
		toReturn = ch;
		break;
	}

	return toReturn;
}

char getUserNick()
{
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE| BACKGROUND_RED);

	bool properlyInserted = false;
	int numOfFilled = 0;
	int nameSize = 1;
	string name;
	int c;
	
	int startCursorX = cursor.X;

	while (!properlyInserted)
	{
		c = _getch();

		if (c == ' ')
		{
			if (name != "" && numOfFilled < nameSize)
			{
				name += ' ';
				cout << " ";
				cursor.X++;
				numOfFilled++;
			}
		}
		else if (c == VK_RETURN)
		{
			if (name != "")
			{
				properlyInserted = true;

				cursor.X = startCursorX;
				SetConsoleCursorPosition(hConsole, cursor);

				cout << " ";
			}
		}
		else if (c == 8)
		{
			if (name != "")
			{
				name.erase(name.size() - 1, 1);
				numOfFilled--;
				cursor.X--;
				SetConsoleCursorPosition(hConsole, cursor);
				cout << " ";
			}
		}
		else
		{
			if (numOfFilled < nameSize)
			{
				numOfFilled++;
				cursor.X++;
				name += (char)c;
				cout << (char)c;
			}
		}
		if (name == "")
		{
			cursor.X = startCursorX;
			SetConsoleCursorPosition(hConsole, cursor);
		}
	}

	char alt;

	if (options.getLanguage() == Language::UKRAINIAN)
	{
		alt = getUkrCapital(name[0]);
	}
	else
	{
		alt = toupper(name[0]);
	}

	return alt;
}

void FieldView::draw()
{
	clear();

	makeSettings();

	info.draw();

	setCursorAt(30, 0);

	if (options.getLanguage() == Language::ENGLISH)
	{
		techData.print("INSERT A SYMBOL: ");
	}
	else
	{
		techData.print("ÂÂÅÄ²ÒÜ Ë²ÒÅÐÓ: ");
	}

	setCursorAt(CONSOLE_WIDTH / 10, CONSOLE_HEIGHT / 2);

	for (size_t i = 0; i < sizeOfWord; ++i)
	{
		word[i].draw();
	}

	setCursorAt(cursor.X, 2*CONSOLE_HEIGHT / 3 - 1);

	if (options.getLanguage() == Language::ENGLISH)
	{
		printAtCenter("Used letters: ", headline);
	}
	else
	{
		printAtCenter("Âèêîðèñòàí³ ë³òåðè: ", headline);
	}
	
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

bool FieldView::allLettersGuessed()
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

	if (options.getLevel() == Difficulty::EASY)
	{
		options.easyUsed = true;
	}
	else if (options.getLevel() == Difficulty::MIDDLE)
	{
		options.middleUsed = true;
	}
	else
	{
		options.hardUsed = true;
	}
}

void FieldView::addUsed(char let)
{
	bool letterFound = false;

	for (size_t i = 0; i < sizeOfWord; ++i)
	{
		if (word[i].letter == let)
		{
			letterFound = true;

			if (!word[i].active)
			{
				++info.numOfLetters;
				word[i].active = true;
				word[i].draw();
			}
		}
	}


	if (!letterFound)
	{
		bool alreadyAdded = false;

		for (size_t i = 0; i < numOfUsed; ++i)
		{
			if (usedLetter[i / 10][i % 10].letter == let)
			{
				alreadyAdded = true;
				break;
			}
		}

		if (!alreadyAdded)
		{
			for (size_t i = 0; i < options.langTemplate.size(); ++i)
			{
				if (options.langTemplate[i] == let)
				{
					usedLetter[numOfUsed / 10][numOfUsed % 10].letter = let;
					usedLetter[numOfUsed / 10][numOfUsed % 10].active = true;
					usedLetter[numOfUsed / 10][numOfUsed % 10].draw();
					++numOfUsed;
					break;
				}
			}

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
}

Result FieldView::getResult()
{
	Result res = Result::DEFEAT;
	bool finished = false;

	while (!finished)
	{
		setCursorAt(50, 0);

		char input = getUserNick();

		bool found = false;

		addUsed(input);

		info.draw();

		if (allLettersGuessed())
		{
			info.numOfLetters = 0;
			info.life += 3;
			res = Result::VICTORY;

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

			finished = true;
		}
		else if (info.life <= 0)
		{
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
		info.draw();


		Difficulty cur = options.getLevel();
		string currWord = options.chooseWord();
		Difficulty cur1 = options.getLevel();

		for (size_t i = 0; i < sizeOfWord; ++i)
		{
			word[i].active = false;
		}

		if (cur != cur1)
		{
			drawBackground(word[0].left - 1, word[0].top - 1,
				options.numOfWords * 51, word[0].top + 51, RGB(0, 100, 200));

			if (options.getLevel() == Difficulty::EASY)
			{
				options.easyUsed = true;
			}
			else if (options.getLevel() == Difficulty::MIDDLE)
			{
				options.middleUsed = true;
			}
			else
			{
				options.hardUsed = true;
			}
		}

		if (currWord == "")
		{
			res = Result::DEFEAT;
		}
		else
		{
			sizeOfWord = currWord.size();

			for (size_t i = 0; i < sizeOfWord; ++i)
			{
				word[i].letter = currWord[i];
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

	Player toReturn;

	toReturn.langUsed = options.getLanguage();

	if (options.hardUsed)
	{
		toReturn.topLevel = Difficulty::HARD;
	}
	else if (options.middleUsed)
	{
		toReturn.topLevel = Difficulty::MIDDLE;
	}
	else
	{
		toReturn.topLevel = Difficulty::EASY;
	}

	toReturn.score = info.score;
	toReturn.numLetters = info.numOfLetters;

	return new ResultView(toReturn);
}