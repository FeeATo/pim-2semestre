#include "utils.h"


int salvaLinhaNoArquivo(char *linha, FILE *fp){
    char *linha2 = &linha;
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return 0;
    }

    int result;
    result = fputs(linha2,fp);
    if(result!=EOF)
        return 1;

    return 0;
}
