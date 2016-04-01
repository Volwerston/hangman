#pragma once

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