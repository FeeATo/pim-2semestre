#define CURSOR_CIMA "\033[A"
#define DELETA_LINHA "\033[0;32m"
#define TEXTO_VERMELHO "\033[32m"
#define TEXTO_PRETO "\033[0m"
#define TEXTO_VERDE "\033[31m"
#include "utils.h"
#include "login.h"


struct Usuario{
    char *login;
    int type;
    char *nome;
    char *sobrenome;
    int cpf;
};

struct User{
    char *login;
    char *senha;
    int type;
};

int escreveTelaCadastroFuncionario(){
    system("cls");
    printf("\n         ====== Cadastro -  Funcion�rio ====== \n ");

    printf("\n   **************************************************\n");
    printf("   * Pressione '.' para voltar!                     *\n");
    printf("   * Pressione ESC para reescrever o campo anterior *");
    printf("\n   **************************************************\n");
    printf("\n              Preencha os seguintes dados: \n");
    printf("");

}



int cadastroFuncionarioTela(){
    escreveTelaCadastroFuncionario();
    int tipe = 1;
    char login[10];
    char senha[10];
    char senhaConfirmar[10];
    char nome[20];
    char sobrenome[20];
    int cpf;

    int existencia=0;
    printf("\n");
    do{
        printf(" Login: ");
        gets(login);
        existencia = checaExistenciaLogin(login);
        if(existencia){
            printf("%s Login j� existente!\n%s", TEXTO_VERDE, TEXTO_PRETO);
            timer_util(1,0);
            excluiLinha(2);
        }
    } while(existencia==1);

    //checa se j� existe um usu�rio com este login
    //checaExistenciaLogin(login);


    printf(" Nome: ");
    gets(nome);


    printf(" Sobrenome: ");
    gets(sobrenome);

    printf(" CPF: ");
    cpf = intASCIIToInt(getIntegerOnly());
    //s� deixa digitar n�meros


    printf("\n Senha: "); //fazer bot�ozinho de ver senha
    //funcao de ler senha e escrever um asterisco
    int i=0;
    char ch;
    int allowedBackspaces=0;
    while(1) {
        ch=getch();
        if(ch==13){
            break;
        } else{
            if(ch==8 && allowedBackspaces>0) {
                senha[i];
                i--;
                allowedBackspaces--;
                printf("\b \b");
            } else if(ch==8 && allowedBackspaces==0){
                //n�o fa�a nada
            } else{
                senha[i] = ch;
                i++;
                allowedBackspaces++;
                printf("*");
            }
        }
    }
    senha[i++] = '\0';


    int reps=0;
    do{
        if(reps>0) printf(DELETA_LINHA);
        printf("\n Senha novamente: ");
        i=0;
        allowedBackspaces=0;
        while(1) {
            ch=getch();
            if(ch==13){
                break;
            } else{
                if(ch==8 && allowedBackspaces>0) {
                    senhaConfirmar[i];
                    i--;
                    allowedBackspaces--;
                    printf("\b \b");
                } else if(ch==8 && allowedBackspaces==0){
                    //n�o fa�a nada
                } else{
                    senhaConfirmar[i] = ch;
                    i++;
                    allowedBackspaces++;
                    printf("*");
                }
            }
        }
        reps++;
        senhaConfirmar[i++]='\0';
    } while(stringComp(strlen(senha), senha, senhaConfirmar)!=1);


    //vai ser salvo no arquivo de dados dos usu�rios
    struct Usuario newUsuario = {login, 1, nome, sobrenome, cpf};
    struct User newUser = {login, senha, 1};

    //salva newUsuario
    //salva newUser
}


int checaExistenciaLogin(char *login){
    FILE *fp = fopen(".\\DB\\loginCredentials.txt", "r");
    if(fp==NULL){
        printf("Erro ao acessar arquivo");
        timer_util(1,0);
        exit(1);
    }

    int i = 0;
    char ch;
    int typeLogin;
    for(i = 0; i< contaLinhasTxt(fp); i++){

        struct User myUser;
        char *values;
        values = pegaLinhaPorIndex(fp,i);
        myUser = separaValores(values);


        int loginComp = stringComp(strlen(login), login, myUser.login);

        if(loginComp == 1){
            fclose(fp);
            typeLogin = myUser.type;
            return 1;
        } else{
            continue;
        }
    }
    return 0;


}

