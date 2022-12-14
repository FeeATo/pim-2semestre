#define CURSOR_CIMA "\033[A"
#define DELETA_LINHA "\033[0;32m"
#define TEXTO_VERMELHO "\033[32m"
#define TEXTO_PRETO "\033[0m"
#define TEXTO_VERDE "\033[31m"
#include "utils.h"
#include "login.h"
#include <math.h>
#include "dbFuncoes.h"

//este script ? respons?vel por cadastrar funcion?rios e administradores. O nome ficou apenas cadastroFuncionario porque n?o sei alter?-lo.

struct Usuario{
    char *login;
    int type;
    char *nome;
    char *sobrenome;
    long long int cpf;
};

struct User{
    char *login;
    char *senha;
    int type;
};

char *usuarioStructToLinhaCSV(struct Usuario usuario, char *var);
char *userStructToLinhaCSV(struct User user, char *var);

int escreveTelaCadastroUsuario(int type){
    system("cls");
    printf("\n         ====== Cadastro - %s  ====== \n ", getTypeCadastro(type));

    printf("\n   **************************************************\n");
    printf("   * Pressione ESC para voltar!                     *");
    printf("\n   **************************************************\n");
    printf("\n              Preencha os seguintes dados: \n");
    printf("");

}



int cadastroUsuarioTela(int type){
    escreveTelaCadastroUsuario(type);
    char loginAux[10];
    char *login;

    char senhaAux[10];
    char *senha;

    char senhaConfirmarAux[10];
    char *senhaConfirmar;

    char nomeAux[20];
    char *nome;

    char sobrenomeAux[50];
    char *sobrenome;

    long long int cpf;

    int existencia=0;
    printf("\n");

    char ch='\0';
    int allowedBackspaces=0;
    int i=0;
    do{
        printf(" Login: ");
        do{
            ch=getch();
            if(ch==27)
                return -1;
            else if(ch==13){
                printf("\n");
                break;
            } else if(ch==8){
                if(allowedBackspaces>0){
                    allowedBackspaces--;
                    loginAux[i--]=0;
                    printf("\b \b");
                }
            }
            else{
                printf("%c", ch);
                loginAux[i++]=ch;
                allowedBackspaces++;
            }
        } while(1);
        //gets(login);
        login = malloc(i);
        strcpy(login, loginAux);
        login[i]='\0';
        existencia = checaExistenciaLogin(login);
        if(existencia){
            printf("%s Login j? existente!\n%s", TEXTO_VERDE, TEXTO_PRETO);
            timer_util(1,0);
            excluiLinha(2);
        }
    } while(existencia==1);

    //checa se j? existe um usu?rio com este login
    //checaExistenciaLogin(login);

    ch=0;
    allowedBackspaces=0;
    i=0;
    printf(" Nome: ");
    do{
        ch=getch();
        if(ch==27)
            return -1;
        else if(ch==13){
            printf("\n");
            break;
        } else if(ch==8){
            if(allowedBackspaces>0){
                allowedBackspaces--;
                nomeAux[i--]=0;
                printf("\b \b");
            }
        }
        else{
            printf("%c", ch);
            nomeAux[i++]=ch;
            allowedBackspaces++;
        }
    } while(1);

    nome = malloc(i);
    nome[i]='\0';
    strcpy(nome, nomeAux);

    ch=0;
    allowedBackspaces=0;
    i=0;
    printf(" Sobrenome: ");
    do{
        ch=getch();
        if(ch==27)
            return -1;
        else if(ch==13){
            printf("\n");
            break;
        } else if(ch==8){
            if(allowedBackspaces>0){
                allowedBackspaces--;
                sobrenomeAux[i--]=0;
                printf("\b \b");
            }
        }
        else{
            printf("%c", ch);
            sobrenomeAux[i++]=ch;
            allowedBackspaces++;
        }
    } while(1);

    sobrenome = malloc(i);
    sobrenome[i] = '\0';
    strcpy(sobrenome, sobrenomeAux);

    int repetCpf = 0;
    do{
        if(repetCpf>0) excluiLinha(1);
        printf(" CPF: ");
        repetCpf++;
    } while(scanf("%lld", &cpf) != 1 || cpf<10000000000 || cpf>99999999999);
    //s? deixa digitar n?meros

    fflush(stdin);
    printf(" Senha: "); //fazer bot?ozinho de ver senha
    //funcao de ler senha e escrever um asterisco
    ch=0;
    allowedBackspaces=0;
    i=0;
    while(1) {
        ch=getch();
        if(ch==13)
            break;
        else if(ch==27)
            return -2;
        else{
            if(ch==8 && allowedBackspaces>0) {
                senhaAux[i];
                i--;
                allowedBackspaces--;
                printf("\b \b");
            } else if(ch==8 && allowedBackspaces==0){
                //n?o fa?a nada
            } else{
                senhaAux[i++] = ch;
                allowedBackspaces++;
                printf("*");
            }
        }
    }

    senha = malloc(i);
    strcpy(senha, senhaAux);
    senha[i] = '\0';

    ch=0;
    allowedBackspaces=0;
    i=0;
    int reps=0;
    do{
        if(reps>0) printf(DELETA_LINHA);
        printf("\n Senha novamente: ");
        i=0;
        allowedBackspaces=0;
        while(1) {
            ch=getch();
            if(ch==13)
                break;
            else if(ch==27)
                return -2;
            else{
                if(ch==8 && allowedBackspaces>0) {
                    senhaConfirmarAux[i];
                    i--;
                    allowedBackspaces--;
                    printf("\b \b");
                } else if(ch==8 && allowedBackspaces==0){
                    //n?o fa?a nada
                } else{
                    senhaConfirmarAux[i] = ch;
                    i++;
                    allowedBackspaces++;
                    printf("*");
                }
            }
        }
        reps++;
        senhaConfirmar = malloc(i);
        senhaConfirmar[i]='\0';
        strcpy(senhaConfirmar, senhaConfirmarAux);
    } while(stringComp(strlen(senha), senha, senhaConfirmar)!=1);


    //vai ser salvo no arquivo de dados dos usu?rios
    struct Usuario newUsuario = {login, type, nome, sobrenome, cpf};
    struct User newUser = {login, senha, type};

    char *csvUsuarioLine;
    char *csvUserLine;

    csvUsuarioLine = usuarioStructToLinhaCSV(newUsuario, &csvUsuarioLine);
    csvUserLine = userStructToLinhaCSV(newUser, &csvUserLine);

    FILE *loginCredenciais = fopen(".\\DB\\loginCredentials.txt", "a");
    FILE *usuariosInformacoes = fopen(".\\DB\\usuariosInformacoes.txt", "a");

    int retorno;
    int salva1 = salvaLinhaNoArquivo(csvUsuarioLine, usuariosInformacoes);
    int salva2 = salvaLinhaNoArquivo(csvUserLine, loginCredenciais);
    //salva newUsuario
    if(salva1 && salva2)
        retorno = 1;
    else
        retorno = 0;

    fclose(loginCredenciais);
    fclose(usuariosInformacoes);

    return retorno;

    //salva newUser
}



