#pragma once
#ifndef INPUTPROCESS
#define INPUTPROCESS
#pragma once
#include <iostream>
#include <fstream>
#include "regex"
#include <string>
#include "map"
#include "list"
#include "word.h"
#include "algorithm"
#include "exceptionPackage.h"
#endif

using namespace std;

extern char paramHead;
extern char paramTail;
extern map<char, bool> params;
void testInputProcess(char* words[], int len, char portHead, char portTail,
    bool enable_loop, char functionType);
void initAlphabet();
