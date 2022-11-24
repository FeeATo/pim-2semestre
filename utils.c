#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define CURSOR_CIMA "\033[A"
#define DELETA_LINHA "\033[0;32m"
#define TEXTO_VERMELHO "\033[31m"
#define TEXTO_PRETO "\033[0m"
#define TEXTO_VERDE "\033[32m"



//atribui valor a uma String com base em outra String, n�o funciona ainda pq n�o sei ponteiros
/*char[20] atribuiArray(char target[20], char str[20], int size){

    for(int i = 0; i<size; i++){
        target[i] = str[i];
    }

    return target;

}*/

struct UsuarioUtils{
    char *login;
    int type;
    char *nome;
    char *sobrenome;
    long long int cpf;
};

struct Cliente{
    int id;
    long long int cnpj;
    char *nome;
    char *email;
    long long int telefone;
};

//l� apenas um n�mero
int getOneIntegerOnly()
{
    //printf("%s", );
    int allowdBackspaces=0;
    int num = 0, ch;
    int reps=0;
     while(1) {
        ch=getch();
        if(ch==13){
           return num;
        } else{
            if(ch==8) {
                if(allowdBackspaces==1){
                    printf("\b \b");
                    allowdBackspaces=0;
                }
                reps=-1;
            } else{
                if(ch>=48 && ch<=57){
                    num = ch;
                    if(reps>0){
                        printf("\b");
                    }
                    printf("%c", ch);
                    allowdBackspaces=1;
                }
            }
        }
        reps++;
    }

    return (num);
}


//l� apenas n�meros
int getIntegerOnly()
{
    //printf("%s", );
    int allowdBackspaces=0;
    int num = 0, ch;
    int reps=0;
     while(1) {
        ch=getch();
        if(ch==13){
           return num;
        } else{
            if(ch==8 && allowdBackspaces>0) {
                printf("\b \b");
                allowdBackspaces--;

            } else{
                if(ch>=48 && ch<=57){
                    num = ch;
                    printf("%c", ch);
                    allowdBackspaces++;
                }
            }
        }
        reps++;
    }

    return (num);
}

//retorna o n�mero de digitos em um long long int
int getNumberOfDigitsInLongLongInt(long long int number){
    int count=0;

    while(number!=0){
        number=number/10;
        count++;
    }

    return count;
}

//retorna o n�mero de digitos em um int
int getNumberOfDigitsInInt(int number){
    int count=0;

    while(number!=0){
        number=number/10;
        count++;
    }

    return count;
}

//l� senha e esconde caracteres digitados
char *readPasswordAndMaskDigited(){
    char senha[10];
    char ch;
    int i =0;
    int allowedBackspaces=0;
    while(1) {
        ch=getch();
        if(ch==13){
            break;
        } else{
            if(ch==8 && allowedBackspaces>0) {
                i--;
                allowedBackspaces--;
                printf("\b \b");
            } else if(ch==8 && allowedBackspaces==0){
                    //n�o fa�a nada
            } else{
                    *(senha+1) = ch;
                    i++;
                    allowedBackspaces++;
                    printf("*");
            }
        }
    }

    return senha;
}


