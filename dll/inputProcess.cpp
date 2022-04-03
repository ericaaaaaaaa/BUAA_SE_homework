#include "pch.h"
#include "inputProcess.h"
 
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

void insertWord(string wordContent) {
    if (dirty.find(wordContent) == dirty.end()) {
        dirty[wordContent] = false;
        int length = (int)wordContent.length();
        int tmpLenth = length - 1;
        auto* newWord = new Word(length, wordContent);
        auto* wordList = alphabet[fromChar2Index(wordContent[0])]
            [fromChar2Index(wordContent[tmpLenth])];
        wordList->listLength++;
        if (params['c']) {
            auto iter = wordList->listOfWord.begin();
            for (; iter != wordList->listOfWord.end() &&
                (*iter)->wordLength > length; ++iter) {
            } // TODO ����ֻ����һ������Ϊ���
            wordList->listOfWord.insert(iter, newWord);
        }
        else
        {
            wordList->listOfWord.push_back(newWord);
        }
    }
}


    // �����ļ��е��ı�
/*
    void readWordFromFile() {
        ifstream inputFile;
        inputFile.open(fileName, ios::in);
        if (inputFile.good()) { // ������������
            inputFile >> noskipws; // ������ĸ����
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
        else { // �ļ�������
            throw "ERROR: cannot open file."; // TODO catch error
        }
    }
    */

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

void initAlphabet() { // ��ʼ�� alphabet
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
    if (!outputWordList.empty())outputWordList.clear();
    if (!dirty.empty()) dirty.clear();
    paramHead = 0;
    paramTail = 0;
}

// ���������в���
/*
void analyzeParam(int argc, char* argv[]) {
    //regex reg(".*\.txt"); // ������ʽ
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
    // ����������ȱʧ / ��ͻ
    if (!(params['n'] || params['w'] || params['c'] || params['m'])) { // �޹��ܲ���
        throw "ERROR: no functional parameter.";
    }
    else if (params['m'] && (params['n'] || params['w'] || params['c'] || // �Ƿ��ͻ
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
*/

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

/*
void inputProcess(int argc, char* argv[]) {
    initAlphabet();
    analyzeParam(argc, argv);
    readWordFromFile();
    initGraph();
    //cout << "====== FILE READ INPUT END=======" << endl;

}
*/

void testInputProcess(char* words[], int len, char portHead, char portTail, bool enable_loop, char functionType) {
    initAlphabet();
    analyseParam(portHead, portTail, enable_loop, functionType);
    readWordFromPort(words, len);
    initGraph();
    //cout << "====== PORT READ INPUT END=======" << endl;
}

