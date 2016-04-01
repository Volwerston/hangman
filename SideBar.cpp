#pragma once

#include <Windows.h>

#include "SideBar.h"
#include "ConsoleProperties.h"

using namespace std;

SideBar::SideBar(int _left, int _top, int _width, int _height)
	: left(_left),
	top(_top),
	width(_width),
	height(_height)
{
	score = 0;
	numOfLetters = 0;
	numOfVictories = 0;
}

void SideBar::draw()
{
	setCursorAt(left/FONT_WIDTH, top/FONT_HEIGHT);

	drawBackground(left, top, width, height, RGB(0,0,100));

	setCursorAt(left/FONT_WIDTH + 1, top/FONT_HEIGHT + 1);
	stats.print("Score: " + string(25 - 7 - toString(score).size(), ' ') + toString(score));
	setCursorAt(left/FONT_WIDTH + 1, top/FONT_HEIGHT + 3);
	stats.print("Victories: " + string(25 - 11 - toString(numOfVictories).size(), ' ') + toString(numOfVictories));
	setCursorAt(left/FONT_WIDTH + 1, top/FONT_HEIGHT + 5);
	stats.print("Guessed letters: " + string(25 - 17 - toString(numOfLetters).size(), ' ') + toString(numOfLetters));
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