#include "iterator"
#include "word.h"
#include "inputProcess.h"
#include <iostream>

bool reset;
list<string> outputWordList;

void resetDirty() {
    for (auto iter = dirty.begin(); iter != dirty.end(); iter++) {
        iter->second = false;
    }
}

//以i结尾或开头的数量
int countHT(int i, bool findHead, bool ii) {
    int countI = 0;
    if (findHead)
        for (int j = 0; j < 26; j++) {
            if (!ii || i != j) {
                countI += alphabet[i][j]->listLength;
            }
        }
    else
        for (int j = 0; j < 26; j++) {
            if (!ii || i != j) {
                countI += alphabet[j][i]->listLength;
            }
        }
    return countI;
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
            if (i == j && alphabet[i][j]->listLength == 1)continue;
            return true;
        }
    }
    for (j = 0; j < 26; j++) {
        if (cycleFind[j] || 0 == alphabet[i][j]->listLength)continue;
//        cycleFind[j] = 1;
        outputWordList.push_back((*alphabet[i][j]->listOfWord.begin())->wordContent);
        //cout << "-next: "<<char('a'+j) << endl;
        if (CycleVisitDetection(j, cycleFind, allFind)) {
            return true;
        }
        outputWordList.pop_back();
    }
    //TODO:?
    cycleFind[i] = 0;
    return false;
}

bool CycleDetection() {
    int i;
    int cycleFind[26] = {0}, allFind[26] = {0};
    for (i = 0; i < 26; i++) {
        int countI = countHT(i, true, false);
        //for(int j =0;j<26;j++)countI+=alphabet[i][j]->listLength;
        if (!allFind[i] && countI != 0) {
            if (CycleVisitDetection(i, cycleFind, allFind)) {
                return true;
            }
            resetArray(cycleFind, 26);
        }
    }
    return false;
}


list<string> DFS(int row, int column) {
    //深度优先搜索出以每个不同的“头尾”开头的单词链,放入outputWordList
    auto *wordList = alphabet[row][column];
    list<string> result;
    for (auto iter = wordList->listOfWord.begin(); iter != wordList->listOfWord.end(); ++iter) {
        string currentWord = (*iter)->wordContent;
        if (dirty[currentWord]) continue;
        dirty[currentWord] = true;
        result.push_back(currentWord);
        for (int i = 0; i < 26; ++i) {
            if (alphabet[column][i]->listLength != 0) {
                auto wordAfter = DFS(column, i);
                for (auto after_iter = wordAfter.begin(); after_iter != wordAfter.end(); ++after_iter) {
                    result.push_back(currentWord + " " + (*after_iter));
                }
            }
        }
        dirty[currentWord] = false;
    }
    return result;
}

void FunctionN_noR() {
    //配合DFS用outputWordList获取所有单词链
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (alphabet[i][j]->listLength > 0) {
                auto wordList = DFS(i, j);
                for (auto iter = wordList.begin(); iter != wordList.end(); ++iter) {
                    if ((*iter).find(" ") != string::npos) {
                        outputWordList.push_back((*iter));
                    }
                }
            }
//            outputWordList.splice(outputWordList.end(), wordList);
        }
    }
}

inline bool checkTailOk(list<string> wordList) {
    if (!wordList.empty()) {
        string word = wordList.back();
        if (word[word.size() - 1] == tail) return true;
        return false;
    } else {
        return false;
    }
}

list<string> findGreatestWDFS(int row, int column) {
    auto *wordList = alphabet[row][column];
    list<string> result;
    if (wordList->listLength > 0) {
        string currentWord = (*wordList->listOfWord.begin())->wordContent;
        if (dirty[currentWord]) return result;
        dirty[currentWord] = true;
        result.push_back(currentWord);
        list<string> maxWordAfter;
        int maxLength = 0;
        for (int i = 0; i < 26; ++i) {
            if (alphabet[column][i]->listLength != 0) {
                auto wordAfter = findGreatestWDFS(column, i);

                int curLength = wordAfter.size();
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxWordAfter = wordAfter;
                }
            }
        }
        result.splice(result.end(), maxWordAfter);
        dirty[currentWord] = false;
    }
    return result;
}

list<string> findGreatestWDFSReverse(int row, int column) {
    list<string> maxWordList;
    if (alphabet[row][column]->listLength > 0) {
        string word = (*alphabet[row][column]->listOfWord.begin())->wordContent;
        if (dirty[word]) return maxWordList;
        else {
            dirty[word] = true;
            int maxLength = 0;
            for (int index = 0; index < 26; ++index) {
                auto *wordList = alphabet[index][row];
                if (wordList->listLength > 0) {
                    auto curList = findGreatestWDFSReverse(index, row);
                    int curLength = curList.size();
                    if (curLength > maxLength) {
                        maxLength = curLength;
                        maxWordList = curList;
                    }
                }
            }
            maxWordList.push_back(word);
            dirty[word] = true;
        }
    }
    return maxWordList;
}

