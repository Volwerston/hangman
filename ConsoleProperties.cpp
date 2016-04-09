#pragma once

#include <conio.h>

#include "ConsoleProperties.h"

using namespace std;

Printer headline(Color::YELLOW, Color::BLUE);
Printer menuPassive(Color::YELLOW, Color::BROWN);
Printer menuActive(Color::YELLOW, Color::RED);
Printer techData(Color::BLACK, Color::WHITE);
Printer stats(Color::WHITE, Color::LIGHT_BLUE);
Printer letterPrint(Color::BLACK, Color::WHITE);
Printer rightLetterPrint(Color::LIGHT_GREEN, Color::WHITE);
Printer wrongLetterPrint(Color::LIGHT_GREEN, Color::WHITE);

HWND hwnd = GetConsoleWindow();
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HDC hdc = GetDC(hwnd);
RECT rect;
COORD cursor;
POINT op;

const int FONT_WIDTH = 11;
const int FONT_HEIGHT = 18;
const int CONSOLE_WIDTH = 60;
const int CONSOLE_HEIGHT = 30;

Options options;

void setConsoleProperties()
{

	// ? must be working
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// setting text font
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = 18; // leave X as zero
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(hConsole, NULL, &info);

	// making cursor invisible
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);

	// making edges immutable
	HMENU hm = GetSystemMenu(GetConsoleWindow(), FALSE);
	RemoveMenu(hm, SC_SIZE, MF_BYCOMMAND | MF_REMOVE);
	RemoveMenu(hm, SC_MAXIMIZE, MF_BYCOMMAND | MF_REMOVE);
	DrawMenuBar(GetConsoleWindow());

	// configuring buffer and window
	SMALL_RECT r;
	r.Left = 0;
	r.Top = 0;
	r.Right = CONSOLE_WIDTH - 1;
	r.Bottom = CONSOLE_HEIGHT - 1;
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &r);

	COORD c;
	c.X = CONSOLE_WIDTH;
	c.Y = CONSOLE_HEIGHT;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setCursorAt(int x, int y)
{
	cursor.X = x;
	cursor.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
}

void printAtCenter(string st, const Printer& p)
{
	int size = st.size();
	int x_pos = (CONSOLE_WIDTH - size) / 2 + (CONSOLE_WIDTH - size) % 2;
	setCursorAt(x_pos, cursor.Y);
	p.print(st);
}

string getUserTextInput(int len)
{
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_RED);

	bool properlyInserted = false;
	int numOfFilled = 0;
	string name;
	int c;

	int startCursorX = cursor.X;

	while (!properlyInserted)
	{
		c = _getch();

		if (c == ' ')
		{
			if (name != "" && numOfFilled < len)
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
			if (numOfFilled < len)
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

	return name;
}