#include "utils.h"
#include "menuCadastro.h"
#include "menuConsultas.h"
#include "menuGerenciamento.h"

int testaValidadeDaOpcao(int opcao);
int direcionaParaOpcaoDesejada(int telaCod, int typeUser);

////////////FUN��O PRINCIPAL////////////
//carrega a tela de menu com todas as op��es. Verifica se op��o digitada � v�lida e direciona para ela.
void carregaTelaMenu(int typeUser){
    int telaCod=-1;
    while(1){
        system("cls");
        printf("\n =================== Menu =================== \n ");

        escreveOpcoesDeNavegacao(); //fun��o em menu.c - escreve op��es na tela
        printf("\n\n Digite o n�mero da tela que deseja acessar: ");

                    //fun��o em utils.c intASCIIToInt: converte caracteres num�ricos com c�digos da tabela ASCII em inteiros
        telaCod = intASCIIToInt(getOneIntegerOnly()); //fun��es em utils.c - getOneIntegerOnly: apenas aceita um �nico n�mero. N�o aceita letras.

        int validoOuInvalido = testaValidadeDaOpcao(telaCod); //fun��o em menu.c - testa se op��o digitada � v�lida

        if(validoOuInvalido==0){ //se op��o for v�lida, redireciona para a pr�xima tela.
            int result = direcionaParaOpcaoDesejada(telaCod, typeUser);
            if(result==-1) continue;
            break;
        } else{
            printf(" \n \033[0;31mOP��O INV�LIDA!");
            timer_util(1, 0); //conta 1 segundo e n�o mostra mensagem de Loading
            printf("\033[0m");
            continue;
        }


    }

    printf("\n\n");
    system("pause");
}

int testaValidadeDaOpcao(int opcao){
    switch(opcao){
        case 1: return 0;
        case 2: return 0;
        case 3: return 0;
        default: return 1;
    }
}

int direcionaParaOpcaoDesejada(int telaCod, int typeUser){
    int result = 0;
   switch(telaCod){
        case 1:
            result = telaCadastro(typeUser); //fun��o em menuCadastro.c
            if(result==-1)
                return result;
            break;
        case 2:
            result = telaConsultas(typeUser); //fun��o em menuConsultas.c
            if(result==-1)
                return result;
            break;
        case 3:
            if(typeUser!=3){
                printaUsuarioSemPrivilegioMessage(); //caso usu�rio n�o tenha privil�gio suficiente, mostrar mensagem
                return -1;
            }
            result = telaGerenciamento(); //fun��o em menuGerenciament.c
            if(result==-1)
                return result;
            break;
        default:
            excluiLinha(1); //fun��o em utils.c - exclui do console o n�mero de linhas passado como par�matro
            break;
    }
}

void escreveOpcoesDeNavegacao(){
    printf("\n 1. Cadastrar novo usu�rio");
    printf("\n 2. Consultas");
    printf("\n 3. Gerenciamento");
}
