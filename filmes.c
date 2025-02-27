#include "main.h"

void menu_clientes(){

};
void menu_alugueis(){

};

// Função que compara dois filmes pelo nome para ordenação
int comparar_filmes(const void *a, const void *b){
    Filme *filmeA = (Filme *)a;
    Filme *filmeB = (Filme *)b;

    return strcmp(filmeA->nome_filme, filmeB->nome_filme);
}

// Função que ordena os filmes de cada gênero em ordem alfabética
void ordenar_filmes(){
    for(int i = 0; i < MAX_GENEROS; i++){
        qsort(generos[i].filmes, generos[i].num_filmes, sizeof(Filme), comparar_filmes);
    }
}

// Função que cadastra um novo filme em um gênero escolhido pelo usuário
void cadastrar_filme(){
    int genero_id;

    printf("\nEscolha o genero do filme:\n");
    for(int i = 0; i < MAX_GENEROS; i++){
        printf("%d - %s\n", i + 1, generos[i].nome_genero);
    }
    printf("\nDigite a opcao desejada:\n> ");
    scanf("%d", &genero_id);
    genero_id--;

    if(genero_id >= 0 && genero_id < MAX_GENEROS && generos[genero_id].num_filmes < MAX_FILMES){
        Filme *novo_filme = &generos[genero_id].filmes[generos[genero_id].num_filmes];

        printf("\nDigite o nome do filme: ");
        scanf(" %[^\n]s", novo_filme->nome_filme);
        printf("Digite o preco do filme: ");
        scanf("%f", &novo_filme->preco_filme);
        novo_filme->disponivel = 1;
        generos[genero_id].num_filmes++;

        ordenar_filmes(); // Ordena os filmes após cadastrar um novo filme
        printf("\nFilme cadastrado com sucesso!\n");
    } else{
        printf("\nGenero invalido ou limite de filmes atingido!\n");
    }
}

// Função que lista todos os filmes cadastrados, organizados por gênero
void listar_filmes(){
    printf("\n");

    for(int i = 0; i < MAX_GENEROS; i++){
        printf("Genero: %s\n", generos[i].nome_genero);

        for(int j = 0; j < generos[i].num_filmes; j++){
            Filme *filme = &generos[i].filmes[j];
            printf("  Filme %d: %s\n", j + 1, filme->nome_filme);
            printf("    Preco: %.2f\n", filme->preco_filme);
            printf("    Disponivel: %s\n", filme->disponivel ? "Sim" : "Nao");
        }
    }
}

// Função que remove um filme de um gênero escolhido pelo usuário
void remover_filme(){
    int genero_id, filme_id;

    printf("\nEscolha o genero do filme a ser removido:\n");
    for(int i = 0; i < MAX_GENEROS; i++){
        printf("%d - %s\n", i + 1, generos[i].nome_genero);
    }
    printf("\nDigite a opcao desejada:\n> ");
    scanf("%d", &genero_id);
    genero_id--;

    if(genero_id >= 0 && genero_id < MAX_GENEROS && generos[genero_id].num_filmes > 0){
        printf("\nEscolha o filme a ser removido:\n");

        for(int j = 0; j < generos[genero_id].num_filmes; j++){
            printf("%d - %s\n", j + 1, generos[genero_id].filmes[j].nome_filme);
        }
        printf("\nDigite a opcao desejada:\n> ");
        scanf("%d", &filme_id);
        filme_id--;

        if(filme_id >= 0 && filme_id < generos[genero_id].num_filmes){
            for(int j = filme_id; j < generos[genero_id].num_filmes - 1; j++){
                generos[genero_id].filmes[j] = generos[genero_id].filmes[j + 1];
            }
            generos[genero_id].num_filmes--;
            printf("\nFilme removido com sucesso!\n");
        } else{
            printf("\nFilme invalido!\n");
        }
    } else{
        printf("\nGenero invalido ou nenhum filme cadastrado nesse genero!\n");
    }
}

// Função que edita as informações de um filme já cadastrado
void editar_filme(){
    int genero_id, filme_id;

    printf("\nEscolha o genero do filme a ser editado:\n");
    for(int i = 0; i < MAX_GENEROS; i++){
        printf("%d - %s\n", i + 1, generos[i].nome_genero);
    }
    printf("\nDigite a opcao desejada:\n> ");
    scanf("%d", &genero_id);
    genero_id--;

    if(genero_id >= 0 && genero_id < MAX_GENEROS && generos[genero_id].num_filmes > 0){
        printf("\nEscolha o filme a ser editado:\n");

        for(int j = 0; j < generos[genero_id].num_filmes; j++){
            printf("%d - %s\n", j + 1, generos[genero_id].filmes[j].nome_filme);
        }
        printf("\nDigite a opcao desejada:\n> ");
        scanf("%d", &filme_id);
        filme_id--;

        if(filme_id >= 0 && filme_id < generos[genero_id].num_filmes){
            Filme *filme = &generos[genero_id].filmes[filme_id];

            printf("\nDigite o novo nome do filme: ");
            scanf(" %[^\n]s", filme->nome_filme);
            printf("Digite o novo preco do filme: ");
            scanf("%f", &filme->preco_filme);
            printf("O filme esta disponivel? (1 - Sim, 0 - Nao): ");
            scanf("%d", &filme->disponivel);

            ordenar_filmes(); // Ordena os filmes após editar um filme
            printf("\nFilme editado com sucesso!\n");
        } else{
            printf("\nFilme invalido!\n");
        }
    } else{
        printf("\nGenero invalido ou nenhum filme cadastrado nesse genero!\n");
    }
}

// Função que exibe o menu principal e gerencia as opções escolhidas pelo usuário
void menu_filmes(){
    int op = -1;

    while(op != 0){
        printf("\nGerenciamento de Filmes:\n\n");
        printf("1 - Cadastrar Filme \n2 - Listar Filmes\n3 - Remover Filme\n4 - Editar Filme\n0 - Voltar\n\n");
        printf("Digite a opcao desejada:\n> ");
        scanf("%d", &op);

        switch(op){
            case 0:
                break;
            case 1:
                cadastrar_filme();
                break;
            case 2:
                listar_filmes();
                break;
            case 3:
                remover_filme();
                break;
            case 4:
                editar_filme();
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }
}