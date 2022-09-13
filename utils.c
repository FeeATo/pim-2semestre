#include "time.h"
#include <string.h>

//atribui valor a uma String com base em outra String, não funciona ainda pq não sei ponteiros
/*char[20] atribuiArray(char target[20], char str[20], int size){

    for(int i = 0; i<size; i++){
        target[i] = str[i];
    }

    return target;

}*/

void timer_util(int secs) {
    time_t start, end;
    double elapsed;

    time(&start);  /* start the timer */
    printf(" Loading...");
    do {
        time(&end);

        elapsed = difftime(end, start);
        /* For most data types one could simply use
            elapsed = end - start;
            but for time_t one needs to use difftime(). */


    } while(elapsed < secs);  /* run for ten seconds */
    printf("\r           \n");
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

