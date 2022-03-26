#include "iterator"
#include "word.h"
#include <iostream>

bool reset;
list<string> outputWordList;

void resetDirty() {
    for (auto iter = dirty.begin(); iter != dirty.end(); iter++) {
        iter->second = false;
    }
}

void resetArray(int list[], int length) {
    for (int i = 0; i < length; i++)list[i] = 0;
}

bool CycleVisitDetection(int i, int *cycleFind, int *allFind) {
    //cout << "find: "<<char('a'+i) << endl;
    cycleFind[i] = 1;
    allFind[i] = 1;
    int j;
    for (j = 0; j < 26; j++) {
        if (cycleFind[j] && alphabet[i][j]->listLength) {
            return true;
        }
    }
    for (j = 0; j < 26; j++) {
        if (cycleFind[j] || 0 == alphabet[i][j]->listLength)continue;
        cycleFind[j] = 1;
        outputWordList.push_back((*alphabet[i][j]->listOfWord.begin())->wordContent);
        //cout << "-next: "<<char('a'+j) << endl;
        if (CycleVisitDetection(j, cycleFind, allFind)) {
            return true;
        }
        outputWordList.pop_back();
    }
    cycleFind[i] = 0;
    return false;
}

bool CycleDetection() {
    int i;
    int cycleFind[26] = {0}, allFind[26] = {0};
    for (i = 0; i < 26; i++) {
        int countI = 0;
        for(int j =0;j<26;j++)countI+=alphabet[i][j]->listLength;
        if (!allFind[i] && countI != 0) {
            if (CycleVisitDetection(i, cycleFind, allFind)) {
                return true;
            }
            resetArray(cycleFind,26);
        }
    }
}


void DFS() {
    //���������������ÿ����ͬ�ġ�ͷβ����ͷ�ĵ�����,����outputWordList

}

void FunctionN_noR() {
    //���DFS��outputWordList��ȡ���е�����
}

void FunctionWC_noR(char head, char tail) {
    //�ҵ����Ϊ0�ġ�ͷβ����Ȼ�������Щ�㣨��ͷβ����ͬ����Ϊ��ͷֻ��һ��)����DijkstraѰ�����
    //W����Ϊ�����б��ȣ�C����Ϊ������ĸ�ܳ�
}


//  aaa ab�� m��Ч
//�����N_noR��ͬ

void FunctionM() {
    //�ҵ����Ϊ0�ġ�ͷβ����Ȼ�������Щ�㣨��ͷβ����ͬ����Ϊ��ͷֻ��һ��)����DijkstraѰ�����
    //����Ϊ�����б���
}

#include "inputProcess.h"

//����ѭ����⣺

int main(int argc, char* argv[]) {
    try {
        inputProcess(argc,argv);
        cout << "cycle detection " << CycleDetection() << endl;
        for(auto iter = outputWordList.begin();iter != outputWordList.end(); iter++){
            cout << (*iter) << " -> ";
        }
    } catch (const char* msg) {
        cout << msg << endl;
    }
    return 0;
}

//���Բ������벿�֣�
/*
int main(int argc, char *argv[]) {
    try {
        initAlphabet();
        analyzeParam(argc, argv);
        cout << "FileName: " << fileName << endl;
        cout << "Parameters:\t" << "-n: " << params['n'] <<
             "\t-w: " << params['w'] <<
             "\t-c: " << params['c'] <<
             "\t-m: " << params['m'] <<
             "\t-h: " << params['h'] <<
             "\t-t: " << params['t'] <<
             "\t-r: " << params['r'] << endl;
        readWordFromFile();
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                for (auto iter = alphabet[i][j]->listOfWord.begin();
                     iter != alphabet[i][j]->listOfWord.end(); ++iter) {
                    cout << "alphabet[" << char('a' + i) << "][" << char('a' + j) << "]: " << (*iter)->wordContent
                         << "\tLength: " << (*iter)->wordLength << endl;
                }
            }
        }
        cout << "======THE END=======" << endl;
    } catch (const char *msg) {
        cout << msg << endl;
    }
}*/