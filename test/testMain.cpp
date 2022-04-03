#include "word.h"
#include "inputProcess.h"
#include <assert.h>
#include <iostream>
#include "string"
#include "Core.h"


int times;
char** input;
char* result[20000] = { 0 };
char** refAns;
int len;
int inLen;
int refLen;

using namespace std;


void check(int refLen, char* refAns[]) {
	cout << len << endl;
	if (true) {
		for (int i = 0; i < len; i++) {
			const char* tmpRes = result[i];
			cout << tmpRes << endl;
		}
	}
	else {
		assert(refLen == len);
		for (int i = 0; i < len && i < refLen; i++) {
			const char* tmpRef = refAns[i];
			const char* tmpRes = result[i];
			assert(strcmp(tmpRef, tmpRes) == 0);
			cout << tmpRes << endl;
		}
	}
	cout << "--------times " << times << " end ----" << endl;
	times++;
	len = 0;
}

void init(char** inputw, int inLenw) {
	/*for (int i = 0; i < inLenw; i++) {
		string tmpInput = inputw[i];
		int length = (int)tmpInput.length()+1;
		char* wordContent0 = (char*)malloc(sizeof(char) * 1024);
		int j = 0;
		if(wordContent0!=0)strcpy_s(wordContent0, length, tmpInput.data());
		length--;
		input[i] = wordContent0;
	}*/
	input = inputw;
	inLen = inLenw;
}


int main() {
	cout << "===========TEST BEGIN============" << endl;
	input = (char**)malloc(sizeof(char*) * 20000);
	/*-------N-------*/
	cout << "-----------TEST N--------------" << endl;
	times = 0;

	const int inLenN0 = 4;
	const char* inputN0[inLenN0] = { "aend", "OF", "thea", "World" };
	const int refLenN0 = 1;
	const char* refAnsN0[refLenN0] = { "thea aend" };
	init((char**)inputN0, inLenN0);
	len = Core::gen_chains_all(input, inLen, result);
	check(refLenN0, (char**)refAnsN0);


	/*-------M/N-------*/
	cout << "-----------TEST M/N--------------" << endl;
	times = 0;

	const int inLenN1 = 10;
	const char* inputN1[inLenN1] = { "ab", "bc", "cd", "de", "af", "fg", "gh", "aa", "kk", "lmopq" };
	const int refLenN1 = -1;//如果懒得写答案了
	const char* refAnsN1 = NULL;//如果懒得写答案了
	init((char**)inputN1, inLenN1);
	len = Core::gen_chains_all(input, inLen, result);
	check(-1, NULL);
	len = Core::gen_chain_word_unique(input, inLen, result);
	check(-1, NULL);


	const int inLenN2 = 7;
	const char* inputN2[inLenN2] = { "ab", "bcbc", "dcd", "ede", "faf", "gfg", "hgh" };
	const int refLenN2 = -1;//如果懒得写答案了
	const char* refAnsN2 = NULL;//如果懒得写答案了
	init((char**)inputN2, inLenN2);
	len = Core::gen_chains_all(input, inLen, result);
	check(-1, NULL);
	len = Core::gen_chain_word_unique(input, inLen, result);
	check(-1, NULL);

	const int inLenN3 = 6;
	const char* inputN3[inLenN3] = { "ba", "ab","ca","ammmmmc","cb","bc" };
	const int refLenN3 = -1;//如果懒得写答案了
	const char* refAnsN3 = NULL;//如果懒得写答案了
	init((char**)inputN3, inLenN3);;
	len = Core::gen_chains_all(input, inLen, result);
	check(-1, NULL);
	len = Core::gen_chain_word_unique(input, inLen, result);
	check(-1, NULL);


	/*----------M-----------*/
	const int inLenM0 = 10;
	const char* inputM0[inLenM0] = { "ab", "bc", "cd", "de", "af", "fg", "gh", "aa", "kk", "lmopq" };
	const int refLenM0 = 4;
	const char* refAnsM0[refLenM0] = { "ab","bc","cd","de" };
	init((char**)inputM0, inLenM0);
	len = Core::gen_chain_word_unique(input, inLen, result);
	check(refLenM0, (char**)refAnsM0);


	/*----------W/C-----------*/
	cout << "-----------TEST W_R--------------" << endl;
	times = 0;

	const int inLenW3 = 2;
	const char* inputW3[inLenW3] = { "aaaaaaaaa","aa" };
	init((char**)inputW3, inLenW3);

	len = Core::gen_chain_word(input, inLen, result, '$', 0, true);
	check(-1, NULL);
	len = Core::gen_chain_word(input, inLen, result, 'b', 0, true);
	check(0, NULL);
	len = Core::gen_chain_word(input, inLen, result, 'a', 'b', true);
	check(-1, NULL);
	len = Core::gen_chain_word(input, inLen, result, 0, 0, false);
	check(-1, NULL);

	len = Core::gen_chain_char(input, inLen, result, '$', 0, true);
	check(-1, NULL);
	len = Core::gen_chain_char(input, inLen, result, 'b', 0, true);
	check(0, NULL);
	len = Core::gen_chain_char(input, inLen, result, 'a', 'b', true);
	check(-1, NULL);
	len = Core::gen_chain_char(input, inLen, result, 0, 0, false);
	check(-1, NULL);


	const int inLenW2 = 4;
	const char* inputW2[inLenW2] = { "aaaa","abbb","bccc","cccca" };
	init((char**)inputW2, inLenW2);

	len = Core::gen_chain_word(input, inLen, result, 'b', 'c', true);
	check(-1, NULL);

	len = Core::gen_chain_char(input, inLen, result, 'b', 'c', true);
	check(-1, NULL);


	const int inLenW0 = 12;
	const char* inputW0[inLenW0] = { "XY","YX","XZ","ZX","YZ","ZY","ax","ay","az","za","ya","xa" };
	init((char**)inputW0, inLenW0);

	len = Core::gen_chain_word(input, inLen, result, 0, 0, true);
	check(-1, NULL);
	len = Core::gen_chain_char(input, inLen, result, 0, 0, true);
	check(-1, NULL);
	len = Core::gen_chain_word(input, inLen, result, 'h', 0, true);
	check(-1, NULL);
	len = Core::gen_chain_word(input, inLen, result, 0, 't', true);
	check(-1, NULL);
	len = Core::gen_chain_word(input, inLen, result, 'y', 0, true);
	check(-1, NULL);
	len = Core::gen_chain_word(input, inLen, result, 0, 'y', true);
	check(-1, NULL);
	len = Core::gen_chain_word(input, inLen, result, 'x', 'y', true);
	check(-1, NULL);
	len = Core::gen_chain_word(input, inLen, result, 'x', 't', true);
	check(-1, NULL);
	len = Core::gen_chain_word(input, inLen, result, 'h', 'y', true);
	check(-1, NULL);
	len = Core::gen_chain_word(input, inLen, result, 0, 0, false);
	check(-1, NULL);
	len = Core::gen_chain_word(input, inLen, result, 'a', 0, true);
	check(-1, NULL);




	len = Core::gen_chain_char(input, inLen, result, 'h', 0, true);
	check(-1, NULL);
	len = Core::gen_chain_char(input, inLen, result, 0, 't', true);
	check(-1, NULL);
	len = Core::gen_chain_char(input, inLen, result, 'y', 0, true);
	check(-1, NULL);
	len = Core::gen_chain_char(input, inLen, result, 0, 'y', true);
	check(-1, NULL);
	len = Core::gen_chain_char(input, inLen, result, 'x', 'y', true);
	check(-1, NULL);
	len = Core::gen_chain_char(input, inLen, result, 'x', 't', true);
	check(-1, NULL);
	len = Core::gen_chain_char(input, inLen, result, 'h', 'y', true);
	check(-1, NULL);
	len = Core::gen_chain_char(input, inLen, result, 0, 0, false);
	check(-1, NULL);
	len = Core::gen_chain_char(input, inLen, result, 'a', 0, true);
	check(-1, NULL);

	cout << "-----------TEST W_NoR--------------" << endl;
	times = 0;

	const int inLenW1 = 10;
	const char* inputW1[inLenW1] = { "ab", "bc", "cd", "de", "af", "fg", "gh", "aa", "kk", "kxxxxxxxxxxxxlmopq" };
	init((char**)inputW1, inLenW1);

	const int refLenW10 = 5;
	const char* refAnsW10[refLenW10] = { "aa","ab", "bc", "cd", "de" };
	len = Core::gen_chain_word(input, inLen, result, 0, 0, false);
	check(refLenW10, (char**)refAnsW10);
	check(-1, NULL);


	const int refLenW11 = 4;
	const char* refAnsW11[refLenW11] = { "aa","ab", "bc", "cd" };
	len = Core::gen_chain_word(input, inLen, result, 0, 'd', true);
	check(refLenW11, (char**)refAnsW11);
	//check(-1, NULL);


	len = Core::gen_chain_word(input, inLen, result, 0, 0, true);
	check(-1, NULL);

	const int refLenW12 = 2;
	const char* refAnsW12[refLenW12] = { "kk", "kxxxxxxxxxxxxlmopq" };
	len = Core::gen_chain_char(input, inLen, result, 0, 0, false);
	check(refLenW12, (char**)refAnsW12);
	len = Core::gen_chain_char(input, inLen, result, 0, 'd', true);
	check(refLenW11, (char**)refAnsW11);
	len = Core::gen_chain_char(input, inLen, result, 0, 0, true);
	check(-1, NULL);




	cout << "===========TEST END============" << endl;

	return 0;
}



