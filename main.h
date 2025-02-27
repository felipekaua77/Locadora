#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define as constantes dos tamanhos máximos de gêneros e filmes
#define MAX_GENEROS 5
#define MAX_FILMES 15

//Define a estrutura de um filme
typedef struct filme{
    char nome_filme[100];
    float preco_filme;
    int disponivel; // 1 - Disponivel, 0 - Alugado
}Filme;

//Define a estrutura de um gênero
typedef struct genero{
    char nome_genero[50];
    Filme filmes[MAX_FILMES];
    int num_filmes;
}Genero;

//Define o vetor com os gêneros disponíveis
Genero generos[MAX_GENEROS] = {
    {"Terror", {}, 0},
    {"Comedia", {}, 0},
    {"Acao", {}, 0},
    {"Romance", {}, 0},
    {"Drama", {}, 0}
};

//Protótipos das funções do arquivo filmes.c
int comparar_filmes(const void *a, const void *b);
void ordenar_filmes();
void cadastrar_filme();
void listar_filmes();
void remover_filme();
void editar_filme();
void menu_filmes();

//Protótipos das funções do arquivo clientes.c
void menu_clientes();

//Protótipos das funções do arquivo alugueis.c
void menu_alugueis();

#endif