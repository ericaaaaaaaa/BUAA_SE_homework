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
	//���������������ÿ����ͬ�ġ�ͷβ����ͷ�ĵ�����,����outputWordList
}

void FunctionN_noR() {
	//���DFS��outputWordList��ȡ���е�����
}

void FunctionWC_noR(char head,char tail) {
	//�ҵ����Ϊ0�ġ�ͷβ����Ȼ�������Щ�㣨��ͷβ����ͬ����Ϊ��ͷֻ��һ��)����DijkstraѰ�����
	//W����Ϊ�����б��ȣ�C����Ϊ������ĸ�ܳ�
}


//  aaa ab�� m��Ч
//�����N_noR��ͬ

void FunctionM() {
	//�ҵ����Ϊ0�ġ�ͷβ����Ȼ�������Щ�㣨��ͷβ����ͬ����Ϊ��ͷֻ��һ��)����DijkstraѰ�����
	//����Ϊ�����б���
}

