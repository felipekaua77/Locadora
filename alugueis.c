#include "cabecalho.h"
#include "filmes.c"

void registrar_aluguel(){
    if(num_alugueis >= MAX_ALUGUEIS){
        printf("Limite de alugueis atingido!\n");
        return;
    }

    int cpf;
    char nome_filme[100];
    int dias_aluguel;
    time_t agora = time(NULL);

    printf("Digite o CPF do cliente:\n> ");
    scanf("%d", &cpf);
    listar_filmes();
    printf("Digite o nome do filme:\n> ");
    scanf(" %[^\n]s", nome_filme);
    printf("Digite a quantidade de dias para o aluguel:\n> ");
    scanf("%d", &dias_aluguel);

    // Verifica se o filme está disponível
    int filme_encontrado = 0;
    for(int i = 0; i < MAX_GENEROS; i++){
        for(int j = 0; j < generos[i].num_filmes; j++){
            if(strcmp(generos[i].filmes[j].nome_filme, nome_filme) == 0){
                if(generos[i].filmes[j].disponivel == 1){
                    generos[i].filmes[j].disponivel = 0;
                    filme_encontrado = 1;
                    break;
                } else{
                    printf("Filme nao disponivel para aluguel.\n");
                    return;
                }
            }
        }
        if(filme_encontrado) break;
    }

    if(!filme_encontrado){
        printf("Filme nao encontrado.\n");
        return;
    }

    Aluguel novo_aluguel;
    novo_aluguel.cpf_cliente = cpf;
    strcpy(novo_aluguel.nome_filme, nome_filme);
    novo_aluguel.data_aluguel = agora;
    novo_aluguel.data_devolucao = agora + (dias_aluguel * 24 * 60 * 60);
    novo_aluguel.devolvido = 0;

    alugueis[num_alugueis++] = novo_aluguel;
    printf("Aluguel registrado com sucesso!\n");
}

void calcular_multa(){
    printf("Calculando multas...\n"); // Mensagem de depuração
    time_t agora = time(NULL);
    double multa_por_dia = 5.0; // Valor da multa por dia de atraso

    for(int i = 0; i < num_alugueis; i++){
        if(!alugueis[i].devolvido && alugueis[i].data_devolucao < agora){
            double dias_atraso = difftime(agora, alugueis[i].data_devolucao) / (24 * 60 * 60);
            double multa = dias_atraso * multa_por_dia;
            printf("Cliente CPF: %d esta atrasado na devolucao do filme '%s'. Multa: R$%.2f\n", alugueis[i].cpf_cliente, alugueis[i].nome_filme, multa);
        }
    }
}

void devolver_filme(){
    int cpf;
    char nome_filme[100];
    time_t agora = time(NULL);

    printf("Digite o CPF do cliente:\n> ");
    scanf("%d", &cpf);
    printf("Digite o nome do filme:\n> ");
    scanf(" %[^\n]s", nome_filme);

    for(int i = 0; i < num_alugueis; i++){
        if(alugueis[i].cpf_cliente == cpf && strcmp(alugueis[i].nome_filme, nome_filme) == 0 && !alugueis[i].devolvido){
            alugueis[i].devolvido = 1;
            printf("Filme devolvido com sucesso!\n");

            // Atualiza a disponibilidade do filme
            for(int j = 0; j < MAX_GENEROS; j++){
                for (int k = 0; k < generos[j].num_filmes; k++) {
                    if (strcmp(generos[j].filmes[k].nome_filme, nome_filme) == 0) {
                        generos[j].filmes[k].disponivel = 1;
                        break;
                    }
                }
            }

            // Calcula a multa se houver atraso
            if(alugueis[i].data_devolucao < agora){
                double dias_atraso = difftime(agora, alugueis[i].data_devolucao) / (24 * 60 * 60);
                double multa = dias_atraso * 5.0; // Valor da multa por dia de atraso
                printf("Multa por atraso: R$%.2f\n", multa);
            }
            return;
        }
    }
    printf("Aluguel nao encontrado.\n");
}

void listar_filmes_alugados(){
    printf("\nFilmes Alugados:\n\n");
    for(int i = 0; i < num_alugueis; i++){
        if(!alugueis[i].devolvido){
            printf("Cliente CPF: %d\n", alugueis[i].cpf_cliente);
            printf("Filme: %s\n", alugueis[i].nome_filme);
            printf("Data de Aluguel: %s", ctime(&alugueis[i].data_aluguel));
            printf("Data de Devolucao: %s", ctime(&alugueis[i].data_devolucao));
            printf("\n");
        }
    }
}

void menu_alugueis(){
    int op = -1;

    while(op != 0){
        printf("\nGerenciamento de Alugueis:\n\n");
        printf("1 - Registrar Aluguel\n2 - Devolver Filme\n3 - Calcular Multa\n4 - Listar Filmes Alugados\n0 - Voltar\n\n");
        printf("Digite a opcao desejada:\n> ");
        scanf("%d", &op);

        switch(op){
            case 0:
                break;
            case 1:
                registrar_aluguel();
                break;
            case 2:
                devolver_filme();
                break;
            case 3:
                calcular_multa();
                break;
            case 4:
                listar_filmes_alugados();
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }
}