char *userStructToLinhaCSV(struct User user, char* var){
    int sizeLogin = strlen(user.login);
    int sizeSenha = strlen(user.senha);
    int totalSize = sizeLogin+1+sizeSenha+1+1;
    char *line = malloc(totalSize);
    int i = 0;
    int j=0;
    for(i=0; i<sizeLogin; i++){
        line[i] = user.login[i];
    }

    line[i]=';';
    i++;
    for(j=0; j<sizeSenha; j++){
        line[i]=user.senha[j];
        i++;
    }
    line[i]=';';
    i++;
    line[i]=intToIntASCII(user.type);
    line[++i]='\0';

    var = malloc(strlen(line));

    strcpy(var, line);

    return var;

}

char *usuarioStructToLinhaCSV(struct Usuario user, char* var){
    int sizeLogin = strlen(user.login);
    int quatroBytes = 4;
    int sizeNome = strlen(user.nome);
    int sizeSobrenome = strlen(user.sobrenome);
    int quarentaEQuatroBytes = 11;
    int totalSize = sizeLogin+1+1+1+sizeNome+1+sizeSobrenome+1+quarentaEQuatroBytes;
    char *line = malloc(totalSize);
    int i = 0;
    int j=0;
    for(i=0; i<sizeLogin; i++){
        line[i] = user.login[i];
    }

    line[i]=';';
    i++;
    line[i]=intToIntASCII(user.type);
    i++;
    line[i]=';';
    i++;
    for(j=0; j<sizeNome;j++){
        line[i]=user.nome[j];
        i++;
    }
    line[i]=';';
    i++;
    for(j=0;j<sizeSobrenome;j++){
        line[i]=user.sobrenome[j];
        i++;
    }
    line[i]=';';
    i++;
    long long int cpfInt = user.cpf;
    for(j=10; j>=0; j--){
        line[i+j] = intToIntASCII(cpfInt%10);
        cpfInt/=10;
    }
    i+=11;
    line[i]='\0';

    var = malloc(strlen(line));

    strcpy(var, line);

    return var;
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

