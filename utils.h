#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

//dando erro, precisa aprender ponteiros pra retornar esse array!!
//char[] atribuiArray(char[] target, char[] str, int size);
int timer_util(int secs, int withLoadingMessage);
void excluiLinha(int x);
int getIntegerOnly();
int intASCIIToInt(int);
int contaLinhasTxt(FILE *);
char *pegaLinhaPorIndex(FILE *, int);
#endif // UTILS_H_INCLUDED
