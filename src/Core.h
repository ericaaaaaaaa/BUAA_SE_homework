#ifndef CLIONWORDLIST_CORE_H
#define CLIONWORDLIST_CORE_H
#include "word.h"
#include "inputProcess.h"
#include "exceptionPackage.h"
#endif //CLIONWORDLIST_CORE_H

class Core {

public:
    //words为输入的单词列表，len为单词列表的长度，result存放单词链，函数返回值为单词链长度。
    //1.单词数量最多的最长单词链：
    //head和tail分别为单词链首字母与尾字母约束（如果传入0，表示没有约束），
    //当enable_loop为true时表示允许输入单词文本中隐含“单词环”
    static int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
    //2.函数返回所有符合定义的单词链，函数返回值为单词链的总数
    static int gen_chains_all(char* words[], int len, char* result[]);
    //3.函数返回首字母不同的，单词数最多的单词链，函数返回值为单词链的长度
    static int gen_chain_word_unique(char* words[], int len, char* result[]);
    //4.计算最多字母数量的最长单词链
    static int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
};
