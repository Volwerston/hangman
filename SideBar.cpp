#pragma once

#include <Windows.h>

#include "SideBar.h"
#include "ConsoleProperties.h"

using namespace std;

void SideBar::draw()
{
	setCursorAt(left/FONT_WIDTH, top/FONT_HEIGHT);

	drawBackground(left, top, width, height, RGB(0,0,100));

	setCursorAt(left / FONT_WIDTH + 1, top / FONT_HEIGHT + 1);
	if (life >= 0)
	{
		if (options.getLanguage() == Language::ENGLISH)
		{
			stats.print("Life: " + string(25 - 6 - toString(life).size(), ' ') + toString(life));
		}
		else
		{
			stats.print("Життя: " + string(25 - 7 - toString(life).size(), ' ') + toString(life));
		}
	}
	else
	{
		if (options.getLanguage() == Language::ENGLISH)
		{
			stats.print("Life: " + string(25 - 6 - toString("0").size(), ' ') + toString("0"));
		}
		else
		{
			stats.print("Життя: " + string(25 - 7 - toString("0").size(), ' ') + toString("0"));
		}
	}
	setCursorAt(left/FONT_WIDTH + 1, top/FONT_HEIGHT + 3);

	if (options.getLanguage() == Language::ENGLISH)
	{
		stats.print("Score: " + string(25 - 7 - toString(score).size(), ' ') + toString(score));
		setCursorAt(left / FONT_WIDTH + 1, top / FONT_HEIGHT + 5);
		stats.print("Guessed letters: " + string(25 - 17 - toString(numOfLetters).size(), ' ') + toString(numOfLetters));
	}
	else
	{
		stats.print("Рахунок: " + string(25 - 9 - toString(score).size(), ' ') + toString(score));
		setCursorAt(left / FONT_WIDTH + 1, top / FONT_HEIGHT + 5);
		stats.print("Вгадані літери: " + string(25 - 16 - toString(numOfLetters).size(), ' ') + toString(numOfLetters));
	}
}

void SideBar::setLeft(int leftCoord)
{
	left = leftCoord;
}

void SideBar::setTop(int topCoord)
{
	top = topCoord;
}

void SideBar::setWidth(int widthCoord)
{
	width = widthCoord;
}

void SideBar::setHeight(int heightCoord)
{
	height = heightCoord;
}

int SideBar::getLeft() const
{
	return left;
}

int SideBar::getTop() const
{
	return top;
}

int SideBar::getHeight() const
{
	return height;
}

int SideBar::getWidth() const
{
	return width;
}