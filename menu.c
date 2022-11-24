#include "utils.h"
#include "menuCadastro.h"
#include "menuConsultas.h"
#include "menuGerenciamento.h"

int testaValidadeDaOpcao(int opcao);
int direcionaParaOpcaoDesejada(int telaCod, int typeUser);

////////////FUNÇÃO PRINCIPAL////////////
//carrega a tela de menu com todas as opções. Verifica se opção digitada é válida e direciona para ela.
void carregaTelaMenu(int typeUser){
    int telaCod=-1;
    while(1){
        system("cls");
        printf("\n =================== Menu =================== \n ");

        escreveOpcoesDeNavegacao(); //função em menu.c - escreve opções na tela
        printf("\n\n Digite o número da tela que deseja acessar: ");

                    //função em utils.c intASCIIToInt: converte caracteres numéricos com códigos da tabela ASCII em inteiros
        telaCod = intASCIIToInt(getOneIntegerOnly()); //funções em utils.c - getOneIntegerOnly: apenas aceita um único número. Não aceita letras.

        int validoOuInvalido = testaValidadeDaOpcao(telaCod); //função em menu.c - testa se opção digitada é válida

        if(validoOuInvalido==0){ //se opção for válida, redireciona para a próxima tela.
            int result = direcionaParaOpcaoDesejada(telaCod, typeUser);
            if(result==-1) continue;
            break;
        } else{
            printf(" \n \033[0;31mOPÇÃO INVÁLIDA!");
            timer_util(1, 0); //conta 1 segundo e não mostra mensagem de Loading
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
            result = telaCadastro(typeUser); //função em menuCadastro.c
            if(result==-1)
                return result;
            break;
        case 2:
            result = telaConsultas(typeUser); //função em menuConsultas.c
            if(result==-1)
                return result;
            break;
        case 3:
            if(typeUser!=3){
                printaUsuarioSemPrivilegioMessage(); //caso usuário não tenha privilégio suficiente, mostrar mensagem
                return -1;
            }
            result = telaGerenciamento(); //função em menuGerenciament.c
            if(result==-1)
                return result;
            break;
        default:
            excluiLinha(1); //função em utils.c - exclui do console o número de linhas passado como parâmatro
            break;
    }
}

void escreveOpcoesDeNavegacao(){
    printf("\n 1. Cadastrar novo usuário");
    printf("\n 2. Consultas");
    printf("\n 3. Gerenciamento");
}
