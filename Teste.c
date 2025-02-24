#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_GENEROS 5
#define MAX_FILMES_POR_GENERO 15

typedef struct {
    char nome_filme[100];
    float preco_filme;
    int disponivel; // 1 - Disponivel, 0 - Alugado
} Filme;

typedef struct {
    char nome_genero[50];
    Filme filmes[MAX_FILMES_POR_GENERO];
    int num_filmes;
} Genero;

Genero generos[MAX_GENEROS] = {
    {"Terror", {}, 0},
    {"Comedia", {}, 0},
    {"Acao", {}, 0},
    {"Romance", {}, 0},
    {"Drama", {}, 0}
};

void cadastrar_filme() {
    int genero_id;
    printf("Escolha o genero do filme:\n");
    for (int i = 0; i < MAX_GENEROS; i++) {
        printf("%d - %s\n", i + 1, generos[i].nome_genero);
    }
    printf("Digite a opcao desejada: ");
    scanf("%d", &genero_id);
    genero_id--;

    if (genero_id >= 0 && genero_id < MAX_GENEROS && generos[genero_id].num_filmes < MAX_FILMES_POR_GENERO) {
        Filme *novo_filme = &generos[genero_id].filmes[generos[genero_id].num_filmes];
        printf("Digite o nome do filme: ");
        scanf(" %[^\n]s", novo_filme->nome_filme);
        printf("Digite o preco do filme: ");
        scanf("%f", &novo_filme->preco_filme);
        novo_filme->disponivel = 1;
        generos[genero_id].num_filmes++;
        printf("\n\nFilme cadastrado com sucesso!\n");
    } else {
        printf("Genero invalido ou limite de filmes atingido!\n");
    }
}

void listar_filmes() {
    for (int i = 0; i < MAX_GENEROS; i++) {
        printf("Genero: %s\n", generos[i].nome_genero);
        for (int j = 0; j < generos[i].num_filmes; j++) {
            Filme *filme = &generos[i].filmes[j];
            printf("  Filme %d: %s\n", j + 1, filme->nome_filme);
            printf("    Preco: %.2f\n", filme->preco_filme);
            printf("    Disponivel: %s\n", filme->disponivel ? "Sim" : "Nao");
        }
    }
}

void menu() {
    int op = -1;

    while (op != 0) {
        printf("\nGerenciamento de Filmes:\n\n");
        printf("1 - Cadastrar Filme \n2 - Listar Filmes\n0 - Sair\n\n");
        printf("Digite a opcao desejada:\n> ");
        scanf("%d", &op);

        switch (op) {
            case 0:
                break;
            case 1:
                cadastrar_filme();
                break;
            case 2:
                listar_filmes();
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }
}

int main() {
    srand(time(NULL));
    menu();

    return 0;
}