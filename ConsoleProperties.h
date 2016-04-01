#pragma once

#include <sstream>
#include <string>
#include "Printer.h"

using namespace std;

void setConsoleProperties();

void setCursorAt(int, int);

void printAtCenter(string st, const Printer& p);

template<class T>
string toString(const T& t)
{
	ostringstream oStream;
	oStream << t;
	return oStream.str();
}

extern Printer headline;
extern Printer menuActive;
extern Printer menuPassive;
extern Printer finish;
extern Printer techData;
extern Printer stats;
extern Printer letterPrint;
extern Printer rightLetterPrint;
extern Printer wrongLetterPrint;

extern HWND hwnd;
extern HANDLE hConsole;
extern HDC hdc;
extern RECT rect;
extern COORD cursor;
extern POINT op;

extern const int FONT_WIDTH;
extern const int FONT_HEIGHT;
extern const int CONSOLE_WIDTH;
extern const int CONSOLE_HEIGHT;