list<string> findGreatestWDFS(int row, int column, char t) { // 指定尾的 DFS
    auto *wordList = alphabet[row][column];
    list<string> result;
    if (wordList->listLength > 0) {
        string currentWord = (*wordList->listOfWord.begin())->wordContent;
        if (dirty[currentWord]) return result;
        dirty[currentWord] = true;
        list<string> maxWordAfter;
        int maxLength = 0;
        for (int i = 0; i < 26; ++i) {
            if (alphabet[column][i]->listLength != 0) {
                auto wordAfter = findGreatestWDFS(column, i, t);
                if (!checkTailOk(wordAfter)) continue;
                int curLength = wordAfter.size();
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxWordAfter = wordAfter;
                }
            }
        }
        result.push_back(currentWord);
        result.splice(result.end(), maxWordAfter);
        if (!checkTailOk(result)) {
            result.clear();
        }
        dirty[currentWord] = false;
    }
    return result;
}

inline int getLength(list<string> wordList) { // long or int?
    int result = 0;
    for (auto iter = wordList.begin(); iter != wordList.end(); ++iter) {
        result += (*iter).size();
    }
    return result;
}

list<string> findGreatestCDFS(int row, int column) {
    auto *wordList = alphabet[row][column];
    list<string> result;
    if (wordList->listLength > 0) {
        string currentWord = (*wordList->listOfWord.begin())->wordContent;
        if (dirty[currentWord]) return result;
        dirty[currentWord] = true;
        result.push_back(currentWord);
        list<string> maxWordAfter;
        int maxLength = 0;
        for (int i = 0; i < 26; ++i) {
            if (alphabet[column][i]->listLength != 0) {
                auto wordAfter = findGreatestCDFS(column, i);
                int curLength = getLength(wordAfter);
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxWordAfter = wordAfter;
                }
            }
        }
        result.splice(result.end(), maxWordAfter);
        dirty[currentWord] = false;
    }
    return result;
}

list<string> findGreatestCDFSReverse(int row, int column) {
    list<string> maxWordList;
    if (alphabet[row][column]->listLength > 0) {
        string word = (*alphabet[row][column]->listOfWord.begin())->wordContent;
        if (dirty[word]) return maxWordList;
        else {
            dirty[word] = true;
            int maxLength = 0;
            for (int index = 0; index < 26; ++index) {
                auto *wordList = alphabet[index][row];
                if (wordList->listLength > 0) {
                    auto curList = findGreatestCDFSReverse(index, row);
                    int curLength = getLength(curList);
                    if (curLength > maxLength) {
                        maxLength = curLength;
                        maxWordList = curList;
                    }
                }
            }
            maxWordList.push_back(word);
            dirty[word] = true;
        }
    }
    return maxWordList;
}

list<string> findGreatestCDFS(int row, int column, char t) { // 指定尾
    auto *wordList = alphabet[row][column];
    list<string> result;
    if (wordList->listLength > 0) {
        string currentWord = (*wordList->listOfWord.begin())->wordContent;
        if (dirty[currentWord]) return result;
        dirty[currentWord] = true;
        result.push_back(currentWord);
        list<string> maxWordAfter;
        int maxLength = 0;
        for (int i = 0; i < 26; ++i) {
            if (alphabet[column][i]->listLength != 0) {
                auto wordAfter = findGreatestCDFS(column, i, t);
                if (!checkTailOk(wordAfter)) continue;
                int curLength = getLength(wordAfter);
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxWordAfter = wordAfter;
                }
            }
        }
        result.splice(result.end(), maxWordAfter);
        if (!checkTailOk(result)) {
            result.clear();
        }
        dirty[currentWord] = false;
    }
    return result;
}

