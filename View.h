#pragma once

#include <Windows.h>

using namespace std;

class View
{
public:
	virtual void draw() = 0;
	virtual View* handle() = 0;

	void drawBackground(int, int, int, int, COLORREF);

	void clear();
	virtual ~View() {};
};