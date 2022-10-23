#include "time.h"
#include <string.h>

//atribui valor a uma String com base em outra String, não funciona ainda pq não sei ponteiros
/*char[20] atribuiArray(char target[20], char str[20], int size){

    for(int i = 0; i<size; i++){
        target[i] = str[i];
    }

    return target;

}*/

int getIntegerOnly()
{
    //printf("%s", );
    int num = 0, ch;
     while(1) {
        ch=getch();
        if(ch==13){
           return num;
        } else{
            if(ch==8) {
                    printf("\b \b");
            } else{
                if(ch>=48 && ch<=57){
                    num = ch;
                    printf("%c", ch);
                }
            }
        }
    }

    return (num);
}

int getSimOuNao()
{
    //printf("%s", );
    int num = 0, ch;
     while(1) {
        ch=getch();
        if(ch==13){
           return num;
        } else{
            if(ch==8) {
                    printf("\b \b");
            } else{
                if(ch=='s' || ch=='n'){
                    num = ch;
                    printf("%c", ch);
                }
            }
        }
    }

    return (num);
}

int intASCIIToInt(int intAsc){
    switch(intAsc){
        case 48: return 0;
        case 49: return 1;
        case 50: return 2;
        case 51: return 3;
        case 52: return 4;
        case 53: return 5;
        case 54: return 6;
        case 55: return 7;
        case 56: return 8;
        case 57: return 9;
    }
}

void limpaTela(){
    system("cls");
}

void excluiLinha(int x){
    for(int i = 0; i<x; i++){
        printf("\033[A \33[2K");
    }
}

void timer_util(int secs, int withLoaingMessage) {
    time_t start, end;
    double elapsed;

    time(&start);  /* start the timer */
    if(withLoaingMessage==1) printf("\n Loading...");
    do {
        time(&end);

        elapsed = difftime(end, start);
        /* For most data types one could simply use
            elapsed = end - start;
            but for time_t one needs to use difftime(). */


    } while(elapsed < secs);  /* run for ten seconds */
    if(withLoaingMessage==1)printf("\033[A \33[2K\r         \n");
}

//compara tamanho de strings
//Se strings tem tamanhos diferentes -> retorna -1, não podem ser comparadas
//Se strings tem tamanhos iguais e são iguais -> retorna 1
//Se string tem tamanhos iguais mas são diferentes -> retorna 0
int stringComp(int size, char str1[], char str2[]){

    int count=0;
    if(strlen(str1) != strlen(str2))
        return -1;

    for(int i = 0; i<size; i++){
        if(str1[i]==str2[i]) count++;
    }

    int ret=0;
    ret = size == count ? 1 : 0;
    return ret;
}

