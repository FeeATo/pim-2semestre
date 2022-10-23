void telaConsultas(){

}

void direcionaParaOpcaoDesejadaConsulta(int telaCod){
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
        default:
            excluiLinha(1);
            break;
    }
}

void escreverOpcoesDeConsulta(){
    printf("\n ====== Menu - Cadastro ====== \n ");
    printf("\n 1. Cadastrar novo funcionário");
    printf("\n 2. Cadastrar novo administrador");
    printf("\n 3. Cadastrar novo cliente");
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
