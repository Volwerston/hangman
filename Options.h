#pragma once

#include <string>

using namespace std;

enum class Difficulty
{
	EASY,
	MIDDLE,
	HARD
};

enum class Language
{
	ENGLISH,
	UKRAINIAN
};

class Options
{
	struct Word
	{
		string data;
		bool chosen;

		Word(string = "", bool = false);

		string getText() const;

		friend istream& operator>>(istream& in, Word& word)
		{
			in >> word.data;
			return in;
		}

		friend ostream& operator<<(ostream& out, const Word& word)
		{
			out << word.data << endl;
			return out;
		}
	};

	Word* dictionary;
	Language language;
	string langTemplate;
	string filePath;
	Difficulty level;
	int numOfWords;

public:
	Options(Language = Language::ENGLISH, Difficulty = Difficulty::EASY);

	void loadDictionary();
	void setFilePath(string);
	void setLanguage(Language);
	string getFilePath() const;
	Language getLanguage() const;

	~Options();
};