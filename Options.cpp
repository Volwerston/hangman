#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "Options.h"

using namespace std;

void sortPlayers(vector<Player>& vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		for (size_t j = 0; j < vec.size() - (i + 1); ++j)
		{
			if ((vec[j].score + 0.05*double(vec[j].numLetters)) <
				(vec[j + 1].score + 0.05*double(vec[j + 1].numLetters)))
			{
				Player buffer = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = buffer;
			}
		}
	}
}

Options::Word::Word(string _dat, bool _ch)
	: data(_dat),
	chosen(_ch)
{
}

string Options::Word::getText() const 
{ 
	return data; 
}

Player::Player(int _s, int let, Language _lang, Difficulty _dif, string _n)
	: nickname(_n),
	score(_s),
	numLetters(let),
	topLevel(_dif),
	langUsed(_lang)
{
}

ostream& operator<<(ostream& out, const Player& p)
{
	out << p.nickname << " " << p.score << " " << p.numLetters << " ";

	if (p.langUsed == Language::ENGLISH)
	{
		out << " English ";
	}
	else
	{
		out << " Ukrainian ";
	}

	if (p.topLevel == Difficulty::EASY)
	{
		out << " easy ";
	}
	else if (p.topLevel == Difficulty::MIDDLE)
	{
		out << " middle ";
	}
	else
	{
		out << " hard ";
	}

	return out;
}

istream& operator>>(istream& in, Player& p)
{
	in >> p.nickname >> p.score >> p.numLetters;

	string level;
	string language;

	in >> language >> level;

	if (language == "English")
	{
		p.langUsed = Language::ENGLISH;
	}
	else
	{
		p.langUsed = Language::UKRAINIAN;
	}

	if (level == "easy")
	{
		p.topLevel = Difficulty::EASY;
	}
	else if (level == "middle")
	{
		p.topLevel = Difficulty::MIDDLE;
	}
	else
	{
		p.topLevel = Difficulty::HARD;
	}

	return in;
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

	ifstream in("Records.txt");
	Player buf;

	while (in >> buf)
	{
		records.push_back(buf);
	}

	in.close();
}

vector<Player> Options::getRecords() const
{
	return records;
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

void Options::addPlayer(Player pl)
{
	if (records.empty())
	{
		records.push_back(pl);
	}
	else
	{
		bool playerFound = false;

		for (size_t i = 0; i < records.size(); ++i)
		{
			if (records[i].nickname == pl.nickname)
			{
				playerFound = true;
				records[i] = pl;
				break;
			}
		}

		if (playerFound)
		{
			sortPlayers(records);
		}
		else
		{
			records.push_back(pl);
			sortPlayers(records);
		}
		
	}

	ofstream out("Records.txt");

	for (size_t i = 0; i < records.size(); ++i)
	{
		out << records[i] << endl;
	}
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


