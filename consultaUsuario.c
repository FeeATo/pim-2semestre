#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Usuario{
    char *login;
    int type;
    char *nome;
    char *sobrenome;
    long long int cpf;
};


int *contaCaracteresCamposUsuarioLinha(char *linha, int* tamanho){
    tamanho = malloc(20);
    int count=0;
    int caractereIndex=0;
    for(int i=0; linha[i]!='\0'; i++){
        if(linha[i]!=';'){
            count++;
        } else{
            *(tamanho+caractereIndex)=count;
            count=0;
            caractereIndex++;
            if(caractereIndex==4){
                *(tamanho+caractereIndex)=11;
                break;
            }
        }
    }

    return tamanho;
}


struct Usuario separaValoresUsuarioCSVLinha(char *linha, struct Usuario usuario){
    int *tamanhos;
    tamanhos = contaCaracteresCamposUsuarioLinha(linha, tamanhos);

    int tamanhoTotal = (*tamanhos)+(*(tamanhos+1))+(*(tamanhos+2))+(*(tamanhos+3))+(*(tamanhos+4))+4;

    int tamanhoLogin = *tamanhos;
    char login[tamanhoLogin];
    //login = malloc(sizeof(char) * tamanhoLogin);

    int tamanhoNome = *(tamanhos+2);
    char nome[*(tamanhos+1)];

    int tamanhoSobrenome = *(tamanhos+3);
    char sobrenome[tamanhoSobrenome];

    char cpf[11];
    //senha = malloc(sizeof(char) * (*(tamanhos+1)));
    int type;
    int indexAux=0;
    int countCommas=0;
    int cursor=0;
    int aux=0;
    for(int i=0; i<tamanhoTotal; i++){
        if(linha[i]!=';'){
            if(countCommas==0){
                *(login+aux) = *(linha+i);
            } else if(countCommas==1){
                type = intASCIIToInt(linha[i]);
            } else if(countCommas==2) {
                *(nome+aux) = *(linha+i);
            } else if(countCommas==3) {
                *(sobrenome+aux) = *(linha+i);
            } else if(countCommas==4) {
                *(cpf+aux) = *(linha+i);
            }
        } else{
            if(countCommas==0){
                *(login+aux) = '\0';
            } else if(countCommas==2) {
                *(nome+aux) = '\0';
            } else if(countCommas==3) {
                *(sobrenome+aux) = '\0';
            } else if(countCommas==4) {
                *(cpf+aux) = '\0';
            }
            aux=-1;
            countCommas++;
        }
        aux++;
    }

    struct Usuario myUsuario = {login, type, nome, sobrenome, atoll(cpf)};

    usuario.login = malloc(strlen(myUsuario.login));
    strcpy(usuario.login, myUsuario.login);

    usuario.type = myUsuario.type;

    usuario.nome = malloc(strlen(myUsuario.nome));
    strcpy(usuario.nome, myUsuario.nome);

    usuario.sobrenome = malloc(strlen(myUsuario.sobrenome));
    strcpy(usuario.sobrenome, myUsuario.sobrenome);

    usuario.cpf = malloc(11);
    usuario.cpf = myUsuario.cpf;

    return usuario;
}

//função principal
int consultaUsuarios(int type){

    carregaTelaConsultaUsuario(type);

    FILE *usuariosInformacoes = fopen(".\\DB\\usuariosInformacoes.txt", "r");
    int qntdLinhasArquivo = contaLinhasTxt(usuariosInformacoes);

    int count=0;
    for(int i=0; i<qntdLinhasArquivo; i++){
        char *linha = pegaLinhaPorIndex(usuariosInformacoes, i);
        struct Usuario usuario;
        usuario = separaValoresUsuarioCSVLinha(linha, usuario);
        if(usuario.type==type){
            count++;
            imprimeUsuario(usuario);
        }
    }

    //se não houver nenhum usuário do tipo, exibirá esta mensagem
    if(count==0){
        char *tipo;
        tipo = getTypeCadastroToPointer(type, tipo);
        for(int i=0; i<strlen(tipo); i++){
            *(tipo+i) = tolower(*(tipo+i));
        }

        printf("\n            Nenhum %s cadastrado!", tipo);
    }

    printf("\n\n\n Pressione qualquer tecla para voltar.");
    getch();
    fclose(usuariosInformacoes);
    return 0;

}

void imprimeUsuario(struct Usuario usuario){
    printf("\n\n       __________");
    printf("\n      | Usuário:      %s", usuario.login);
    printf("\n      | Nome:         %s", usuario.nome);
    printf("\n      | Sobrenome:    %s", usuario.sobrenome);
    printf("\n      | CPF:          %lld", usuario.cpf);
}

void carregaTelaConsultaUsuario(int type){
    system("cls");
    printf("\n         ====== Consulta - %s  ====== \n ", getTypeCadastro(type));
    printf("\n");
}







