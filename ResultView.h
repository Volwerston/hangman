#pragma once

#include "View.h"
#include "Options.h"

class ResultView : public View
{
	Player p;
public:

	ResultView(Player = Player());

	void draw();

	View* handle();
};