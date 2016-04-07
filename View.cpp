#pragma once

#include <Windows.h>

#include "View.h"
#include "ConsoleProperties.h"
#include "Printer.h"

using namespace std;

void View::drawBackground(int left, int top, int width, int height, COLORREF background)
{
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SelectObject(hdc, GetStockObject(DC_PEN));

	SetDCBrushColor(hdc, background);
	SetDCPenColor(hdc, background);

	GetClientRect(hwnd, &rect);
	Rectangle(hdc, left, top, left + width, top + height);
}

void View::clear()
{
	system("cls");

	drawBackground(0, 0, CONSOLE_WIDTH*FONT_WIDTH, CONSOLE_HEIGHT*FONT_HEIGHT, RGB(0, 100, 200));
}