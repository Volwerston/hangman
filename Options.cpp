#pragma once

#include <iostream>
#include <fstream>

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
	filePath(""),
	numOfWords(20)
{
	dictionary = new Word[20];
	if (language == Language::ENGLISH)
	{
		langTemplate = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	}
	else
	{
		langTemplate = "¿¡¬√ƒ≈™∆«»≤Ø… ÀÃÕŒœ–—“”‘’÷◊ÿŸ‹ﬁﬂ";
	}
}

Options::~Options()
{
	delete[] dictionary;
}

void Options::setLanguage(Language _lan)
{
	language = _lan;
}

void Options::setFilePath(string path)
{
	filePath = path;
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
		}
	}
}