//retorna n�mero da tabela ASCII se digitado "s" ou "n"
int getSimOuNao(){
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

//retorna 1 se for digitado "s" e 0 se for digitado "n"
int getSimOuNaoInt() {
    //printf("%s", );
    int num = 0, ch;
     while(1) {
        ch=getch();
        if(ch==13){
           return intYesOrNoFromCharInt(num);
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

    return -1;
}

//retorna um n�mero 0 se op��o digitada � "n" e 1 se "s"
int intYesOrNoFromCharInt(int num){
    if(num==110) return 0;
    else return 1;
}

//retorna o valor inteiro correspondente ao n�mero da tabela ASCII de um inteiro
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

//retorna o valor da tabela ASCII de um n�mero inteiro
char intToIntASCII(int integer){
    switch(integer){
        case 0: return 48;
        case 1: return 49;
        case 2: return 50;
        case 3: return 51;
        case 4: return 52;
        case 5: return 53;
        case 6: return 54;
        case 7: return 55;
        case 8: return 56;
        case 9: return 57;
    }
}

//limpa tela toda
void limpaTela(){
    system("cls");
}


//exclui do console o n�mero de linhas passado como par�metro
void excluiLinha(int x){
    for(int i = 0; i<x; i++){
        printf("\033[A\33[2K");
    }
}

//retorna uma linha com base em um index da linha
char *pegaLinhaPorIndex(FILE *fp, int index){
    char c;
    int count=0;
    char *retorno;
    if (fp == NULL)
    {
        printf("Could not open file");
        return 0;
    }

    int i=0;

    //volta o cursor ara o in�cio do arquivo
    // Extract characters from file and store in character c
    int normalCaracter=0;
    int indexFimDaLinha;

    while((c = fgetc(fp))!=EOF){
        if (c == '\n'){
            // Increment count if this character is newline
            if(count==index){
                break;
            }
            count++;
            normalCaracter=0;
        }
        else {
            normalCaracter++;
            indexFimDaLinha=normalCaracter;
        }
    }

    char *linhaCerta = malloc(indexFimDaLinha);

    rewind(fp);
    count=0;
    while((c = fgetc(fp))!=EOF){
        // Increment count if this character is newline
        if(count==index){
            *(linhaCerta+i) = c;
            if(i==indexFimDaLinha){
                break;
            }
            i++;
        }
        if (c == '\n'){
            count++;
        }


    }

    rewind(fp);
    return linhaCerta;
}

char *pegaTamanhoLinhaPorIndex(FILE *fp, int index){
    char c;
    int count=0;
    char *retorno;
    if (fp == NULL)
    {
        printf("Could not open file");
        return 0;
    }

    int i=0;

    //volta o cursor ara o in�cio do arquivo
    // Extract characters from file and store in character c
    int normalCaracter=0;
    int indexFimDaLinha;

    while((c = fgetc(fp))!=EOF){
        if (c == '\n'){
            // Increment count if this character is newline
            if(count==index){
                break;
            }
            count++;
            normalCaracter=0;
        }
        else {
            normalCaracter++;
            indexFimDaLinha=normalCaracter;
        }
    }

    char linhaCerta[normalCaracter];

    rewind(fp);
    count=0;
    while((c = fgetc(fp))!=EOF){
        // Increment count if this character is newline
        if(count==index){
            linhaCerta[i] = c;
            if(i==indexFimDaLinha){
                linhaCerta[i+1] = '\n';
                break;
            }
            i++;
        }
        if (c == '\n'){
            count++;
        }

    }

    rewind(fp);
    return i+1;
}

//retorna o n�mero de linhas em um arquivo .txt. Ponteiro passado como par�metro
int contaLinhasTxt(FILE *fp){
    char c;
    int count=0;
    if (fp == NULL)
    {
        printf("Could not open file");
        return 0;
    }

    // Extract characters from file and store in character c
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            count++;

    // Close the file

    rewind(fp);

    return count+1;
}

//timer - conta o n�mero de segundos e mostra mensagem de Loading ou n�o
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

//sobe cursor a qntd passada como par�metro
void sobeLinha(int qntd){
    for(int i=0; i<qntd; i++)
        printf(CURSOR_CIMA);
}

//compara tamanho de strings
//Se strings tem tamanhos diferentes -> retorna -1, n�o podem ser comparadas
//Se strings tem tamanhos iguais e s�o iguais -> retorna 1
//Se string tem tamanhos iguais mas s�o diferentes -> retorna 0
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

//conta caracteres em uma linha
int contaCaracters(char *p){
    int count=0;
    char *p1 = p;
    while(*(p1+count)!='\n'){
        count++;
    }

    return count;
}

//retorna nome do tipo com base em seu ID
char *getTypeCadastro(int type){

    switch(type){
        case 1: return "Funcion�rio";
        case 2: return "Administrador";
    }

    return NULL;
}

//retorna nome do tipo com base em seu ID
char *getTypeCadastroToPointer(int type, char *pointer){

    switch(type){
        case 1: return strcpy(pointer,"Funcion�rio");
        case 2: return strcpy(pointer,"Administrador");
    }

    return pointer;
}

//imprime mensagem
void printaUsuarioSemPrivilegioMessage(){
    printf(" \n \033[0;31mACESSO NEGADO, USU�RIO SEM PRIVIL�GIO. \033[0m");
    timer_util(2, 0);
    excluiLinha(2);
}

//abre diret�rio explorador de arquivos
void openDirectory(char *endereco){
    char command[40]="start \"\" \"";
    strcat(command, endereco);
   system(command);
}

//conta n�mero de digitados em um inteiro
int contaCasasDecimais(int number){
    int count = 1;
    while((number/10)>0){
        count++;
        number/=10;
    }


    return count;
}

//conta n�mero de digitados em um inteiro
int contaCasasDecimaisLong(long long int number){
    int count = 1;
    while((number/10)>0){
        count++;
        number/=10;
    }


    return count;
}
