#include "utils.h"
#include <stdlib.h>
#include "dbFuncoes.h"

struct Cliente separaValoresCliente(char *linha);
char *clienteStructToLinhaCSV(struct Cliente cliente, char* var);

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
    printf("   * Pressione ESC para voltar!                     *");
    printf("\n   **************************************************\n");
    printf("\n              Preencha os seguintes dados: \n");
    printf("");

}

//main deste script
int cadastroClienteTela(){

    escreveTelaCadastroCliente();
    int id;
    long long int cnpj;
    char nome[30];
    char email[30];
    long long int telefone;

    id = getNextId();

    char ch=0;
    int allowedBackspaces=0;
    int i = 0;
    printf("\n Nome da empresa: ");
    do{
        ch=getch();
        if(ch==27)
            return -1;
        else if(ch==13){
            break;
        } else if(ch==8){
            if(allowedBackspaces>0){
                allowedBackspaces--;
                nome[i--]=0;
                printf("\b \b");
            }
        }
        else{
            printf("%c", ch);
            nome[i++]=ch;
            allowedBackspaces++;
        }
    } while(1);
    nome[strlen(nome)]='\0';
    char *nomePointer = nome;

    printf("\n");
    int existencia=0;
    allowedBackspaces=0;
    i = 0;
    ch=0;
    do{
        if(i)
            excluiLinha(1);
        printf(" CNPJ: ");
        scanf("%lld", &cnpj);
        if(cnpj>10000000000000 && checkCnpjExistence(cnpj)==0)
            break;

        i++;
    } while(1);

    fflush(stdin);

    allowedBackspaces=0;
    i = 0;
    ch=0;
    printf(" Email: ");
    do{
        ch=getch();
        if(ch==27)
            return -1;
        else if(ch==13){
            break;
        } else if(ch==8){
            if(allowedBackspaces>0){
                allowedBackspaces--;
                email[i--]=0;
                printf("\b \b");
            }
        }
        else{
            printf("%c", ch);
            email[i++]=ch;
            allowedBackspaces++;
        }
    } while(1);
    email[strlen(email)]='\0';
    char *emailPointer = email;


    printf("\n Telefone: ");
    scanf("%lld", &telefone);

     //1;11111111000111;infotera;infotera@email.com.br;1124217789;
    struct Cliente cliente = {id, cnpj, nomePointer, emailPointer, telefone};
    FILE *fileClientes = fopen(".\\DB\\clientesCredentials.txt", "a");

    char *csvClienteLine = clienteStructToLinhaCSV(cliente, csvClienteLine);

    if(salvaLinhaNoArquivo(csvClienteLine, fileClientes)){
        fclose(fileClientes);
        return 1;
    }



    fclose(fileClientes);
    return 0;
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
}

char *clienteStructToLinhaCSV(struct Cliente cliente, char* var){
    int sizeId = getNumberOfDigitsInInt(cliente.id);
    int sizeCnpj = getNumberOfDigitsInLongLongInt(cliente.cnpj);
    int sizeNome = strlen(cliente.nome);
    int sizeEmail = strlen(cliente.email);
    int sizeTelefone = getNumberOfDigitsInLongLongInt(cliente.telefone);

    int totalSize = sizeId+1+sizeCnpj+1+sizeNome+1+sizeEmail+1+sizeTelefone;

    char *line = malloc(totalSize);
    int i = 0;
    int j=0;
    int id = cliente.id;
    for(i=0; i<sizeId; i++){
        line[i] = intToIntASCII(id%10);
        id/=10;
    }


    line[i]=';';
    long long int cnpj = cliente.cnpj;
    for(j=14; j>0; j--){
        line[i+j]= intToIntASCII(cnpj%10);
        cnpj/=10;
    }
    i+=14;
    i++;
    line[i]=';';
    i++;

    for(j = 0; j<sizeNome;j++){
        line[i] = cliente.nome[j];
        i++;
    }

    line[i]=';';
    i++;
    for(j=0; j<sizeEmail; j++){
        line[i] = cliente.email[j];
        i++;
    }
    line[i]=';';

    long long int telefone = cliente.telefone;
    for(j=sizeTelefone; j>0; j--){
        line[i+j]= intToIntASCII(telefone%10);
        telefone/=10;

    }

    i+=sizeTelefone;
    i++;
    line[i]=';';
    i++;
    line[i]='\0';


    var = malloc(strlen(line));

    strcpy(var, line);

    return var;

}
