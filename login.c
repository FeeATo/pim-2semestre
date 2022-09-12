#include "utils.h"

const char LOGIN[10] = "TEST";
const char PASSWORD[10] = "1234";

char login_enter[10] = "";
char senha_enter[10] = "";



//carrega a tela de login e atribui os valores de login digitados pelo usuário às variáveis para serem comparadas
void carregaTelaLogin(){
    printf("\n ========== Login ========== \n \n");
    printf("Login: ");
    gets(login_enter);

    printf("senha: ");


    //maskPassword();

    printf("%s", senha_enter);

    printf("\n =========================== \n");
}

private char[10] maskPassword(){
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
}


