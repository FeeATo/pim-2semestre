#include "utils.h"
#include "menuCadastro.h"
#include "menuConsultas.h"
#include "menuGerenciamento.h"

int testaValidadeDaOpcao(int opcao);
int direcionaParaOpcaoDesejada(int telaCod, int typeUser);

void carregaTelaMenu(int typeUser){
    int telaCod=-1;
    while(1){
        system("cls");
        printf("\n =================== Menu =================== \n ");

        escreveOpcoesDeNavegacao();
        printf("\n\n Digite o número da tela que deseja acessar: ");

        telaCod = intASCIIToInt(getOneIntegerOnly());

        int validoOuInvalido = testaValidadeDaOpcao(telaCod);

        if(validoOuInvalido==0){
            int result = direcionaParaOpcaoDesejada(telaCod, typeUser);
            if(result==-1) continue;
            break;
        } else{
            printf(" \n \033[0;31mOPÇÃO INVÁLIDA!");
            timer_util(1, 0);
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
            result = telaCadastro(typeUser);
            if(result==-1)
                return result;
            break;
        case 2:
            result = telaConsultas(typeUser);
            if(result==-1)
                return result;
            break;
        case 3:
            if(typeUser!=3){
                printaUsuarioSemPrivilegioMessage();
                return -1;
            }
            result = telaGerenciamento();
            if(result==-1)
                return result;
            break;
        default:
            excluiLinha(1);
            break;
    }
}

void escreveOpcoesDeNavegacao(){
    printf("\n 1. Cadastrar novo usuário");
    printf("\n 2. Consultas");
    printf("\n 3. Gerenciamento");
}
