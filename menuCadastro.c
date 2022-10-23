#include "utils.h"


void escreveOpcoesDeNavegacao();

void telaCadastro(){
    int telaCod=-1;

    while(1){
        limpaTela();
        escreverOpcoesDeCadastro();
        printf("\n\n Digite o número da tela que deseja acessar: ");

        telaCod = intASCIIToInt(getIntegerOnly());

        int validoOuInvalido = testaValidadeDaOpcao(telaCod);

        if(validoOuInvalido==0){
            direcionaParaOpcaoDesejadaCadastro(telaCod);
            break;
        } else{
            printf(" \n \033[0;31mOPÇÃO INVÁLIDA!");
            timer_util(1, 0);
            printf("\033[0m");
            continue;
        }
    }
}

void direcionaParaOpcaoDesejadaCadastro(int telaCod){
   switch(telaCod){
        case 1:
            printf("cadastro funcionanrio");
            break;
        case 2:
            printf("cadastro administrador");
            break;
        case 3:
            printf("cadastro cliente");
            break;
        case 4:
            break;
        default:
            excluiLinha(1);
            break;
    }
}

void escreverOpcoesDeCadastro(){
    printf("\n ====== Menu - Cadastro ====== \n ");
    printf("\n 1. Cadastrar novo funcionário");
    printf("\n 2. Cadastrar novo administrador");
    printf("\n 3. Cadastrar novo cliente");
    printf("\n 4. Voltar");
}

int testaValidadeDaOpcaoCadastro(int opcao){
    switch(opcao){
        case 1: return 0;
        case 2: return 0;
        case 3: return 0;
        case 4: return 0;
        default: return 1;
    }
}
