#define CURSOR_CIMA "\033[A"
#define DELETA_LINHA "\033[0;32m"
#define TEXTO_VERMELHO "\033[32m"
#define TEXTO_PRETO "\033[0m"
#define TEXTO_VERDE "\033[31m"
#include "utils.h"
#include "login.h"
#include <math.h>
#include "dbFuncoes.h"

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

int escreveTelaCadastroFuncionario(){
    system("cls");
    printf("\n         ====== Cadastro -  Funcionário ====== \n ");

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
    long long int cpf;

    int existencia=0;
    printf("\n");
    do{
        printf(" Login: ");
        gets(login);
        existencia = checaExistenciaLogin(login);
        if(existencia){
            printf("%s Login já existente!\n%s", TEXTO_VERDE, TEXTO_PRETO);
            timer_util(1,0);
            excluiLinha(2);
        }
    } while(existencia==1);

    //checa se já existe um usuário com este login
    //checaExistenciaLogin(login);


    printf(" Nome: ");
    gets(nome);


    printf(" Sobrenome: ");
    gets(sobrenome);

    int repetCpf = 0;
    do{
        if(repetCpf>0) excluiLinha(1);
        printf(" CPF: ");
        repetCpf++;
    } while(scanf("%lld", &cpf) != 1 || cpf<10000000000 || cpf>99999999999);
    //só deixa digitar números

    fflush(stdin);
    printf(" Senha: "); //fazer botãozinho de ver senha
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
                //não faça nada
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
                    //não faça nada
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


    //vai ser salvo no arquivo de dados dos usuários
    struct Usuario newUsuario = {login, 1, nome, sobrenome, cpf};
    struct User newUser = {login, senha, 1};

    char *csvUsuarioLine;
    char *csvUserLine;

    csvUsuarioLine = usuarioStructToLinhaCSV(newUsuario, csvUsuarioLine);
    csvUserLine = userStructToLinhaCSV(newUser, csvUserLine);

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



char *userStructToLinhaCSV(struct User user, char *var){
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

    strcpy(var,line);

    return var;

}

char *usuarioStructToLinhaCSV(struct Usuario user, char *var){
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

    strcpy(var,line);

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

