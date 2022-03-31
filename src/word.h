#ifndef WORD
#define WORD
#pragma once

#include <string>
#include "map"
#include "list"
#include "inputProcess.h"
#include <iostream>

#endif // WORD

using namespace std;

extern list<string> outputWordList;
extern int degree[26][2]; // 0->in, 1->out

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

void initGraph();

void resultValue(char **result);

/*------Cycle---------*/
//bool CycleVisitDetection(int i, int *, int *);

bool CycleDetection();

/*------ N ---------*/
//list<string> DFS(int row, int column);

void FunctionN_noR();


/*---------W---------*/
//list<string> findGreatestWDFS(int row, int column);
//list<string> findGreatestWDFS_R(int row, int column);
//list<string> findGreatestWDFSReverse(int row, int column);
//list<string> findGreatestWDFSReverse_R(int row, int column);
//list<string> findGreatestWDFS(int row, int column, char t);
//list<string> findGreatestWDFS_R(int row, int column, char t);
//
//list<string> findGreatestCDFS(int row, int column);
//list<string> findGreatestCDFS_R(int row, int column);
//list<string> findGreatestCDFSReverse(int row, int column);
//list<string> findGreatestCDFSReverse_R(int row, int column);
//list<string> findGreatestCDFS(int row, int column, char t);
//list<string> findGreatestCDFS_R(int row, int column, char t);

list<string> FunctionW_noR();

list<string> FunctionW_R();

list<string> FunctionC_noR();

list<string> FunctionC_R();


/*------WCM noR------*/
//void findGreatestDj(int i, int *pred, int *predii, int *rec, int *maxDist);
//bool getDJlist(int rec, int *pred, int *predii, int i);

void FunctionWC_noR();

void FunctionM0();
void FunctionM();
//-------------------



