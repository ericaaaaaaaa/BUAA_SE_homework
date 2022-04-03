#include "pch.h"
#include "core.h"
//
// Created by lenovo on 2022/3/29.
//

using namespace std;

extern char paramHead;
extern char paramTail;
 
int gen_chain_word(char** words, int len, char** result, char head, char tail, bool enable_loop) {
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

int gen_chains_all(char** words, int len, char** result) {
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

int gen_chain_word_unique(char** words, int len, char** result) {
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

int gen_chain_char(char** words, int len, char** result, char head, char tail, bool enable_loop) {
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


