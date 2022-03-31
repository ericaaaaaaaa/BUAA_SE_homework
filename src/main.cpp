#include <iostream>
#include "word.h"
#include "inputProcess.h"
#include "Core.h"
#include <mapidbg.h>
#include <cassert>

using namespace std;

//#define L 4
//int main() {
//    const char * input0[L] = {"end", "OF", "the", "World"};
//    char *input[L];
//    char* result[4] = {nullptr };
//    for(int i = 0; i < L; i++){
//        input[i] = (char *)input0[i];
//    }
//    cout << "===========Core Begin==========" << endl;
//    int len;
//    len = Core::gen_chain_word_unique(input, 4, result);
//    //len = Core::gen_chain_word(input, 4, result,0,0,true);
//    if(len < 0){
//        return -1;
//    }
//    cout << len << endl;
//    auto iter = outputWordList.begin();
//    for (int i = 0; i < len;iter++, i++) {
//        cout << *iter << endl;
//    }
//    assert(len == 2);
//    return 0;
//}
int main(int argc, char *argv[]) {
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
        } else if (!containsLoop) { // 没有环路
            ofstream outFile;
            outFile.open("solution.txt", ios::out);
            if (params['w']) {
                FunctionWC_noR();
                //auto outputWordList = FunctionW_noR();
            } else if (params['c']) {
                FunctionWC_noR();
                //auto outputWordList = FunctionC_noR();
            } else if(params['m']) {
                FunctionM();
            }
            if (outputWordList.size() > 1) {
                for (auto iter = outputWordList.begin(); iter != outputWordList.end(); ++iter) {
                    outFile << (*iter) << endl;
                    cout << (*iter) << endl;
                }
            }
            outFile.close();
        } else { // 有环路
            ofstream outFile;
            outFile.open("solution.txt", ios::out);
            if (params['w']) {
                outputWordList = FunctionW_R();
            } else if (params['c']) {
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
    } catch (const char *msg) {
        cout << msg << endl;
    }
    return 0;
}
