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