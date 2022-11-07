#include "utils.h"
#include <stdlib.h>

struct Cliente separaValoresCliente(char *linha);

struct Cliente{
 //1;11111111000111;infotera;infotera@email.com.br;1124217789;
    int id;
    long long int cnpj;
    char *nome;
    char *email;
    long long int telefone;
};

int escreveTelaCadastroCliente(){
    system("cls");
    printf("\n         ====== Cadastro - Cliente  ====== \n ");

    printf("\n   **************************************************\n");
    printf("   * Pressione '.' para voltar!                     *\n");
    printf("   * Pressione ESC para reescrever o campo anterior *");
    printf("\n   **************************************************\n");
    printf("\n              Preencha os seguintes dados: \n");
    printf("");

}

//main deste script
int cadastroClienteTela(){

    escreveTelaCadastroCliente();
    int id;
    long long int cnpj;
    char nome[20];
    char *email;
    long long int telefone;

    id = getNextId();

    printf(" Nome da empresa: ");
    gets(nome);

    int existencia=0;
    printf("\n");
    int allowedBackspaces=0;

    int i = 0;
    do{
        printf(" CNPJ: ");
        scanf("%lld", &cnpj);
        if(checkCnpjExistence(cnpj)==0)
            break;
    } while(1);




}

int getNextId(){
    FILE *fileClientes = fopen(".\\DB\\clientesCredentials.txt", "r");
    int lastIndex = contaLinhasTxt(fileClientes)-1;
    char *linha = pegaLinhaPorIndex(fileClientes, lastIndex);
    int id = getIdFromLinha(linha)+1;
    fclose(fileClientes);
    return id;
}

int getIdFromLinha(char *linha){
    int i=0;
    char ch;
    char *idChar = malloc(sizeof(char)*3);
    while((ch=linha[i])!=';') {
        idChar[i] = ch;
        i++;
    }

    idChar[i]='\0';

    return atoi(idChar);
}


//retorna 1 se já existir e 0 se não existir
int checkCnpjExistence(long long int cnpj){
    FILE *fileClientes = fopen(".\\DB\\clientesCredentials.txt", "r");

    for(int i = 0; i<contaLinhasTxt(fileClientes); i++){
        char *linha = pegaLinhaPorIndex(fileClientes, i);
        struct Cliente cliente;
        cliente = separaValoresCliente(linha);
        if(cliente.cnpj==cnpj) return 1;
    }

    fclose(fileClientes);
    return 0;

}

struct Cliente separaValoresCliente(char *linha){
    int id;
    char idArrChar[4];
    long long int cnpj;
    char cnpjArrChar[15];
    char nome[31];
    char email[31];
    long long int telefone;
    char telefoneArrChar[14];

    //lê id
    char ch;
    int i = 0;
    int j=0;
    while((ch=linha[i])!=';'){
        *(idArrChar+j)=ch;
        i++;
        j++;
    }
    idArrChar[j++]='\0';
    id = atoi(idArrChar);

    //lê cnpj
    i++;
    j=0;
    while((ch=linha[i])!=';'){
        cnpjArrChar[j]=ch;
        i++;
        j++;
    }

    cnpj = atoll(cnpjArrChar);

    //lê nome
    i++;
    j=0;
    while((ch=linha[i])!=';'){
        nome[j]=ch;
        i++;
        j++;
    }
    nome[j]='\0';

    //lê email
    i++;
    j=0;
    while((ch=linha[i])!=';'){
        email[j]=ch;
        i++;
        j++;
    }

    email[j]='\0';

    //lê telefone
    i++;
    j=0;
    while((ch=linha[i])!=';'){
        telefoneArrChar[j]=ch;
        i++;
        j++;
    }
    telefoneArrChar[++j]='\0';
    telefone = atoll(telefoneArrChar);

    struct Cliente cliente = {id,cnpj,nome,email,telefone};

    return cliente;
};
