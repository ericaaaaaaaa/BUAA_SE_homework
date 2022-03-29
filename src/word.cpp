#include "word.h"

list<string> outputWordList;
int degree[26][2]; // 0->in, 1->out
map<string, bool> dirty;
WordList *alphabet[26][26];



inline int fromChar2Index(char c) {
    return c - 'a';
}

void resultValue(char **result) {
    auto iter = outputWordList.begin();
    for (int i = 0; iter != outputWordList.end(); iter++, i++) {
        result[i] = (char *) (*iter).data();
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

void initGraph() {
    cout << "initGraph..."<<endl;
    for (int i = 0; i < 26; i++) {
        degree[i][0] = countHT(i, true, true);//入度
        degree[i][1] = countHT(i, false, true);//出度
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
        if (word[word.size() - 1] == paramTail) return true;
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

list<string> findGreatestWDFS_R(int row, int column) {
    auto *wordList = alphabet[row][column];
    list<string> result;
    if (wordList->listLength > 0) {
        auto iter = wordList->listOfWord.begin();
        for (; iter != wordList->listOfWord.end() && dirty[(*iter)->wordContent]; ++iter) {}
        if (iter == wordList->listOfWord.end()) return result;
        string currentWord = (*iter)->wordContent;
        if (dirty[currentWord]) return result;
        dirty[currentWord] = true;
        result.push_back(currentWord);
        list<string> maxWordAfter;
        int maxLength = 0;
        for (int i = 0; i < 26; ++i) {
            if (alphabet[column][i]->listLength != 0) {
                auto wordAfter = findGreatestWDFS_R(column, i);

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

list<string> findGreatestWDFSReverse_R(int row, int column) {
    list<string> maxWordList;
    auto *wordList = alphabet[row][column];
    if (wordList->listLength > 0) {
        auto iter = wordList->listOfWord.begin();
        for (; iter != wordList->listOfWord.end() && dirty[(*iter)->wordContent]; ++iter) {}
        if (iter == wordList->listOfWord.end()) return maxWordList;
        string word = (*iter)->wordContent;
        if (dirty[word]) return maxWordList;
        else {
            dirty[word] = true;
            int maxLength = 0;
            for (int index = 0; index < 26; ++index) {
                auto *wordList = alphabet[index][row];
                if (wordList->listLength > 0) {
                    auto curList = findGreatestWDFSReverse_R(index, row);
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

list<string> findGreatestWDFS_R(int row, int column, char t) { // 指定尾的 DFS
    auto *wordList = alphabet[row][column];
    list<string> result;
    if (wordList->listLength > 0) {
        auto iter = wordList->listOfWord.begin();
        for (; iter != wordList->listOfWord.end() && dirty[(*iter)->wordContent]; ++iter) {}
        if (iter == wordList->listOfWord.end()) return result;
        string currentWord = (*iter)->wordContent;
        if (dirty[currentWord]) return result;
        dirty[currentWord] = true;
        list<string> maxWordAfter;
        int maxLength = 0;
        for (int i = 0; i < 26; ++i) {
            if (alphabet[column][i]->listLength != 0) {
                auto wordAfter = findGreatestWDFS_R(column, i, t);
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

list<string> findGreatestCDFS_R(int row, int column) {
    auto *wordList = alphabet[row][column];
    list<string> result;
    if (wordList->listLength > 0) {
        auto iter = wordList->listOfWord.begin();
        for (; iter != wordList->listOfWord.end() && dirty[(*iter)->wordContent]; ++iter) {}
        if (iter == wordList->listOfWord.end()) return result;
        string currentWord = (*iter)->wordContent;
        if (dirty[currentWord]) return result;
        dirty[currentWord] = true;
        result.push_back(currentWord);
        list<string> maxWordAfter;
        int maxLength = 0;
        for (int i = 0; i < 26; ++i) {
            if (alphabet[column][i]->listLength != 0) {
                auto wordAfter = findGreatestCDFS_R(column, i);
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

list<string> findGreatestCDFSReverse_R(int row, int column) {
    list<string> maxWordList;
    auto *wordList = alphabet[row][column];
    if (wordList->listLength > 0) {
        auto iter = wordList->listOfWord.begin();
        for (; iter != wordList->listOfWord.end() && dirty[(*iter)->wordContent]; ++iter) {}
        if (iter == wordList->listOfWord.end()) return maxWordList;
        string word = (*iter)->wordContent;
        if (dirty[word]) return maxWordList;
        else {
            dirty[word] = true;
            int maxLength = 0;
            for (int index = 0; index < 26; ++index) {
                auto *wordList = alphabet[index][row];
                if (wordList->listLength > 0) {
                    auto curList = findGreatestCDFSReverse_R(index, row);
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

list<string> findGreatestCDFS_R(int row, int column, char t) { // 指定尾
    auto *wordList = alphabet[row][column];
    list<string> result;
    if (wordList->listLength > 0) {
        auto iter = wordList->listOfWord.begin();
        for (; iter != wordList->listOfWord.end() && dirty[(*iter)->wordContent]; ++iter) {}
        if (iter == wordList->listOfWord.end()) return result;
        string currentWord = (*iter)->wordContent;
        if (dirty[currentWord]) return result;
        dirty[currentWord] = true;
        result.push_back(currentWord);
        list<string> maxWordAfter;
        int maxLength = 0;
        for (int i = 0; i < 26; ++i) {
            if (alphabet[column][i]->listLength != 0) {
                auto wordAfter = findGreatestCDFS_R(column, i, t);
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
    if (paramHead == 0 && paramTail == 0) { // 如果没有指定头尾
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
        if (paramHead != 0 && paramTail != 0) { // 指定了头和尾
            int i = fromChar2Index(paramHead);
            for (int j = 0; j < 26; ++j) {
                auto curWordList = findGreatestWDFS(i, j, paramTail);
                int curLength = curWordList.size();
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxListOfWords = curWordList;
                }
            }
        } else if (paramHead != 0) { // 只指定了头
            int i = fromChar2Index(paramHead);
            for (int j = 0; j < 26; ++j) {
                auto curWordList = findGreatestWDFS(i, j);
                int curLength = curWordList.size();
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxListOfWords = curWordList;
                }
            }
        } else { // 指定了尾
            int j = fromChar2Index(paramTail);
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

list<string> FunctionW_R() {
    //找到入度为0的“头尾”，然后遍历这些点（“头尾”相同的作为开头只找一次)，用Dijkstra寻找最大
    //W长度为单词列表长度，C长度为单词字母总长
    if (paramHead == 0 && paramTail == 0) { // 如果没有指定头尾
        list<string> maxListOfWords;
        int maxLength = 0;
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; ++j) {
                auto curWordList = findGreatestWDFS_R(i, j);
                int curLength = curWordList.size();
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxListOfWords = curWordList;
                }
            }
        }
        return maxListOfWords;
    } else {
        list<string> maxListOfWords;
        int maxLength = 0;
        if (paramHead != 0 && paramTail != 0) { // 指定了头和尾
            int i = fromChar2Index(paramHead);
            for (int j = 0; j < 26; ++j) {
                auto curWordList = findGreatestWDFS_R(i, j, paramTail);
                int curLength = curWordList.size();
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxListOfWords = curWordList;
                }
            }
        } else if (paramHead != 0) { // 只指定了头
            int i = fromChar2Index(paramHead);
            for (int j = 0; j < 26; ++j) {
                auto curWordList = findGreatestWDFS_R(i, j);
                int curLength = curWordList.size();
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxListOfWords = curWordList;
                }
            }
        } else { // 指定了尾
            int j = fromChar2Index(paramTail);
            for (int i = 0; i < 26; i++) {
                auto curWordList = findGreatestWDFSReverse_R(i, j);
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
    if (paramHead == 0 && paramTail == 0) { // 如果没有指定头尾
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
        if (paramHead != 0 && paramTail != 0) { // 指定了头和尾
            int i = fromChar2Index(paramHead);
            for (int j = 0; j < 26; ++j) {
                auto curWordList = findGreatestCDFS(i, j, paramTail);
                int curLength = getLength(curWordList);
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxListOfWords = curWordList;
                }
            }
        } else if (paramHead != 0) { // 只指定了头
            int i = fromChar2Index(paramHead);
            for (int j = 0; j < 26; ++j) {
                auto curWordList = findGreatestCDFS(i, j);
                int curLength = getLength(curWordList);
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxListOfWords = curWordList;
                }
            }
        } else { // 指定了尾
            int j = fromChar2Index(paramTail);
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

list<string> FunctionC_R() {
    //找到入度为0的“头尾”，然后遍历这些点（“头尾”相同的作为开头只找一次)，用Dijkstra寻找最大
    //W长度为单词列表长度，C长度为单词字母总长
    if (paramHead == 0 && paramTail == 0) { // 如果没有指定头尾
        list<string> maxListOfWords;
        int maxLength = 0;
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; ++j) {
                auto curWordList = findGreatestCDFS_R(i, j);
                int curLength = getLength(curWordList);
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxListOfWords = curWordList;
                }
            }
        }
        return maxListOfWords;
    } else {
        list<string> maxListOfWords;
        int maxLength = 0;
        if (paramHead != 0 && paramTail != 0) { // 指定了头和尾
            int i = fromChar2Index(paramHead);
            for (int j = 0; j < 26; ++j) {
                auto curWordList = findGreatestCDFS_R(i, j, paramTail);
                int curLength = getLength(curWordList);
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxListOfWords = curWordList;
                }
            }
        } else if (paramHead != 0) { // 只指定了头
            int i = fromChar2Index(paramHead);
            for (int j = 0; j < 26; ++j) {
                auto curWordList = findGreatestCDFS_R(i, j);
                int curLength = getLength(curWordList);
                if (curLength > maxLength) {
                    maxLength = curLength;
                    maxListOfWords = curWordList;
                }
            }
        } else { // 指定了尾
            int j = fromChar2Index(paramTail);
            for (int i = 0; i < 26; i++) {
                auto curWordList = findGreatestCDFSReverse_R(i, j);
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




void findGreatestDj(int i, int *pred, int *predii, int *rec, int *maxDist) {
    int k, j;
    int tmp_maxDist;
    int cycleFind[26] = {0};
    int dist[26] = {0};
    int tmp_rec = 0;
    bool reverse = params['t'] && !params['h'];

    for (j = 0; j < 26; j++) {

        if (degree[j][0] == 0 && degree[j][1] == 0)continue;
        tmp_maxDist = 0;
        tmp_rec = i;

        for (k = 0; k < 26; k++) {
            //cout << char('a'+k) << ": " << dist[k] <<" "<< cycleFind[k] << endl;
            if (dist[k] == 0)continue;
            if (cycleFind[k])continue;
            if (dist[k] > tmp_maxDist) {
                tmp_maxDist = dist[k];
                tmp_rec = k;
            }
        }
        //cout << "rmp_rec " << char('a' + tmp_rec) << endl;
        if (cycleFind[tmp_rec])break;

        for (k = 0; k < 26; k++) {
            int row = reverse ? k : tmp_rec;
            int column = reverse ? tmp_rec : k;

            if (alphabet[row][column]->listLength == 0)continue;
            string currentWord = (*alphabet[row][column]->listOfWord.begin())->wordContent;
            int weight = params['c'] ? currentWord.length() : 1;
            if (dist[tmp_rec] + weight > dist[k]) {
                dist[k] = dist[tmp_rec] + weight;
                if (predii == nullptr || column != row) {
                    pred[k] = tmp_rec;
                } else {
                    predii[k] = 1;
                }
            }
        }
        cycleFind[tmp_rec] = 1;
        if (params['t'] && params['h'] && tmp_rec == paramTail - 'a')break;
    }
    //paramTail and paramHead are defined at the same time
    if (params['t'] && params['h'] && tmp_rec == paramTail - 'a') {
        *rec = tmp_rec;
        *maxDist = dist[tmp_rec];
        return;
    }

    for (k = 0; k < 26; k++) {
        if (k != i && dist[k] > tmp_maxDist) {
            tmp_maxDist = dist[k];
            tmp_rec = k;
        }
    }
    *rec = tmp_rec;
    *maxDist = tmp_maxDist;

}

bool getDJlist(int rec, int *pred, int *predii, int i) {
    int k = rec;
    int aa = 0;
    bool reverse = params['t'] && !params['h'];
    while (k != i && aa <= 1) {
        k = pred[k];
        aa++;
        if (predii != nullptr)aa += predii[k];
    }
    if (predii != nullptr) aa += predii[i];
    k = rec;
    if (aa > 1) {
        outputWordList.clear();
        if (reverse) {
            while (k != i) {
                if (predii != nullptr && predii[k]) {
                    outputWordList.push_back((*alphabet[k][k]->listOfWord.begin())->wordContent);
                    //k = pred[k];
                }
                outputWordList.push_back((*alphabet[k][pred[k]]->listOfWord.begin())->wordContent);
                k = pred[k];
            }
            if (!params['m'] && alphabet[k][pred[k]]->listLength) {
                outputWordList.push_back((*alphabet[k][pred[k]]->listOfWord.begin())->wordContent);
            }
        } else {
            while (k != i) {
                if (predii != nullptr && predii[k]) {
                    outputWordList.push_front((*alphabet[k][k]->listOfWord.begin())->wordContent);
                    //k = pred[k];
                }
                outputWordList.push_front((*alphabet[pred[k]][k]->listOfWord.begin())->wordContent);
                k = pred[k];
            }
            if (!params['m'] && alphabet[pred[k]][k]->listLength) {
                outputWordList.push_front((*alphabet[pred[k]][k]->listOfWord.begin())->wordContent);
            }
        }
        return true;
    }
    return false;
}


void FunctionWC_noR() {
    //找到入度为0的“头尾”，然后遍历这些点（“头尾”相同的作为开头只找一次)，用Dijkstra寻找最大
    //W长度为单词列表长度，C长度为单词字母总长
    int i, j, k;
    int pred[26] = {0};
    int predii[26] = {0};
    int maxAll = 0;
    int rec = 0;
    int maxDist = 0;
    list<string> maxAllList;

    if (paramTail == 0 && paramHead == 0) {
        for (i = 0; i < 26; i++) {
            if (degree[i][0] != 0 && degree[i][1] == 0) {//找到了单源点即有他开头无他结尾的单词后：
                resetArray(pred, 26);
                resetArray(predii, 26);
                pred[i] = i;
                findGreatestDj(i, pred, predii, &rec, &maxDist);
                if (maxDist > maxAll) {
                    if (getDJlist(rec, pred, predii, i)) {
                        maxAll = maxDist;
                    }
                }
            }
        }
    } else {
        i = paramHead ? (paramHead - 'a') : (paramTail - 'a');
        if (paramHead && degree[i][0] != 0 || !paramHead && degree[i][1] != 0) { //有它开头（如果是tail就得以他结尾）即可
            pred[i] = i;
            findGreatestDj(i, pred, predii, &rec, &maxDist);
            getDJlist(rec, pred, predii, i);
        }
    }
    cout << "====== CW_Dj end =========" << endl;
}




//  aaa ab， m生效
//此外和N_noR相同

void FunctionM() {
    //找到入度为0的“头尾”，然后遍历这些点（“头尾”相同的作为开头只找一次)，用Dijkstra寻找最大
    //长度为单词列表长度
    int i, j, k;
    //int degree[26][2];
    int cycleFind[26] = {0};
    int dist[26] = {0};//noR ? length?
    int pred[26] = {0};
    int maxAll = 0;
    list<string> maxAllList;
    for (i = 0; i < 26; i++) {
        if (degree[i][0] != 0 && degree[i][1] == 0) {//找到了单源点后：
            resetArray(dist, 26);
            resetArray(pred, 26);
            resetArray(cycleFind, 26);
            pred[i] = i;
            int maxDist = 0;
            int rec = 0;
            resetArray(pred, 26);
            pred[i] = i;
            findGreatestDj(i, pred, nullptr, &rec, &maxDist);
            //cout << "rec: " << rec << endl;
            if (maxDist > maxAll) {
                if (getDJlist(rec, pred, nullptr, i)) {
                    maxAll = maxDist;
                }
            }
        }
    }
    cout << "====== M_Dj end =========" << endl;
}


//测试循环检测：

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