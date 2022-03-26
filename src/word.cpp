#include "iterator"
#include "word.h"
bool reset;
list<string> outputWordList;
void resetDirty() {
	for (auto iter = dirty.begin(); iter != dirty.end(); iter++) {
		iter->second = false;
	}
}
void DFS() {
	//深度优先搜索出以每个不同的“头尾”开头的单词链,放入outputWordList
}

void FunctionN_noR() {
	//配合DFS用outputWordList获取所有单词链
}

void FunctionWC_noR(char head,char tail) {
	//找到入度为0的“头尾”，然后遍历这些点（“头尾”相同的作为开头只找一次)，用Dijkstra寻找最大
	//W长度为单词列表长度，C长度为单词字母总长
}


//  aaa ab， m生效
//此外和N_noR相同

void FunctionM() {
	//找到入度为0的“头尾”，然后遍历这些点（“头尾”相同的作为开头只找一次)，用Dijkstra寻找最大
	//长度为单词列表长度
}

#include "inputProcess.h"

int main(int argc, char* argv[]) {
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
                    cout << "alphabet[" << char('a' + i) << "][" << char('a' + j) << "]: " << (*iter)->wordContent << "\tLength: " << (*iter)->wordLength << endl;
                }
            }
        }
        cout << "======THE END=======" << endl;
    } catch (const char* msg) {
        cout << msg << endl;
    }
}