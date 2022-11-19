#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "consultaCliente.h"
#include "dbFuncoes.h"
#define CURSOR_CIMA "\033[A"
#define DELETA_LINHA "\033[0;32m"
#define TEXTO_VERMELHO "\033[31m"
#define TEXTO_PRETO "\033[0m"
#define TEXTO_VERDE "\033[32m"


struct Cliente{
    int id;
    long long int cnpj;
    char *nome;
    char *email;
    long long int telefone;
};

int telaConsultas(int typeUser){
    int telaCod=-1;

    while(1){
        limpaTela();
        escreverOpcoesDeConsulta();
        printf("\n\n Digite o número da tela que deseja acessar: ");

        telaCod = intASCIIToInt(getIntegerOnly());
        int validoOuInvalido = testaValidadeDaOpcaoConsulta(telaCod);

        if(validoOuInvalido==0){
            int result = direcionaParaOpcaoDesejadaConsulta(telaCod, typeUser);
            if(result==-1) return -1;
        } else{
            printf(" \n \033[0;31mOPÇÃO INVÁLIDA!");
            timer_util(1, 0);
            printf("\033[0m");
            continue;
        }
    }
}

int direcionaParaOpcaoDesejadaConsulta(int telaCod, int typeUser){
   switch(telaCod){
        case 1:
            if(typeUser>1)
                consultaUsuarios(1);
            else
                printaUsuarioSemPrivilegioMessage();
            break;
        case 2:
            if(typeUser>1)
                consultaUsuarios(2);
            else
                printaUsuarioSemPrivilegioMessage();
            break;
        case 3:
            consultaClientes();
            break;
        case 4:
            return gerarRelatorioClientes();
        case 5:
            return -1;
        default:
            excluiLinha(1);
            break;
    }

    return 0;
}

void escreverOpcoesDeConsulta(){
    printf("\n ============= Menu - Consulta ============== \n ");
    printf("\n 1. Consultar funcionários");
    printf("\n 2. Consultar administradores");
    printf("\n 3. Consultar clientes");
    printf("\n 4. Gerar relatório de clientes");
    printf("\n 5. Voltar");
}

int salvaInformacaoNoArquivo(struct Cliente cliente, FILE *relatorio){
    salvaLinhaNoArquivo("", relatorio);
    salvaLinhaNoArquivo("       __________", relatorio);

    char clienteId[2];
    itoa(cliente.id, clienteId, 10);


    char linhaId[40]= "      | Id:        "; strcat(linhaId, clienteId);
    salvaLinhaNoArquivo(linhaId, relatorio);

    char linhaNome[100] = "      | Nome:      "; strcat(linhaNome, cliente.nome);
    salvaLinhaNoArquivo(linhaNome, relatorio);

    char linhaEmail[100]="      | Email:     "; strcat(linhaEmail, cliente.email);
    salvaLinhaNoArquivo(linhaEmail, relatorio);

    char telefone[20];
    lltoa(cliente.telefone, telefone, 10);
    char linhaTelefone[40]="      | Telefone:  "; strcat(linhaTelefone,telefone);
    salvaLinhaNoArquivo(linhaTelefone, relatorio);

    char clienteCNPJ[14]; lltoa(cliente.cnpj, clienteCNPJ, 10);
    char linhaCNPJ[40]="      | CNPJ:      "; strcat(linhaCNPJ, clienteCNPJ);
    salvaLinhaNoArquivo(linhaCNPJ, relatorio);
}

int gerarRelatorioClientes(){

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    FILE *clientesInformacoes = fopen(".\\DB\\clientesCredentials.txt", "r");

    char end1[35] = ".\\DB\\relatorios\\";
    char end2[3] = "txt";

    char year[4]; itoa((tm.tm_year + 1900),year, 10);
    strcat(end1, year);
    strcat(end1, ".");


    char month[2]; itoa((tm.tm_mon + 1),month, 10);
    strcat(end1, month);
    strcat(end1, ".");


    char day[2]; itoa((tm.tm_mday), day, 10);
    strcat(end1, day);
    strcat(end1, "-");


    char hour[2]; itoa((tm.tm_hour), hour, 10);
    strcat(end1, hour);
    strcat(end1, ".");


    char  min[2]; itoa((tm.tm_min), min, 10);
    strcat(end1, min);
    strcat(end1, ".");


    char sec[2]; itoa((tm.tm_sec), sec, 10);
    strcat(end1, sec);

    strcat(end1,".");
    strcat(end1,"txt");

    FILE *relatorio = fopen(end1, "w");
    int qntdLinhasArquivo = contaLinhasTxt(clientesInformacoes);

    if(desenhaCabecalhoRelatorio(relatorio)==-1){
        printf(" Erro ao gerar arquivo.");
        return -1;
    }


    int count=0;
    for(int i=0; i<qntdLinhasArquivo; i++){
        char *linha = pegaLinhaPorIndex(clientesInformacoes, i, linha);
        struct Cliente cliente;
        cliente = separaValoresClienteCSVLinha(linha, cliente);
        count++;
        if(salvaInformacaoNoArquivo(cliente, relatorio)==-1){
            system("cls");
            printf(" \n %s Erro ao gerar arquivo. %s", TEXTO_VERMELHO, TEXTO_PRETO);
            return -1;
        }
    }

    system("cls");
    printf("\n %s Relatório gerado com sucesso! %s \n", TEXTO_VERDE, TEXTO_PRETO);
    timer_util(2,0);
    fclose(clientesInformacoes);
    fclose(relatorio);

    return 1;
}

int desenhaCabecalhoRelatorio(FILE *relatorio){
    salvaLinhaNoArquivo(" ------------------------------------------------", relatorio);
    salvaLinhaNoArquivo(" ------- RELATÓRIO - CLIENTES CADASTRADOS -------", relatorio);
    salvaLinhaNoArquivo(" ------------------------------------------------", relatorio);
    salvaLinhaNoArquivo("", relatorio);
}

int testaValidadeDaOpcaoConsulta(int opcao){
    switch(opcao){
        case 1: return 0;
        case 2: return 0;
        case 3: return 0;
        case 4: return 0;
        case 5: return 0;
        default: return 1;
    }
}
