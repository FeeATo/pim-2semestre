#include <stdio.h>
#include <stdlib.h>
#include "login.h"
#include "menu.h" // for wstring_convert
#include "locale.h"
#define CURSOR_CIMA "\033[A"
#define DELETA_LINHA "\033[0;32m"


void aplicaConfigs();


int main()
{
    aplicaConfigs();
    //a função carregaTelaLogin() retorna 0 se o login for correto e 1 se o usuário errar a senha e não quiser tentar novamente
    int typeUsuario = carregaTelaLogin();
    if(typeUsuario != 0)
        carregaTelaMenu(typeUsuario);

    system("cls");
    printf("\n Tchau! \n");

    return 0;
}

void aplicaConfigs(){
    setlocale ( LC_ALL, "" );
}


