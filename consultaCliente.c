#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Cliente{
    int id;
    long long int cnpj;
    char *nome;
    char *email;
    long long int telefone;
};

//conta número de caracteres DE CADA CAMPO de uma linha do arquivo de clientes cadastrados
int *contaCaracteresCamposClienteLinha(char *linha, int* tamanho){
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
            if(caractereIndex==2){
                *(tamanho+caractereIndex)=14;
                continue;
            } else if(caractereIndex==4){
                *(tamanho+caractereIndex)=11;
                break;
            }
        }
    }

    return tamanho;
}

//retorna uma struct com base em uma linha no formato CSV passada como parâmetro
struct Cliente separaValoresClienteCSVLinha(char *linha, struct Cliente cliente){
    int *tamanhos;
    tamanhos = contaCaracteresCamposClienteLinha(linha, tamanhos);

    int tamanhoTotal = (*tamanhos)+(14)+(*(tamanhos+2))+(*(tamanhos+3))+(11)+4;

    int tamanhoId = *tamanhos;
    char id[tamanhoId];

    char cnpj[14];

    int tamanhoNome = *(tamanhos+3);
    char nome[tamanhoNome];

    int tamanhoEmail = *(tamanhos+3);
    char email[tamanhoEmail];

    char telefone[11];
    //senha = malloc(sizeof(char) * (*(tamanhos+1)));
    int type;
    int indexAux=0;
    int countCommas=0;
    int cursor=0;
    int aux=0;
    for(int i=0; i<tamanhoTotal; i++){
        if(linha[i]!=';'){
            if(countCommas==0){
                *(id+aux) = *(linha+i);
            } else if(countCommas==1){
                *(cnpj+aux) = *(linha+i);
            } else if(countCommas==2) {
                *(nome+aux) = *(linha+i);
            } else if(countCommas==3) {
                *(email+aux) = *(linha+i);
            } else if(countCommas==4) {
                *(telefone+aux) = *(linha+i);
            }
        } else{
            if(countCommas==0){
                *(id+aux) = '\0';
            } else if(countCommas==1) {
                *(cnpj+aux) = '\0';
            } else if(countCommas==2) {
                *(nome+aux) = '\0';
            } else if(countCommas==3) {
                *(email+aux) = '\0';
            } else if(countCommas==4) {
                *(telefone+aux) = '\0';
            }
            aux=-1;
            countCommas++;
        }
        aux++;
    }

    struct Cliente myCliente = {atoi(id), atoll(cnpj), nome, email, atoll(telefone)};

    cliente.id = myCliente.id;

    cliente.cnpj = myCliente.cnpj;

    cliente.nome = malloc(strlen(myCliente.nome));
    strcpy(cliente.nome, myCliente.nome);

    cliente.email = malloc(strlen(myCliente.email));
    strcpy(cliente.email, myCliente.email);

    cliente.telefone = myCliente.telefone;

    return cliente;
}


////////////FUNÇÃO PRINCIPAL////////////
//mostra informações dos clientes cadastrados
int consultaClientes(){

    carregaTelaConsultaCliente();

    FILE *usuariosInformacoes = fopen(".\\DB\\clientesCredentials.txt", "r");
    int qntdLinhasArquivo = contaLinhasTxt(usuariosInformacoes);

    int count=0;
    for(int i=0; i<qntdLinhasArquivo; i++){
        char *linha = pegaLinhaPorIndex(usuariosInformacoes, i);
        struct Cliente cliente;
        cliente = separaValoresClienteCSVLinha(linha, cliente);
        count++;
        imprimeCliente(cliente);
    }

    //se não houver nenhum usuário do tipo, exibirá esta mensagem
    if(count==0){
        printf("\n\n            Nenhum cliente cadastrado!");
    }

    printf("\n\n\n Pressione qualquer tecla para voltar.");
    getch();
    fclose(usuariosInformacoes);
    return 0;

}

/*struct Cliente{
    int id;
    long long int cnpj;
    char *nome;
    char *email;
    long long int telefone;
};*/

void imprimeCliente(struct Cliente cliente){
    printf("\n       __________");
    printf("\n      | Id:        %d", cliente.id);
    printf("\n      | Nome:      %s", cliente.nome);
    printf("\n      | Email:     %s", cliente.email);
    printf("\n      | Telefone:  %lld", cliente.telefone);
    printf("\n      | CNPJ:      %lld\n", cliente.cnpj);
}

void carregaTelaConsultaCliente(int type){
    system("cls");
    printf("\n         ====== Consulta - Cliente  ====== ");
}
