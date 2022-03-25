#pragma once
#include <string>
#include "map"
#include "list"
using namespace std;
struct word {
	int wordLength;
	string wordContent;
};
struct wordList{
	list<struct word> listOfWord;
	int listLength;
};
map<string, bool> dirty;
struct wordList* alphabet[26][26];
