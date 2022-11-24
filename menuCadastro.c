#include "utils.h"
#include "cadastroFuncionario.h"
#include "cadastroCliente.h"

void escreveOpcoesDeNavegacao();

////////////FUNÇÃO PRINCIPAL////////////
//mostra opções de cadastro, valida opção digitada e direciona para a escolhida.
int telaCadastro(int typeUser){
    int telaCod=-1;

    while(1){
        limpaTela();
        escreverOpcoesDeCadastro();
        printf("\n\n Digite o número da tela que deseja acessar: ");

        telaCod = intASCIIToInt(getOneIntegerOnly()); //-> explicação em menu.c linhas 20 e 21

        int validoOuInvalido = testaValidadeDaOpcaoCadastro(telaCod); //-> explicação em menu.c linha 23

        if(validoOuInvalido==0){
            int result = direcionaParaOpcaoDesejadaCadastro(telaCod, typeUser); //função em menuCadastro.c direciona para opção digitada
            if(result==-1) return -1;
            if(result==0) telaCadastro(typeUser);
            break;
        } else{
            printf(" \n \033[0;31mOPÇÃO INVÁLIDA!");
            timer_util(1, 0);
            printf("\033[0m");
            continue;
        }
    }
}

//direciona para opção passada no parâmetro. Testa se usuário tem privilégio caso a opção requira.
int direcionaParaOpcaoDesejadaCadastro(int telaCod, int typeUser){
   switch(telaCod){
        case 1:
            do{
                int result = cadastroUsuarioTela(1);  //função em cadastroFuncionario.c chama tela de cadastro para funcionário.
                if(result>0){
                    printf("\n Deseja cadastrar outro funcionário? (s/n) ");
                    if(getSimOuNaoInt()==0)
                        break;
                } else if(result ==-2){
                    break;
                }
                else{
                    printf(" Erro inesperado no cadastro");
                    break;
                }
            } while(1);
            break;
        case 2:
            if(typeUser>1){
                do{
                    int result = cadastroUsuarioTela(2); //função em cadastroFuncionario.c chama tela de cadastro para administrador.
                    if(result>0){
                        printf("\n Deseja cadastrar outro administrador? (s/n) ");
                        if(getSimOuNaoInt()==0) //função em utils.c
                            break;
                    } else if(result ==-2){
                        break;
                    }
                    else{
                        printf(" Erro inesperado no cadastro");
                        break;
                    }
                } while(1);
            } else{
                printaUsuarioSemPrivilegioMessage();
                break;
            }
            break;
        case 3:
            do{
                int result = cadastroClienteTela();
                if(result>0){
                    printf("\n Deseja cadastrar outro cliente? (s/n) ");
                    if(getSimOuNaoInt()==0)
                        break;

                } else if(result == -2){
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
    printf("\n ============= Menu - Cadastro ============== \n ");
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
