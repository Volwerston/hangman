#include <conio.h>

#include "OptionView.h"
#include "ConsoleProperties.h"

using namespace std;

OptionView::OptionView()
	:menuCurrent(0)
{
	menu = new MenuItem*[3];

	menu[0] = new MenuItem[2];
	menu[0][0].text = "English";
	menu[0][1].text = "Ukrainian";
	menu[1] = new MenuItem[3];
	menu[1][0].text = "Easy";
	menu[1][1].text = "Medium";
	menu[1][2].text = "Hard";
	menu[2] = new MenuItem[2]; 
	menu[2][0].text = "Back to menu";
	menu[2][1].text = "New game";
}

View* OptionView::handle() 
{ 
	bool finish = false;
	int c;

	while (!finish)
	{
		c = _getch();
		switch (c)
		{
		case 224:
			switch (_getch())
			{
			case 72: // down 

				break;
			case 80: // up

				break;
			case 75: // left

				break;
			case 77: //right

				break;
			}
			break;
		case VK_RETURN:
		
			break;
		}
	}

	return nullptr;
}

void OptionView::draw()
{
	clear();

	drawBackground(0, 0, CONSOLE_WIDTH*FONT_WIDTH, CONSOLE_HEIGHT*FONT_HEIGHT, RGB(0, 100, 200));

	printAtCenter("Language:", headline);

	setCursorAt(CONSOLE_WIDTH/5, 2);
	menuActive.print(menu[0][0].text);

	setCursorAt(3*CONSOLE_WIDTH/5, 2);
	menuPassive.print(menu[0][1].text);

	setCursorAt(CONSOLE_WIDTH / 2, CONSOLE_HEIGHT / 3);
	printAtCenter("Difficulty:", headline);
	
	setCursorAt(cursor.X, cursor.Y + 2);

	for (size_t i = 0; i < 3; ++i)
	{
		setCursorAt(CONSOLE_WIDTH / 5 + (CONSOLE_WIDTH / 4)*i, cursor.Y);
		menuPassive.print(menu[1][i].text);
	}

	setCursorAt(CONSOLE_WIDTH/6, CONSOLE_HEIGHT - 2);
	menuPassive.print(menu[2][0].text);

	setCursorAt(4 * CONSOLE_WIDTH / 6, CONSOLE_HEIGHT - 2);
	menuPassive.print(menu[2][1].text);
}

OptionView::~OptionView()
{
	for (size_t i = 0; i < 3; ++i) delete[] menu[i];
	delete[] menu;
}
