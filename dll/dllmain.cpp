// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "Core.h"
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
/*
int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop)
{
    return gen_chain_word0(words, len, result, head, tail, enable_loop);
}
//2.函数返回所有符合定义的单词链，函数返回值为单词链的总数
int gen_chains_all(char* words[], int len, char* result[])
{
    return gen_chains_all0(words, len, result);

}
//3.函数返回首字母不同的，单词数最多的单词链，函数返回值为单词链的长度
int gen_chain_word_unique(char* words[], int len, char* result[])
{
    return gen_chain_word_unique0(words, len, result);

}
//4.计算最多字母数量的最长单词链
int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop)
{
    return gen_chain_char0(words, len, result, head, tail, enable_loop);

}
*/
