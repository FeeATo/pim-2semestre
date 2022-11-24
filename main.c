#include <stdio.h>
#include <stdlib.h>
#include "login.h"
#include "menu.h" // for wstring_convert
#include "locale.h"
#define CURSOR_CIMA "\033[A"
#define DELETA_LINHA "\033[0;32m"

void aplicaConfigs();

/*
    _______________________________________________________________________________
   |               PROGRAMA DESENVOLVIDO POR MIGUEL ALOTA TELES                    |
   |        linkedin: https://www.linkedin.com/in/miguel-teles-6a9b161b0/          |
   |_____________________ email: miguelteles2002@gmail.com ________________________|

   23/11/2022

*/

int main()
{
    aplicaConfigs();

    int typeUsuario = carregaTelaLogin(); //função em login.c
    if(typeUsuario != 0)
        carregaTelaMenu(typeUsuario); //função em menu.c

    system("cls");
    printf("\n Tchau! \n");

    return 0;
}

//muda locale para aparecer acentos nos textos
void aplicaConfigs(){
    setlocale ( LC_ALL, "" );
}


