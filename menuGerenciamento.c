
////////////FUNÇÃO PRINCIPAL////////////////
int telaGerenciamento(){
    int telaCod=-1;

    while(1){
        limpaTela();
        escreverOpcoesDeGerenciamento();
        printf("\n\n Digite o número da tela que deseja acessar: ");

        telaCod = intASCIIToInt(getIntegerOnly());
        int validoOuInvalido = testaValidadeDaOpcaoGerenciamento(telaCod);

        if(validoOuInvalido==0){
            int result = direcionaParaOpcaoDesejadaGerenciamento(telaCod);
            if(result==-1) return -1;
            if(result>0) break;
        } else{
            printf(" \n \033[0;31mOPÇÃO INVÁLIDA!");
            timer_util(1, 0);
            printf("\033[0m");
            continue;
        }
    }
}

int direcionaParaOpcaoDesejadaGerenciamento(int telaCod){
   switch(telaCod){
        case 1:
            openDirectory(".\\DB\"");
            return 0;
            break;
        case 2:
            openDirectory(".\\DB\\logs\"");
            break;
        case 3:
            return -1;
        default:
            excluiLinha(1);
            break;
    }
}

void escreverOpcoesDeGerenciamento(){
    printf("\n =========== Menu - Gerenciamento =========== \n ");
    printf("\n 1. Acessar arquivos raw");
    printf("\n 2. Logs");
    printf("\n 3. Voltar");
}

int testaValidadeDaOpcaoGerenciamento(int opcao){
    switch(opcao){
        case 1: return 0;
        case 2: return 0;
        case 3: return 0;
        default: return 1;
    }
}
