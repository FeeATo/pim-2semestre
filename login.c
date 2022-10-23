#include "utils.h"
#include "stdlib.h"
#define CURSOR_CIMA "\033[A"
#define DELETA_LINHA "\033[0;32m"

const char LOGIN[10] = "TEST";
const char PASSWORD[10] = "1234";
const int ID_USER = 1;

char login_enter[10] = "";
char senha_enter[10] = "";



//carrega a tela de login e atribui os valores de login digitados pelo usuário às variáveis para serem comparadas
int carregaTelaLogin(){
    while(1){
        system("cls");
        printf("\n ========== Login ========== \n \n");
        printf(" Login: ");
        gets(login_enter);

        printf(" Senha: ");
        int i=0;
        char ch;
        while(1) {
            ch=getch();
            if(ch==13){
               break;
            } else{
                if(ch==8) {
                        senha_enter[i];
                        i--;
                        printf("\b \b");
                } else{
                    senha_enter[i] = ch;
                    i++;
                    printf("*");
                }
            }
        }
        senha_enter[i++] = '\0';
        printf("\n");


        //maskPassword();
        timer_util(2, 1);
        int check = checkLogin(login_enter, senha_enter);
        if(check==1){

            printf("\n %s%sLogin correto  \n", CURSOR_CIMA, DELETA_LINHA);
            printf("\033[0m");
            timer_util(1,1);

            return ID_USER;
            break;
        }
        else{
            char teclaApertada;

            if(check==2) printf(" \033[0;31mLogin incorreto!\n");
            else if(check==3) printf("\033[0;31m Senha incorreta!\n");

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

    int loginComp = stringComp(10,login, LOGIN);
    int pwdComp = stringComp(10,pwd, PASSWORD);
    if(loginComp == 1 && pwdComp == 1){
        return 1;
    } else{
        if(loginComp!=1) return 2;
        if(pwdComp!=1) return 3;
    }
    return 0;


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


