#ifndef INPUTPROCESS
#define INPUTPROCESS
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "map"
#include "list"
#include "word.h"
#include "exceptionPackage.h"
#endif

using namespace std;

extern char paramHead;
extern char paramTail;
extern map<char, bool> params;
void testInputProcess(char* words[], int len, char portHead, char portTail,
    bool enable_loop, char functionType)throw(ParamHTException);
void initAlphabet();

void inputProcess(int argc, char* argv[]);