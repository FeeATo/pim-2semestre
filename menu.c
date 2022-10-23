#include "utils.h"
#include "menuCadastro.h"
#include "menuConsultas.h"

int testaValidadeDaOpcao(int opcao);
void direcionaParaOpcaoDesejada(int telaCod);

void carregaTelaMenu(int idUser){
    int telaCod=-1;
    while(1){
        system("cls");
        printf("\n ========== Menu ========== \n ");

        escreveOpcoesDeNavegacao();
        printf("\n\n Digite o número da tela que deseja acessar: ");

        telaCod = intASCIIToInt(getIntegerOnly());

        int validoOuInvalido = testaValidadeDaOpcao(telaCod);

        if(validoOuInvalido==0){
            direcionaParaOpcaoDesejada(telaCod);
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
        case 4: return 0;
        case 5: return 0;
        default: return 1;
    }
}

void direcionaParaOpcaoDesejada(int telaCod){
   switch(telaCod){
        case 1:
            telaCadastro();
            break;
        case 2:
            telaConsultas();
            break;
        case 3:
            //telaGerencimento();
            break;
        case 4: break;
        case 5: break;
        default:
            excluiLinha(1);
            break;
    }
}

void escreveOpcoesDeNavegacao(){
    printf("\n 1. Cadastrar novo usuário");
    printf("\n 2. Consultas");
    printf("\n 3. Gerenciamento");
    printf("\n 4. Sei lá");
    printf("\n 5. Não sei ");
}
