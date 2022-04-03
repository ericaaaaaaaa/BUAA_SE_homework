#include "word.h"
#include "inputProcess.h"
#include <assert.h>
#include <iostream>
#include "string"


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