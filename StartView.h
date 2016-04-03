#pragma once

#include <string>
#include "View.h"

using namespace std;


struct MenuItem
{
	string text;
	bool chosen;
	int x;
	int y;

	MenuItem(string _text = "", int _x = 0, int _y = 0) :
		text(_text),
		chosen(false),
		x(_x),
		y(_y)
	{
	}
};

class StartView : public View
{

	int menuCurrent;

	enum class Action
	{
		START,
		OPTIONS,
		HIGH_SCORES,
		EXIT
	};


	//Options selectedOption;
	MenuItem menu[4];

	void drawMenu();

public:
	StartView() 
		: menuCurrent(0)
	{
		menu[0] = MenuItem("START GAME");
		menu[1] = MenuItem("OPTIONS");
		menu[2] = MenuItem("HIGH SCORES");
		menu[3] = MenuItem("EXIT");
		menu[0].chosen = true;
	}

	void draw();
	View* handle();

	~StartView()
	{
	}
};
