#pragma once

#include <string>
#include <vector>

using namespace std;

enum class Difficulty
{
	EASY = 1,
	MIDDLE,
	HARD
};

enum class Language
{
	ENGLISH = 1,
	UKRAINIAN
};

struct Player
{
	string nickname;
	int score;
	int numLetters;
	Difficulty topLevel;
	Language langUsed;

	Player(int = 0, int = 0, Language = Language::ENGLISH, Difficulty = Difficulty::EASY,
		string = " ");

	friend ostream& operator<<(ostream&, const Player&);

	friend istream& operator>>(istream&, Player&);
};

class Options
{
	friend class FieldView;
	friend class SideBar;
	vector<Player> records;

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

	bool easyUsed;
	bool middleUsed;
	bool hardUsed;

	Word* dictionary;
	Language language;
	string langTemplate;
	string filePath;
	Difficulty level;
	int numOfWords;
public:
	Options(Language = Language::ENGLISH, Difficulty = Difficulty::EASY);

	void loadDictionary();
	void setFilePath();
	void setLanguage(Language);
	void setDifficulty(Difficulty);
	void addPlayer(Player);

	vector<Player> getRecords() const;

	string getFilePath() const;
	Language getLanguage() const;

	Difficulty getLevel() const
	{
		return level;
	}

	bool allChosen();
	string chooseWord();

	~Options();
};