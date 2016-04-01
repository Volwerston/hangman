#pragma once

#include "View.h"
#include "StartView.h"

class OptionView : public View
{
	MenuItem** menu;
	int menuCurrent;
public:
	OptionView();

	View* handle();

	void draw();

	~OptionView();
};