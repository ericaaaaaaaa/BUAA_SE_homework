#include "pch.h"
#include "Core.h"
//
// Created by lenovo on 2022/3/29.
//

#include "Core.h"

using namespace std;

extern char paramHead;
extern char paramTail;

/*class Core{
public:
    //wordsΪ����ĵ����б�lenΪ�����б�ĳ��ȣ�result��ŵ���������������ֵΪ���������ȡ�
    //1.���������������������
    //head��tail�ֱ�Ϊ����������ĸ��β��ĸԼ�����������0����ʾû��Լ������
    //��enable_loopΪtrueʱ��ʾ�������뵥���ı������������ʻ���
    int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
    //2.�����������з��϶���ĵ���������������ֵΪ������������
    int gen_chains_all(char* words[], int len, char* result[]);
    //3.������������ĸ��ͬ�ģ����������ĵ���������������ֵΪ�������ĳ���
    int gen_chain_word_unique(char* words[], int len, char* result[]);
    //4.���������ĸ�������������
    int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
};*/
//void testInputProcess(char *words[], int len,char head,char tail,bool enable_loop, char functionType){

int gen_chain_word(char** words, int len, char** result, char head, char tail, bool enable_loop) {
    try {
        int resultSize;
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
            outputWordList = FunctionW_noR();
            //FunctionWC_noR();
        }
        //W���������ĸ����
        resultSize = (int)outputWordList.size();
        if (resultSize > RESULT_CONTAIN) {
            throw ResultContainException(resultSize);
        }
        resultValue(result);
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

int gen_chains_all(char** words, int len, char** result) {
    try {
        testInputProcess(words, len, 0, 0, false, 'n');
        if (CycleDetection()) {
            throw LoopException();
        }
        FunctionN_noR();
        //����������
        int resultSize = (int)outputWordList.size();
        if (resultSize > RESULT_CONTAIN) {
            throw ResultContainException(resultSize);
        }
        resultValue(result);
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
        //M����ĵ�������
        int resultSize = (int)outputWordList.size();
        if (resultSize > RESULT_CONTAIN) {
            throw ResultContainException(resultSize);
        }
        resultValue(result);
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
        //c���������ĸ����
        int resultSize = (int)outputWordList.size();
        if (resultSize > RESULT_CONTAIN) {
            throw ResultContainException(resultSize);
        }
        resultValue(result);
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


