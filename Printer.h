#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <sstream>

#include "ConsoleProperties.h"

using namespace std;

enum class Color
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHT_GRAY,
	DARK_GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	YELLOW,
	WHITE
};

class Printer
{
	string* colors;
	Color font;
	Color background;

public:
	Printer(Color f = Color::WHITE, Color back = Color::BLACK) : font(f), background(back)
	{
		colors = new string[16] { "BLACK", "BLUE", "GREEN", "CYAN", "RED", "MAGENTA", "BROWN",
			"LIGHT_GRAY", "DARK_GRAY", "LIGHT_BLUE", "LIGHT_GREEN", "LIGHT_CYAN",
			"LIGHT_RED", "LIGHT_MAGENTA", "YELLOW", "WHITE" };
	}

	template <class T>
	void print(T text) const
	{

		int _font = static_cast<int>(font);
		int _back = static_cast<int>(background);

		SetConsoleTextAttribute(hConsole, _font + 16 * _back);

		ostringstream out;
		out << text;
		cout << out.str() << endl;

		cursor.X += out.str().size();

		setCursorAt(cursor.X, cursor.Y);

		SetConsoleTextAttribute(hConsole, 15);  // return to normal state
	}

	string indicateColor(Color _color) const
	{
		string col;

		switch (_color)
		{
		case Color::BLACK: col = "BLACK";
			break;
		case Color::BLUE: col = "BLUE";
			break;
		case Color::GREEN: col = "GREEN";
			break;
		case Color::CYAN: col = "CYAN";
			break;
		case Color::RED: col = "RED";
			break;
		case Color::MAGENTA: col = "MAGENTA";
			break;
		case Color::BROWN: col = "BROWN";
			break;
		case Color::LIGHT_GRAY: col = "LIGHT_GRAY";
			break;
		case Color::DARK_GRAY: col = "DARK_GRAY";
			break;
		case Color::LIGHT_BLUE: col = "LIGHT_BLUE";
			break;
		case Color::LIGHT_GREEN: col = "LIGHT_GREEN";
			break;
		case Color::LIGHT_CYAN: col = "LIGHT_CYAN";
			break;
		case Color::LIGHT_RED: col = "LIGHT_RED";
			break;
		case Color::LIGHT_MAGENTA: col = "LIGHT_MAGENTA";
			break;
		case Color::YELLOW: col = "YELLOW";
			break;
		case Color::WHITE: col = "WHITE";
			break;
		default: col = "No such color";
		}
		return col;
	}

	string getFont() const
	{
		return indicateColor(font);
	}

	string getBackground() const
	{
		return indicateColor(background);
	}

	friend istream& operator>>(istream& in, Printer& p)
	{
		string font_c, back_c;
		in >> font_c >> back_c;
		for (size_t i = 0; i < 16; ++i)
		{
			if (font_c == p.colors[i])
				p.font = static_cast<Color>(i);

			if (back_c == p.colors[i])
				p.background = static_cast<Color>(i);
		}
			return in;
	}

	~Printer() { delete[] colors; }
};