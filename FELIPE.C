#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct cadastro_pessoa {
    char nome[50];
    int id;
} cadastro_pessoa;

typedef struct cadastro_filme {
    char nome_filme[50];
    char genero_filme[30];
    float preco_filme;
    int disponivel; // 1 para disponível, 0 para alugado
} cadastro_filme;

typedef struct agendamentos {
    int id;
    int id_filme;
    int id_pessoa;
    int data;
    int hora;
} agendamentos;

cadastro_filme** criarTabuleiro(int linhas, int colunas) {
    cadastro_filme** tabuleiro = (cadastro_filme**)malloc(linhas * sizeof(cadastro_filme*));
    for (int i = 0; i < linhas; i++) {
        tabuleiro[i] = (cadastro_filme*)malloc(colunas * sizeof(cadastro_filme));
    }
    return tabuleiro;
}

void imprimirTabuleiro(cadastro_filme** tabuleiro, int linhas, int colunas) {
    // Calcula o comprimento máximo dos nomes dos filmes
    int maxLen = 1; // Para o caso de "X"
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int len = strlen(tabuleiro[i][j].nome_filme);
            if (len > maxLen) {
                maxLen = len;
            }
        }
    }

    // Imprime os números das colunas
    printf("    ");
    for (int j = 0; j < colunas; j++) {
        printf(" %*d ", maxLen, j);
    }
    printf("\n");

    // Imprime o tabuleiro
    for (int i = 0; i < linhas; i++) {
        // Imprime linha de separação
        printf("   ");
        for (int j = 0; j < colunas; j++) { 
            printf("+");
            for (int k = 0; k < maxLen + 2; k++) {
                printf("-");
            }
        }
        printf("+\n");

        // Imprime o número da linha
        printf(" %2d ", i);

        // Imprime os filmes
        for (int j = 0; j < colunas; j++) { // Imprime "X" se o filme não estiver disponível
            if (tabuleiro[i][j].disponivel == 0) {
                printf("| %*s ", -maxLen, "X");
            } else {
                printf("| %*s ", -maxLen, tabuleiro[i][j].nome_filme);
            }
        }
        printf("|\n");
    }

    // Imprime linha de separação final
    printf("   ");
    for (int j = 0; j < colunas; j++) {
        printf("+");
        for (int k = 0; k < maxLen + 2; k++) {
            printf("-");
        }
    }
    printf("+\n");
}

int main() {
    srand(time(NULL));

    int linhas = 15;
    int colunas = 4;

    cadastro_filme** tabuleiro = criarTabuleiro(linhas, colunas);

    // Exemplo de preenchimento do tabuleiro
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            snprintf(tabuleiro[i][j].nome_filme, 50, "Filme%d%d", i, j);
            snprintf(tabuleiro[i][j].genero_filme, 30, "Genero%d%d", i, j);
            tabuleiro[i][j].preco_filme = (float)(rand() % 100) / 10.0;
            tabuleiro[i][j].disponivel = 1; // Todos os filmes começam como disponíveis
        }
    }

    printf("Tabuleiro de Filmes:\n");
    imprimirTabuleiro(tabuleiro, linhas, colunas);

    // Libera a memória alocada
    for (int i = 0; i < linhas; i++) {
        free(tabuleiro[i]);
    }
    free(tabuleiro);

    return 0;
}