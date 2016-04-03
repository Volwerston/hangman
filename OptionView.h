#pragma once

#include <vector>

#include "View.h"
#include "StartView.h"

class OptionView : public View
{
	vector<MenuItem> menu;
	int menuCurrent;

	void drawMenu();
public:
	OptionView();

	View* handle();

	void draw();

	~OptionView() {};
};