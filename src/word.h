#pragma once
#include <string>
#include "map"
using namespace std;
struct word {
	int wordLength;
	string wordContent;
	struct word* next;
	struct word* prev;
};
map<string, bool> dirty;
struct word* alphabet[26][26];
