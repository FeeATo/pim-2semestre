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
