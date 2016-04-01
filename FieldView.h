#pragma once 

#include "View.h"
#include "SideBar.h"

class FieldView : public View
{
	SideBar info;

	struct Letter
	{
		char letter;
		bool active;

		int left;
		int top;
		int width;
		int height;

		Letter(char = ' ', bool = false, int = 0, int = 0, int = 0, int = 0);

		void draw();
	};

	Letter* word;
	Letter **usedLetter;
	int sizeOfWord;
	int numOfUsed;
public:
	FieldView()
		: info(SideBar()),
		numOfUsed(0)
	{
		sizeOfWord = 8;
		word = new Letter[sizeOfWord];

		for (size_t i = 0; i < sizeOfWord; ++i)
		{
			word[i].left = CONSOLE_WIDTH*FONT_WIDTH / 10 + i*(CONSOLE_WIDTH*FONT_WIDTH / 10);
			word[i].top = CONSOLE_HEIGHT*FONT_HEIGHT / 2;
			word[i].width = 50;
			word[i].height = 50;
		}

		usedLetter = new Letter*[4];
		for (size_t i = 0; i < 4; ++i)
		{
			usedLetter[i] = new Letter[10];
		}

		int current = 0;

		while (current < 40)
		{
			usedLetter[current / 10][current % 10].width = 25;
			usedLetter[current / 10][current % 10].height = 25;
			usedLetter[current / 10][current % 10].left = CONSOLE_WIDTH*FONT_WIDTH / 10 
				               + (CONSOLE_WIDTH*FONT_WIDTH / 15)*(current % 10);
			usedLetter[current / 10][current % 10].top = (2 * CONSOLE_HEIGHT*FONT_HEIGHT) / 3 + FONT_HEIGHT + (current / 10) * 30;

			++current;
		}

		word[4].active = true;
		word[4].letter = 'A';

	}

	void draw();

	void addUsed(char);

	View* handle() { return nullptr; };

	~FieldView()
	{
		delete[] word;

		for (size_t i = 0; i < 4; ++i)
		{
			delete[] usedLetter[i];
		}

		delete[] usedLetter;
	}
};