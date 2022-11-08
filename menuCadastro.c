#include "utils.h"
#include "cadastroFuncionario.h"
#include "cadastroCliente.h"

void escreveOpcoesDeNavegacao();

int telaCadastro(){
    int telaCod=-1;

    while(1){
        limpaTela();
        escreverOpcoesDeCadastro();
        printf("\n\n Digite o número da tela que deseja acessar: ");

        telaCod = intASCIIToInt(getOneIntegerOnly());

        int validoOuInvalido = testaValidadeDaOpcao(telaCod);

        if(validoOuInvalido==0){
            int result = direcionaParaOpcaoDesejadaCadastro(telaCod);
            if(result==-1) return -1;
            if(result==0) telaCadastro();
            break;
        } else{
            printf(" \n \033[0;31mOPÇÃO INVÁLIDA!");
            timer_util(1, 0);
            printf("\033[0m");
            continue;
        }
    }
}

int direcionaParaOpcaoDesejadaCadastro(int telaCod){
   switch(telaCod){
        case 1:
            do{
                if(cadastroUsuarioTela(1)){
                        printf("\n Deseja cadastrar outro funcionário? ");
                        if(getSimOuNaoInt()==0)
                            break;
                } else{
                    printf(" Erro inesperado no cadastro");
                    break;
                }
            } while(1);
            break;
        case 2:
            do{
                if(cadastroUsuarioTela(2)){
                    printf("\n Deseja cadastrar outro administrador? ");
                    if(getSimOuNaoInt()==0)
                        break;
                } else{
                    printf("Erro inesperado no cadastro");
                    break;
                }
            } while(1);
            break;
        case 3:
            do{
                if(cadastroClienteTela()){
                    printf("\n Deseja cadastrar outro cliente? ");
                    if(getSimOuNaoInt()==0)
                        break;

                } else{
                    printf("Erro inesperado no cadastro");
                    break;
                }
            } while(1);
            break;
        case 4:
            return -1;
            break;
        default:
            excluiLinha(1);
            break;
    }


    return 0;
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
