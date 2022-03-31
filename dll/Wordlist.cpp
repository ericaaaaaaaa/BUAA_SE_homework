#include <windows.h>
#include <iostream>
#include <assert.h>
#include "Windows.h"
#include "tchar.h"
using namespace std;

typedef int(*functionN)(char* words[], int len, char* result[]);
typedef int(*functionM)(char* words[], int len, char* result[]);
typedef int(*functionW)(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
typedef int(*functionC)(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
#define L 4
int main(){
	const char * input0[L] = {"end", "OF", "the", "World"};
    char *input[L];
    char* result[4] = {0};
    for(int i = 0; i < L; i++){
        input[i] = (char *)input0[i];
    }
	cout << "==========begin===========" << endl;
	functionN N = NULL;
	string str = "./core.dll";
	LPCSTR path = str.c_str();
	
	HMODULE hModule; 
	hModule = LoadLibrary(_T("core.dll"));
	
	//cout<<GetLastError()<<endl;
	
	/*
	if(hModule == NULL){
		cout << "fucking"<<endl;
	}	
	N = (functionN)GetProcAddress(hModule,"gen_chains_all");
	if(N==NULL){
		cout << "liekai"<<endl;
	}else{
		int x = N(input, 4, result);
	}
	*/
	
	//N = (functionN)GetProcAddress(hModule,"gen_chains_all");
	//int len = N(input, 4, result);
	
	//functionM M = (functionM)GetProcAddress(hModule,"gen_chain_word_unique");
	//int len = M(input, 4, result);

//	functionW W = (functionW)GetProcAddress(hModule,"gen_chain_word");
//	int len = W(input, 4, result,0,0,false);

	functionC C = (functionC)GetProcAddress(hModule,"gen_chain_char");
	int len = C(input, 4, result,0,0,false);
	
	cout <<  len << endl; 
    for (int i = 0; i < len;i++) {
    	string tmp = result[i];
        cout << tmp << endl;
    }
    assert(len == 2);
	cout << "===========end============" << endl;
	//assert(len == 1);
	return 0;
}
