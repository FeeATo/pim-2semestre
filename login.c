#include "utils.h"

const char LOGIN[10] = "TEST";
const char PASSWORD[10] = "1234";

char login_enter[10] = "";
char senha_enter[10] = "";



//carrega a tela de login e atribui os valores de login digitados pelo usuário às variáveis para serem comparadas
void carregaTelaLogin(){
    system("cls");
    printf("\n ========== Login ========== \n \n");
    printf(" Login: ");
    gets(login_enter);

    printf(" Senha: ");
    gets(senha_enter);



    //maskPassword();
    timer_util(1);
    int check = checkLogin(login_enter, senha_enter);
    if(check==1)
        printf("certo");
    else{
        if(check==2) printf(" \033[0;31m Login incorreto!\n");
        else if(check==3) printf(" \033[0;31m Senha incorreta!\n");

        printf("\n \033[0m Deseja tentar novamente? (s/n) \n");
        //CONTINUAR ADQUI, CRIAR MÉTODO QUE MUDA A COR DA TELA E SE ACEITA TENTAR NOVAMENTE OU NÃO
    }


    printf("\n =========================== \n");

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


