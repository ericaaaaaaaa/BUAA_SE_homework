#ifndef INPUTPROCESS
#define INPUTPROCESS
#pragma once
#include "stdio.h"
#include <iostream>
#include <fstream>
#include "word.h"
#include "regex"
#endif

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
char head, tail;

inline int fromChar2Index(char c) {
	return c - 'a';
}

void insertWord(string wordContent) {
	if (dirty.find(wordContent) == dirty.end()) {
		dirty[wordContent] = false;
		int length = wordContent.length();
        auto *newWord = new Word(length, wordContent);
		auto *wordList = alphabet[fromChar2Index(wordContent[0])]
			    [fromChar2Index(wordContent[length - 1])];
		wordList->listLength++;
		if (params['c']) {
			auto iter = wordList->listOfWord.begin();
			for (;iter != wordList->listOfWord.end() &&
                          (*iter)->wordLength > length; ++iter) { } // TODO 可以只将第一个设置为最大
			wordList->listOfWord.insert(iter, newWord);
		}
		else
		{
			wordList->listOfWord.push_back(newWord);
		}
	}
}


// 读入文件中的文本
void readWordFromFile() {
	ifstream inputFile;
	inputFile.open(fileName, ios::in);
	if (inputFile.good()) { // 可以正常读入
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

void initAlphabet() { // 初始化 alphabet
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            list<Word *> listOfWord;
            auto *wordList = new WordList();
            wordList->listOfWord = listOfWord;
            wordList->listLength = 0;
            alphabet[i][j] = wordList;
        }
    }
}

// 分析命令行参数
void analyzeParam(int argc, char* argv[]) {
	regex reg(".*\.txt"); // 正则表达式
	for (int i = 1; i < argc; ++i) {
		string arg = argv[i];
        cout << arg << endl;
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
                        } else {
                            arg = argv[i];
                            if (arg.length() == 1 && isalpha(arg[0])) {
                                if (c == 'h') {
                                    head = tolower(arg[0]);
                                } else { // c == 't'
                                    tail = tolower(arg[0]);
                                }
                            } else {
                                throw "ERROR: illegal parameter after -h or -t.";
                            }
                        }
                    }
                }
			}
			else {
				if (regex_match(arg, reg)) {
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
            if (regex_match(arg, reg)) {
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
    } else if (params['m'] && (params['n'] || params['w'] || params['c'] || // 是否冲突
                               params['h'] || params['t'] || params['r'])) {
        throw "ERROR: parameter illegal[-m]";
    } else if (params['n'] && (params['m'] || params['w'] || params['c'] ||
                               params['h'] || params['t'] || params['r'])) {
        throw "ERROR: parameter illegal[-n]";
    } else if (params['w'] && params['c']) {
        throw "ERROR: -w and -c cannot be used together.";
    }

}

void inputProcess(int argc, char *argv[]){
    initAlphabet();
    analyzeParam(argc, argv);
    readWordFromFile();
    cout << "======THE END=======" << endl;

}


// 报错

// 主函数（假设）
/*
* int main(int argc, char* argv[]) {
* try {
        func();
    } catch (const char* msg) {
        cout << msg << endl;
    }
	return 0;
}
*/