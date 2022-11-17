#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#define CURSOR_CIMA "\033[A"
#define DELETA_LINHA "\033[0;32m"


const char LOGIN[10] = "TEST";
const char PASSWORD[10] = "1234";
const int typeUser = 1;

struct User{
    char *login;
    char *senha;
    int type;
};

char login_enter[10] = "";
char senha_enter[10] = "";

struct User separaValores(char *linha);


int typeLogin;

//carrega a tela de login e atribui os valores de login digitados pelo usuário às variáveis para serem comparadas
int carregaTelaLogin(){
    while(1){
        system("cls");
        printf("\n ========== Login ========== \n \n");
        printf(" Login: ");
        gets(login_enter);
        fflush(stdin);

        printf(" Senha: ");
        int i=0;
        char ch;
        int allowedBackspaces=0;
        while(1) {
            ch=getch();
            if(ch==13){
               break;
            } else{
                if(ch==8 && allowedBackspaces>0) {
                        senha_enter[i];
                        i--;
                        allowedBackspaces--;
                        printf("\b \b");
                } else if(ch==8 && allowedBackspaces==0){
                    //não faça nada
                } else{
                    senha_enter[i] = ch;
                    i++;
                    allowedBackspaces++;
                    printf("*");
                }
            }
        }
        senha_enter[i++] = '\0';
        printf("\n");


        //maskPassword();
        timer_util(2, 1);
        int userType = checkLogin(login_enter, senha_enter);
        if(userType!=0){

            printf("\n %s%sLogin correto  \n", CURSOR_CIMA, DELETA_LINHA);
            printf("\033[0m");
            timer_util(1,1);

            return userType;
            break;
        }
        else{
            char teclaApertada;

            printf(" \033[0;31mLogin ou senha incorretos!\n");


            char opcaoDigitada=-1;
            while(1){
                printf("\n\033[0m Deseja tentar novamente (s/n)? ");
                teclaApertada = getSimOuNao();
                if(teclaApertada=='s') break;
                else
                    return 0;

            }

        }
    }

    printf("\33[2K\r");
    printf(" =========================== \n \n");

}



//chega Login.
//Retornos:
//1 - correto
//2 - login incorreto
//3 - senha incorreta
int checkLogin(char login[10], char pwd[10]){

    FILE *fp = fopen(".\\DB\\loginCredentials.txt", "r");
    if(fp==NULL){
        printf("Erro ao acessar arquivo");
        timer_util(1,0);
        exit(1);
    }


    int i = 0;
    char ch;
    struct User myUser;
    for(i = 0; i< contaLinhasTxt(fp); i++){

        char *values;
        values = pegaLinhaPorIndex(fp,i);
        myUser = separaValores(values);

        int loginComp = stringComp(strlen(login),login, myUser.login);
        int pwdComp = stringComp(strlen(pwd),pwd, myUser.senha);
        if(loginComp == 1 && pwdComp == 1){
            fclose(fp);
            typeLogin = myUser.type;
            return myUser.type;
        } else{
            continue;
        }
    }
    return 0;


}

int *contaCaracteresCamposLinha(char *linha){
    static int caracteres[3];
    int count;
    int caractereIndex=0;
    for(int i=0; linha[i]!='\0'; i++){

        if(linha[i]!=';'){
            count++;
            if(caractereIndex==2){
                caracteres[2]=intASCIIToInt(linha[i]);
                return caracteres;
            }
        } else{
            caracteres[caractereIndex]=count;
            count=0;
            caractereIndex++;
        }

    }

    return caracteres;
}

struct User separaValores(char *linha){
    int *tamanhos;
    tamanhos = contaCaracteresCamposLinha(linha);

    int tamanhoTotal = (*tamanhos)+(*(tamanhos+1))+3;
    char login[*tamanhos];
    int tamanhoLogin = *tamanhos;
    //login = malloc(sizeof(char) * tamanhoLogin);
    char senha[(*(tamanhos+1))];
    //senha = malloc(sizeof(char) * (*(tamanhos+1)));
    int type;
    int indexAux=0;
    int countCommas=0;
    int cursor=0;
    int aux=0;
    for(int i=0; i<tamanhoTotal; i++){
        if(linha[i]!=';'){
            if(countCommas==0){
                *(login+aux) = *(linha+i);
            } else if(countCommas==1){
                *(senha+aux) = *(linha+i);
            } else if(countCommas==2) {
                type = intASCIIToInt(linha[i]);
            }
        } else{
            aux=-1;
            countCommas++;
        }
        aux++;
    }

    struct User myUser = {login, senha, type};

    return myUser;
}

/*char[10] maskPassword(){
    int i = 0;
    char ch;
    char pwd[10];
    while((ch = _getch())!=10){
        pwd[i] = ch;
        i++;
        printf("*");
    }
    pwd[i] = '\0';
    return pwd;
}*/


