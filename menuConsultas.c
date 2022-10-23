int telaConsultas(){
    int telaCod=-1;

    while(1){
        limpaTela();
        escreverOpcoesDeConsulta();
        printf("\n\n Digite o número da tela que deseja acessar: ");

        telaCod = intASCIIToInt(getIntegerOnly());
        int validoOuInvalido = testaValidadeDaOpcaoConsulta(telaCod);

        if(validoOuInvalido==0){
            int result = direcionaParaOpcaoDesejadaConsulta(telaCod);
            if(result==-1) return -1;
            break;
        } else{
            printf(" \n \033[0;31mOPÇÃO INVÁLIDA!");
            timer_util(1, 0);
            printf("\033[0m");
            continue;
        }
    }
}

int direcionaParaOpcaoDesejadaConsulta(int telaCod){
   switch(telaCod){
        case 1:
            printf("cadastro funcionanrio");
            break;
        case 2:
            printf("cadastro administrador");
            break;
        case 3:
            printf("cadastro cliente");
            break;
        case 4:
            return -1;
        default:
            excluiLinha(1);
            break;
    }
}

void escreverOpcoesDeConsulta(){
    printf("\n ====== Menu - Consulta ====== \n ");
    printf("\n 1. Consultar funcionários");
    printf("\n 2. Consultar administradores");
    printf("\n 3. Consultar clientes");
    printf("\n 4. Voltar");
}

int testaValidadeDaOpcaoConsulta(int opcao){
    switch(opcao){
        case 1: return 0;
        case 2: return 0;
        case 3: return 0;
        case 4: return 0;
        default: return 1;
    }
}