/*
int main(int argc, char* argv[]) {
    try {
        inputProcess(argc, argv);
        bool containsLoop = CycleDetection();
        if (!params['r'] && containsLoop) throw "ERROR: contains loop.";
        if (params['n']) {
            FunctionN_noR();
            cout << outputWordList.size() << endl;
            for (auto iter = outputWordList.begin(); iter != outputWordList.end(); ++iter) {
                cout << (*iter) << endl;
            }
        }
        else if (!containsLoop) { // 没有环路
            ofstream outFile;
            outFile.open("solution.txt", ios::out);
            if (params['w']) {
                FunctionWC_noR();
                //auto outputWordList = FunctionW_noR();
            }
            else if (params['c']) {
                FunctionWC_noR();
                //auto outputWordList = FunctionC_noR();
            }
            else if (params['m']) {
                FunctionM();
            }
            if (outputWordList.size() > 1) {
                for (auto iter = outputWordList.begin(); iter != outputWordList.end(); ++iter) {
                    outFile << (*iter) << endl;
                    cout << (*iter) << endl;
                }
            }
            outFile.close();
        }
        else { // 有环路
            ofstream outFile;
            outFile.open("solution.txt", ios::out);
            if (params['w']) {
                outputWordList = FunctionW_R();
            }
            else if (params['c']) {
                outputWordList = FunctionC_R();
            }
            if (outputWordList.size() > 1) {
                for (auto iter = outputWordList.begin(); iter != outputWordList.end(); ++iter) {
                    outFile << (*iter) << endl;
                    cout << (*iter) << endl;
                }
            }
            outFile.close();
        }
    }
    catch (const char* msg) {
        cout << msg << endl;
    }
    return 0;
}
*/