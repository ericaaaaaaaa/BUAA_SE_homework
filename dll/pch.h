// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"

#endif //PCH_H

    //words为输入的单词列表，len为单词列表的长度，result存放单词链，函数返回值为单词链长度。
    //1.单词数量最多的最长单词链：
    //head和tail分别为单词链首字母与尾字母约束（如果传入0，表示没有约束），
    //当enable_loop为true时表示允许输入单词文本中隐含“单词环”
extern "C" _declspec(dllexport)int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
//2.函数返回所有符合定义的单词链，函数返回值为单词链的总数
extern "C" _declspec(dllexport)int gen_chains_all(char* words[], int len, char* result[]);
//3.函数返回首字母不同的，单词数最多的单词链，函数返回值为单词链的长度
extern "C" _declspec(dllexport)int gen_chain_word_unique(char* words[], int len, char* result[]);
//4.计算最多字母数量的最长单词链
extern "C" _declspec(dllexport)int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
