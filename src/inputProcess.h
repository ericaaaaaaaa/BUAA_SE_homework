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
void inputProcess(int argc, char *argv[]);
void testInputProcess(char *words[], int len,char portHead,char portTail,
                      bool enable_loop, char functionType);

extern char paramHead;
extern char paramTail;
extern map<char, bool> params;