#pragma once

#include <Windows.h>

#include "FieldView.h"
#include "ConsoleProperties.h"

using namespace std;

void FieldView::draw()
{
	clear();

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
			usedLetter[i][j].draw();
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
	}
}