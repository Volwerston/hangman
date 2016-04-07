#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "Options.h"

using namespace std;

Options::Word::Word(string _dat, bool _ch)
	: data(_dat),
	chosen(_ch)
{
}

string Options::Word::getText() const 
{ 
	return data; 
}

Options::Options(Language _lan, Difficulty dif)
	: language(_lan),
	level(dif),
	filePath("Engl_easy.txt"),
	numOfWords(20),
	easyUsed(false),
	middleUsed(false),
	hardUsed(false),
	langTemplate("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
{
	dictionary = new Word[20];
}

void Options::setLanguage(Language _lan)
{
	language = _lan;

	if (language == Language::ENGLISH)
	{
		langTemplate = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	}
	else
	{
		langTemplate = "¿¡¬√ƒ≈™∆«»≤Ø… ÀÃÕŒœ–—“”‘’÷◊ÿŸ‹ﬁﬂ";
	}
}


void Options::setFilePath()
{
	if (language == Language::ENGLISH)
	{
		if (level == Difficulty::EASY)
		{
			filePath = "Engl_easy.txt";
		}
		else if (level == Difficulty::MIDDLE)
		{
			filePath = "Engl_middle.txt";
		}
		else
		{
			filePath = "Engl_hard.txt";
		}
	}
	else
	{
		if (level == Difficulty::EASY)
		{
			filePath = "Ua_easy.txt";
		}
		else if (level == Difficulty::MIDDLE)
		{
			filePath = "Ua_middle.txt";
		}
		else
		{
			filePath = "Ua_hard.txt";
		}
	}
}

void Options::setDifficulty(Difficulty dif)
{
	level = dif;
}

Language Options::getLanguage() const
{
	return language;
}

string Options::getFilePath() const
{
	return filePath;
}

void Options::loadDictionary()
{

	setFilePath();

	ifstream in(filePath);

	if (!in)
	{
		cout << "Dictionary file couln't be opened" << endl;
		system("pause");
		exit(1);
	}
	else
	{
		for (size_t i = 0; i < numOfWords; ++i)
		{
			in >> dictionary[i];
			dictionary[i].chosen = false;
		}

		for (size_t i = 1; i < numOfWords; ++i)
		{
			dictionary[i].chosen = true;
		}
	}
}

string Options::chooseWord()
{
	string toReturn = "";

	if (!allChosen())
	{
		srand(time(0));

		bool chosen = false;

		int num = 0;

		while (!chosen)
		{
			num = rand() % 20;

			if (!dictionary[num].chosen)
			{
				dictionary[num].chosen = true;
				toReturn = dictionary[num].data;
				break;
			}
		}
	}
	else
	{
		if (level == Difficulty::EASY)
		{
			if (!middleUsed)
			{
				level = Difficulty::MIDDLE;
				loadDictionary();
				toReturn = dictionary[0].data;
				dictionary[0].chosen = true;
			}
		}
		else if (level == Difficulty::MIDDLE)
		{
			if (!hardUsed)
			{
				level = Difficulty::HARD;
				loadDictionary();
				toReturn = dictionary[0].data;
				dictionary[0].chosen = true;
			}
		}
		else
		{
			if (!easyUsed)
			{
				level = Difficulty::EASY;
				loadDictionary();
				toReturn = dictionary[0].data;
				dictionary[0].chosen = true;
			}
		}
	}

	return toReturn;
}

bool Options::allChosen()
{
	bool allUsed = true;

	for (size_t i = 0; i < 20; ++i)
	{
		if (!dictionary[i].chosen)
		{
			allUsed = false;
			break;
		}
	}

	if (allUsed == true)
	{
		if (level == Difficulty::EASY)
		{
			easyUsed = true;
		}
		else if (level == Difficulty::MIDDLE)
		{
			middleUsed = true;
		}
		else
		{
			hardUsed = true;
		}
	}

	return allUsed;
}

Options::~Options()
{
	delete[] dictionary;
}


