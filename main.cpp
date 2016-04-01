#include <iostream>
#include <conio.h>

#include "View.h"
#include "StartView.h"
#include "ConsoleProperties.h"
#include "SideBar.h"
#include "FieldView.h";
#include "Options.h"
#include "OptionView.h"

using namespace std;

int main()
{
	setConsoleProperties();

	//StartView start;

	//FieldView start;

	//start.draw();

	OptionView start;
	start.draw();

	_getch();
	return 0;
}