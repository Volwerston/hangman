#pragma once

#include "View.h"
#include "ConsoleProperties.h"

class SideBar: public View
{
	friend class FieldView;

	int score;
	int numOfVictories;
	int numOfLetters;
	int width;
	int height;
	int left;
	int top;

	View* handle() { return nullptr; }
public:

	SideBar(int = 0, int = 0, int = 27*FONT_WIDTH, int = 7*FONT_HEIGHT);

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