#pragma once

#include "View.h"
#include "ConsoleProperties.h"

class SideBar: public View
{
	friend class FieldView;
	friend class Options;

	int life;
	int score;
	int numOfVictories;
	int numOfLetters;
	int width;
	int height;
	int left;
	int top;

	View* handle() { return nullptr; }
public:

	SideBar(int _life = 0, int _left = 0, int _top = 0, int _width = 27*FONT_WIDTH, 
	int _height = 9*FONT_HEIGHT)
		: life(_life),
		left(_left),
		top(_top),
		width(_width),
		height(_height)
	{
		score = 0;
		numOfLetters = 0;
		numOfVictories = 0;
	}

	void setLeft(int);
	int getLeft() const;

	void setTop(int);
	int getTop() const;

	void setWidth(int);
	int getWidth() const;

	void setHeight(int);
	int getHeight() const;

	void draw();
};