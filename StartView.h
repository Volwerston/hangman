#pragma once

#include <string>
#include "View.h"
#include "ConsoleProperties.h"

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
		if (options.getLanguage() == Language::ENGLISH)
		{
			menu[0] = MenuItem("START GAME");
			menu[1] = MenuItem("OPTIONS");
			menu[2] = MenuItem("HIGH SCORES");
			menu[3] = MenuItem("EXIT");
		}
		else
		{
			menu[0] = MenuItem("ÏÎ×ÀÒÈ ÃÐÓ");
			menu[1] = MenuItem("ÎÏÖ²¯");
			menu[2] = MenuItem("ÐÅÊÎÐÄÈ");
			menu[3] = MenuItem("ÂÈÕ²Ä");
		}
		menu[0].chosen = true;
	}

	void draw();
	View* handle();

	~StartView()
	{
	}
};
