#include "inputProcess.h"
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
extern map<string, bool> dirty;
extern WordList* alphabet[26][26];

map<char, bool> params = {
        {'n', false},
        {'w', false},
        {'c', false},
        {'m', false},
        {'h', false},
        {'t', false},
        {'r', false}
};
string fileName;
char paramHead = 0;
char paramTail = 0;

inline int fromChar2Index(char c) {
    return c - 'a';
}

inline bool isLegalFilename(const string& name) {
    size_t len = name.length(); // .txt
    if (len > 3 && name[len - 1] == 't' && name[len - 2] == 'x'
        && name[len - 3] == 't' && name[len - 4] == '.') return true;
    return false;
}

void insertWord(string wordContent0) {
    int length = (int)wordContent0.length();
    int tmpLenth = length - 1;

    if (dirty.find(wordContent0) == dirty.end()) {
        dirty[wordContent0] = false;
        auto* newWord = new Word(length, wordContent0);
        auto* wordList = alphabet[fromChar2Index(wordContent0[0])]
            [fromChar2Index(wordContent0[tmpLenth])];
        wordList->listLength++;
        if (params['c']) {
            auto iter = wordList->listOfWord.begin();
            for (; iter != wordList->listOfWord.end() &&
                (*iter)->wordLength > length; ++iter) {
            } // TODO 可以只将第一个设置为最大
            wordList->listOfWord.insert(iter, newWord);
        }
        else
        {
            //cout << "-check? "<<newWord->wordContent << endl;
            wordList->listOfWord.push_back(newWord);
        }
    }
    
}
 

void initAlphabet() { // 初始化 alphabet
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (alphabet[i][j] != NULL) {
                alphabet[i][j]->~WordList();
            }
            list<Word*> listOfWord;
            auto* wordList = new WordList(listOfWord);
            alphabet[i][j] = wordList;
        }
        degree[i][0] = 0;
        degree[i][1] = 0;
    }
    for (auto iter = params.begin(); iter != params.end(); iter++) {
        iter->second = false;
    }
    if(!outputWordList.empty())outputWordList.clear();
    if(!dirty.empty()) dirty.clear();
    paramHead = 0;
    paramTail = 0;
}
 
 
void readWordFromPort(char* words[], int len) {

    for (int i = 0; i < len; i++) {

        string wordContent = words[i];
        transform(wordContent.begin(), wordContent.end(), wordContent.begin(), ::tolower);
        if (wordContent.length() > 1) {
            insertWord(wordContent);

        }
    }

    //cout << "====READ END======" << endl;
}

void analyseParam(char portHead, char portTail, bool enable_loop, char functionType)throw(ParamHTException)
{
    try {
       
        if (portHead != 0) {
            if (!isalpha(portHead)) {
                throw ParamHTException();
            }
                params['h'] = true;
                paramHead = portHead;
            
        }
        if (portTail != 0) {
            if (!isalpha(portTail)) {
                throw ParamHTException();
            }
            params['t'] = true;
            paramTail = portTail;
        }
        if (enable_loop) {
            params['r'] = true;
        }
        if (functionType == 'm' || functionType == 'w'
            || functionType == 'c' || functionType == 'n') {
            params[functionType] = true;
        }
        else {
            throw ParamHTException();
            return;
        }
    }
    catch (ParamHTException& e) {
        throw;
    }
}
 
void testInputProcess(char* words[], int len, char portHead, char portTail, bool enable_loop, char functionType) throw(ParamHTException)
{
    try {
        initAlphabet();
        analyseParam(portHead, portTail, enable_loop, functionType);
        readWordFromPort(words, len);
        initGraph();
        //cout << "====== PORT READ INPUT END=======" << endl;
    }
    catch (ParamHTException& e) {
        throw;
    }
}


void analyzeParam(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        //cout << arg << endl;
        if (arg[0] == '-') {
            if (arg.length() == 2) {
                char c = arg[1];
                if (params.find(c) == params.end() || params[c]) {
                    throw "ERROR: duplicated parameter or invalid parameter";
                }
                else {
                    params[c] = true;
                    if (c == 'h' || c == 't') {
                        ++i;
                        if (i >= argc) {
                            throw "ERROR: a parameter is needed after -h or -t.";
                        }
                        else {
                            arg = argv[i];
                            if (arg.length() == 1 && isalpha(arg[0])) {
                                if (c == 'h') {
                                    paramHead = tolower(arg[0]);
                                }
                                else { // c == 't'
                                    paramTail = tolower(arg[0]);
                                }
                            }
                            else {
                                throw "ERROR: illegal parameter after -h or -t.";
                            }
                        }
                    }
                }
            }
            else {
                if (isLegalFilename(arg)) {
                    if (fileName.empty()) {
                        fileName = arg;
                    }
                    else {
                        throw "ERROR: duplicated file name";
                    }
                }
                else {
                    throw "ERROR: parameter illegal.[.txt needed for a file name]";
                }
            }
        }
        else
        {
            if (isLegalFilename(arg)) {
                if (fileName.empty()) {
                    fileName = arg;
                }
                else {
                    throw "ERROR: duplicated file name";
                }
            }
            else {
                throw "ERROR: parameter illegal.[.txt needed for a file name]";
            }
        }
    }
    // 检测参数有无缺失 / 冲突
    if (!(params['n'] || params['w'] || params['c'] || params['m'])) { // 无功能参数
        throw "ERROR: no functional parameter.";
    }
    else if (params['m'] && (params['n'] || params['w'] || params['c'] || // 是否冲突
        params['h'] || params['t'] || params['r'])) {
        throw "ERROR: parameter illegal[-m]";
    }
    else if (params['n'] && (params['m'] || params['w'] || params['c'] ||
        params['h'] || params['t'] || params['r'])) {
        throw "ERROR: parameter illegal[-n]";
    }
    else if (params['w'] && params['c']) {
        throw "ERROR: -w and -c cannot be used together.";
    }

}

void readWordFromFile() {
    ifstream inputFile;
    inputFile.open(fileName, ios::in);
    if (inputFile.good() && inputFile.is_open()) { // 可以正常读入
        inputFile >> noskipws; // 单个字母读入
        char current;
        string wordContent;
        while (inputFile.peek() != EOF) {
            inputFile >> current;
            if (isalpha(current)) {
                if (!islower(current)) {
                    current = 'a' + (current - 'A');
                }
                wordContent += current;
            }
            else {
                if (wordContent.length() > 1) {
                    insertWord(wordContent);
                }
                wordContent = "";
            }
        }
        if (wordContent.length() > 1) {
            insertWord(wordContent);
        }
        inputFile.close();

    }
    else { // 文件不存在
        throw "ERROR: cannot open file."; // TODO catch error
    }
}


void inputProcess(int argc, char* argv[]) {
    initAlphabet();
    analyzeParam(argc, argv);
    readWordFromFile();
    initGraph();

}