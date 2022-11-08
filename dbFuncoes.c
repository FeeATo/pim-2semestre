#include "utils.h"


//retorna 1 se deu certo e 0 se deu erro
int salvaLinhaNoArquivo(char *linha, FILE *fp){

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    int result;
    fputs("\n", fp);
    result = fputs(linha,fp);
    if(result!=EOF)
        return 1;

    return 0;
}
