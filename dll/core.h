#pragma once
#include "word.h"
#include "inputProcess.h"
#include "exceptionPackage.h"

int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
//2.函数返回所有符合定义的单词链，函数返回值为单词链的总数
int gen_chains_all(char* words[], int len, char* result[]);
//3.函数返回首字母不同的，单词数最多的单词链，函数返回值为单词链的长度
int gen_chain_word_unique(char* words[], int len, char* result[]);
//4.计算最多字母数量的最长单词链
int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);



