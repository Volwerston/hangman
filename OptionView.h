#pragma once

#include <vector>

#include "View.h"
#include "StartView.h"

class OptionView : public View
{
	vector<MenuItem> menu;
	int menuCurrent;

	void drawMenu();
	void changeMenuItems();
public:
	OptionView();

	View* handle();

	void draw();

	~OptionView() {};
};