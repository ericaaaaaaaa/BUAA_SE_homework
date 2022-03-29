#include <iostream>
#include <mapidbg.h>
#include "word.h"
#include "inputProcess.h"
#include "Core.h"

using namespace std;
int main() {
    char* input[4] = { "END", "OF", "tHe", "worlD" };
    char* result[4] = { 0 };
    /* 调用Core中封装好的函数 */
    cout << "===========Core Begin==========" << endl;
    int len;
    //Core *core = new Core();
    len = Core::gen_chains_all(input, 4, result);
    //len = core->gen_chains_all(input, 4, result);
    cout << len << endl;
    Assert(len == 1);
    return 0;
}
//int main(int argc, char *argv[]) {
//    try {
//        inputProcess(argc, argv);
//        bool containsLoop = CycleDetection();
//        if (!params['r'] && containsLoop) throw "ERROR: contains loop.";
////        inputProcess(argc, argv);
////        cout << "cycle detection " << CycleDetection() << endl;
////        for (auto iter = outputWordList.begin(); iter != outputWordList.end(); iter++) {
////            cout << (*iter) << " -> ";
////        }
//        if (params['n']) {
//            FunctionN_noR();
//            cout << outputWordList.size() << endl;
//            for (auto iter = outputWordList.begin(); iter != outputWordList.end(); ++iter) {
//                cout << (*iter) << endl;
//            }
//        } else if (!containsLoop) { // 没有环路
//            ofstream outFile;
//            outFile.open("solution.txt", ios::out);
//            if (params['w']) {
//                auto outputWordList = FunctionW_noR();
//                if (outputWordList.size() > 1) {
//                    for (auto iter = outputWordList.begin(); iter != outputWordList.end(); ++iter) {
//                        outFile << (*iter) << endl;
//                        cout << (*iter) << endl;
//                    }
//                }
//            } else if (params['c']) {
//                auto outputWordList = FunctionC_noR();
//                if (outputWordList.size() > 1) {
//                    for (auto iter = outputWordList.begin(); iter != outputWordList.end(); ++iter) {
//                        outFile << (*iter) << endl;
//                        cout << (*iter) << endl;
//                    }
//                }
//            }
//            outFile.close();
//        } else { // 有环路
//            ofstream outFile;
//            outFile.open("solution.txt", ios::out);
//            if (params['w']) {
//                auto outputWordList = FunctionW_R();
//                if (outputWordList.size() > 1) {
//                    for (auto iter = outputWordList.begin(); iter != outputWordList.end(); ++iter) {
//                        outFile << (*iter) << endl;
//                        cout << (*iter) << endl;
//                    }
//                }
//            } else if (params['c']) {
//                auto outputWordList = FunctionC_R();
//                if (outputWordList.size() > 1) {
//                    for (auto iter = outputWordList.begin(); iter != outputWordList.end(); ++iter) {
//                        outFile << (*iter) << endl;
//                        cout << (*iter) << endl;
//                    }
//                }
//            }
//            outFile.close();
//        }
//    } catch (const char *msg) {
//        cout << msg << endl;
//    }
//    return 0;
//}
