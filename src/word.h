#ifndef WORD
#define WORD
#pragma once
#include <string>
#include "map"
#include "list"
#endif // WORD

using namespace std;
//struct word {
//	int wordLength;
//	string wordContent;
//};
class Word {
public:
    int wordLength;
    string wordContent;

    Word(int wl, string wc) : wordLength(wl), wordContent(std::move(wc)) {}
};

class WordList {
public:
    list<Word *> listOfWord;
    int listLength;
};

//struct wordList{
//	list<struct word> listOfWord;
//	int listLength;
//};
map<string, bool> dirty;
//struct wordList* alphabet[26][26];
WordList* alphabet[26][26];