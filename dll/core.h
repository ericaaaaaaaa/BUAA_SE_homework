#pragma once
#include "word.h"
#include "inputProcess.h"
#include "exceptionPackage.h"

int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
//2.�����������з��϶���ĵ���������������ֵΪ������������
int gen_chains_all(char* words[], int len, char* result[]);
//3.������������ĸ��ͬ�ģ����������ĵ���������������ֵΪ�������ĳ���
int gen_chain_word_unique(char* words[], int len, char* result[]);
//4.���������ĸ�������������
int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);



