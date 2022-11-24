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

////////////FUN��O PRINCIPAL DO SCRIPT////////////
//carrega a tela de login e atribui os valores de login digitados pelo usu�rio �s vari�veis para serem comparadas
//retorna 0 se o login for correto e 1 se o usu�rio errar a senha e n�o quiser tentar novamente
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
                    //n�o fa�a nada
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
        int userType = checkLogin(login_enter, senha_enter); //fun��o em login.c compara login com todos os salvos. Se n�o corresponder a nenhum, retorna 0, se n�o retorna o tipo do usu�rio
        if(userType!=0){

            printf("\n %s%sLogin correto  \n", CURSOR_CIMA, DELETA_LINHA);
            printf("\033[0m");
            timer_util(1,1); //fun��o em utils.c - conta 1 segundo (primeiro par�metro) e mostra uma mensagem de Loading (booleano segundo par�metro)

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


//checa Login.
//Retornos:
//>0 - correto - retorna tipo do usu�rio
//0 - incorreto
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
    for(i = 0; i< contaLinhasTxt(fp); i++){ //contaLinhasTxt em utils.c

        //a cada linha no arquivo onde os usu�rios s�o guardados, separa os valores da linha, monta uma struct e compara seus valores.

        char *values;
        values = pegaLinhaPorIndex(fp,i); //fun��o em utils.c
        myUser = separaValores(values); //fun��o em login.c

        int loginComp = stringComp(strlen(login),login, myUser.login); //fun��o em utils.c
        int pwdComp = stringComp(strlen(pwd),pwd, myUser.senha); //fun��o em utils.c
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

//retorna o n�mero de caracteres em uma linha
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

//retorna uma struct User com base em uma string recebida
struct User separaValores(char *linha){
    int *tamanhos;
    tamanhos = contaCaracteresCamposLinha(linha); //fun��o em login.c

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


