﻿#include "Core.h"
//
// Created by lenovo on 2022/3/29.
//

using namespace std;

extern char paramHead;
extern char paramTail;

/*class Core{
public:
    //words为输入的单词列表，len为单词列表的长度，result存放单词链，函数返回值为单词链长度。
    //1.单词数量最多的最长单词链：
    //head和tail分别为单词链首字母与尾字母约束（如果传入0，表示没有约束），
    //当enable_loop为true时表示允许输入单词文本中隐含“单词环”
    int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
    //2.函数返回所有符合定义的单词链，函数返回值为单词链的总数
    int gen_chains_all(char* words[], int len, char* result[]);
    //3.函数返回首字母不同的，单词数最多的单词链，函数返回值为单词链的长度
    int gen_chain_word_unique(char* words[], int len, char* result[]);
    //4.计算最多字母数量的最长单词链
    int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
};*/
//void testInputProcess(char *words[], int len,char head,char tail,bool enable_loop, char functionType){


int Core::gen_chain_word(char** words, int len, char** result, char head, char tail, bool enable_loop) {
    try {
        
        testInputProcess(words, len, head, tail, enable_loop, 'w');
        if (CycleDetection()) {
            if (enable_loop) {
                outputWordList = FunctionW_R();
            }
            else {
                throw LoopException();
            }
        }
        else {
            //outputWordList = FunctionW_noR();
            FunctionWC_noR();
        }
        //W最长单词链字母数量
        int resultSize = resultValue(result);
        return resultSize;
    }
    catch (LoopException& e) {
        cout << e.what() << std::endl;
        result[0] = (char*)e.what();
        return -1;
    }
    catch (ResultContainException& e) {
        cout << e.what() << std::endl;
        return e.length;
    }
    catch (ParamHTException& e) {
        cout << e.what() << std::endl;
        result[0] = (char*)e.what();
        return -2;
    }
}

int Core::gen_chains_all(char** words, int len, char** result) {
    try {
         
        testInputProcess(words, len, 0, 0, false, 'n');
        if (CycleDetection()) {
            throw LoopException();
        }
        FunctionN_noR();
        //单词链数量
        int resultSize = resultValue(result);
        return resultSize;
    }
    catch (LoopException& e) {
        cout << e.what() << std::endl;
        return -1;
    }
    catch (ResultContainException& e) {
        cout << e.what() << std::endl;
        return e.length;
    }
}

int Core::gen_chain_word_unique(char** words, int len, char** result) {
    try { 
        testInputProcess(words, len, 0, 0, false, 'm');
        if (CycleDetection()) {
            throw LoopException();
        }
        
        FunctionM();
        //M最长链的单词数量
        int resultSize = resultValue(result);
        return resultSize;
    }
    catch (LoopException& e) {
        cout << e.what() << std::endl;
        return -1;
    }
    catch (ResultContainException& e) {
        cout << e.what() << std::endl;
        return e.length;
    }

}

int Core::gen_chain_char(char** words, int len, char** result, char head, char tail, bool enable_loop) {
    try { 
        testInputProcess(words, len, head, tail, enable_loop, 'c');
        if (CycleDetection()) {
            if (enable_loop) {
                outputWordList = FunctionC_R();
            }
            else {
                throw LoopException();
            }
        }
        else {
            //outputWordList = FunctionW_noR();
            FunctionWC_noR();
        }
        //c最长单词链字母数量
        int resultSize = resultValue(result);
        return resultSize;
    }
    catch (LoopException& e) {
        cout << e.what() << std::endl;
        result[0] = (char*)e.what();
        return -1;
    }
    catch (ResultContainException& e) {
        cout << e.what() << std::endl;
        return e.length;
    }
    catch (ParamHTException& e) {
        cout << e.what() << std::endl;
        result[0] = (char*)e.what();
        return -2;
    }
}


