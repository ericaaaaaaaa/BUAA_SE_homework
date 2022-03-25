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