list<string> FunctionW_noR() {
    //找到入度为0的“头尾”，然后遍历这些点（“头尾”相同的作为开头只找一次)，用Dijkstra寻找最大
    //W长度为单词列表长度，C长度为单词字母总长
    if (head == 0 && tail == 0) { // 如果没有指定头尾
        list<string> maxListOfWords;
        int maxLength = 0;
        for (int i = 0; i < 26; i++) {
            if (countHT(i, false, true) == 0) { // 如果 i 入度为 0
                for (int j = 0; j < 26; ++j) {
                    auto curWordList = findGreatestWDFS(i, j);
                    int curLength = curWordList.size();
                    if (curLength > maxLength) {
                        maxLength = curLength;
                        maxListOfWords = curWordList;
                    }
                }
            }
        }
        return maxListOfWords;
    } else {
        list<string> maxListOfWords;
        int maxLength = 0;
        if (head != 0 && tail != 0) { // 指定了头和尾
            int i = fromChar2Index(head);
            for (int j = 0; j < 26; ++j) {
                auto curWordList = findGreatestWDFS(i, j, tail);
                int curLength = curWordList.size();
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxListOfWords = curWordList;
                }
            }
        } else if (head != 0) { // 只指定了头
            int i = fromChar2Index(head);
            for (int j = 0; j < 26; ++j) {
                auto curWordList = findGreatestWDFS(i, j);
                int curLength = curWordList.size();
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxListOfWords = curWordList;
                }
            }
        } else { // 指定了尾
            int j = fromChar2Index(tail);
            for (int i = 0; i < 26; i++) {
                auto curWordList = findGreatestWDFSReverse(i, j);
                int curLength = curWordList.size();
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxListOfWords = curWordList;
                }
            }
        }
        return maxListOfWords;
    }
}

list<string> FunctionC_noR() {
    //找到入度为0的“头尾”，然后遍历这些点（“头尾”相同的作为开头只找一次)，用Dijkstra寻找最大
    //W长度为单词列表长度，C长度为单词字母总长
    if (head == 0 && tail == 0) { // 如果没有指定头尾
        list<string> maxListOfWords;
        int maxLength = 0;
        for (int i = 0; i < 26; i++) {
            if (countHT(i, false, true) == 0) { // 如果 i 入度为 0
                for (int j = 0; j < 26; ++j) {
                    auto curWordList = findGreatestCDFS(i, j);
                    int curLength = getLength(curWordList);
                    if (curLength > maxLength) {
                        maxLength = curLength;
                        maxListOfWords = curWordList;
                    }
                }
            }
        }
        return maxListOfWords;
    } else {
        list<string> maxListOfWords;
        int maxLength = 0;
        if (head != 0 && tail != 0) { // 指定了头和尾
            int i = fromChar2Index(head);
            for (int j = 0; j < 26; ++j) {
                auto curWordList = findGreatestCDFS(i, j, tail);
                int curLength = getLength(curWordList);
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxListOfWords = curWordList;
                }
            }
        } else if (head != 0) { // 只指定了头
            int i = fromChar2Index(head);
            for (int j = 0; j < 26; ++j) {
                auto curWordList = findGreatestCDFS(i, j);
                int curLength = getLength(curWordList);
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxListOfWords = curWordList;
                }
            }
        } else { // 指定了尾
            int j = fromChar2Index(tail);
            for (int i = 0; i < 26; i++) {
                auto curWordList = findGreatestCDFSReverse(i, j);
                int curLength = getLength(curWordList);
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxListOfWords = curWordList;
                }
            }
        }
        return maxListOfWords;
    }
}

//  aaa ab， m生效
//此外和N_noR相同

void FunctionM() {
    //找到入度为0的“头尾”，然后遍历这些点（“头尾”相同的作为开头只找一次)，用Dijkstra寻找最大
    //长度为单词列表长度
}


//测试循环检测：

int main(int argc, char *argv[]) {
    try {
        inputProcess(argc, argv);
        bool containsLoop = CycleDetection();
        if (!params['r'] && containsLoop) throw "ERROR: contains loop.";
//        inputProcess(argc, argv);
//        cout << "cycle detection " << CycleDetection() << endl;
//        for (auto iter = outputWordList.begin(); iter != outputWordList.end(); iter++) {
//            cout << (*iter) << " -> ";
//        }
        if (params['n']) {
            FunctionN_noR();
            cout << outputWordList.size() << endl;
            for (auto iter = outputWordList.begin(); iter != outputWordList.end(); ++iter) {
                cout << (*iter) << endl;
            }
        } else {
            ofstream outFile;
            outFile.open("solution.txt", ios::out);
            if (params['w']) {
                auto outputWordList = FunctionW_noR();
                if (outputWordList.size() > 1) {
                    for (auto iter = outputWordList.begin(); iter != outputWordList.end(); ++iter) {
                        outFile << (*iter) << endl;
                        cout << (*iter) << endl;
                    }
                }
            } else if (params['c']) {
                auto outputWordList = FunctionC_noR();
                if (outputWordList.size() > 1) {
                    for (auto iter = outputWordList.begin(); iter != outputWordList.end(); ++iter) {
                        outFile << (*iter) << endl;
                        cout << (*iter) << endl;
                    }
                }
            }
            outFile.close();
        }
    } catch (const char *msg) {
        cout << msg << endl;
    }
    return 0;
}

//测试参数输入部分：
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