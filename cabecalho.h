#ifndef CABECALHO_H
#define CABECALHO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Define as constantes dos tamanhos máximos de gêneros, filmes e aluguéis
#define MAX_GENEROS 5
#define MAX_FILMES 15
#define MAX_ALUGUEIS 100

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

// Estrutura de endereço para o cliente
typedef struct endereco{ 
    char rua[100];
    int numero;
    char bairro[100];
}Endereco_cliente;

// Estrutura de cliente
typedef struct cliente{ 
    char nome_cliente[100];
    int telefone_cliente;
    int cpf_cliente;
    int idade_cliente;
    Endereco_cliente endereco_C;
}Clientes_struct;

// Estrutura de árvore binária para os clientes
typedef struct No{ 
    Clientes_struct cliente;
    struct No * dir;
    struct No * esq;
}No;

// Estrutura de aluguel
typedef struct aluguel {
    int cpf_cliente;
    char nome_filme[100];
    time_t data_aluguel;
    time_t data_devolucao;
    int devolvido; // 1 - Devolvido, 0 - Não devolvido
} Aluguel;

//Define o vetor com os gêneros disponíveis
Genero generos[MAX_GENEROS] = {
    {"Terror", {}, 0},
    {"Comedia", {}, 0},
    {"Acao", {}, 0},
    {"Romance", {}, 0},
    {"Drama", {}, 0}
};

No *raiz = NULL; //Raiz da árvore de clientes
Aluguel alugueis[MAX_ALUGUEIS]; //Vetor de aluguéis
int num_alugueis = 0; //Número de aluguéis registrados

//Definição das funções do arquivo filmes.c
int comparar_filmes(const void *a, const void *b);
void ordenar_filmes();
void cadastrar_filme();
void listar_filmes();
void remover_filme();
void editar_filme();
void menu_filmes();
void salvar_filmes();
void carregar_filmes();

//Definição das funções do arquivo clientes.c
No * buscar(int cpf, No *aux);
void remover_cliente(int cpf);
void listar_clientes(No *aux);
void adicionar_cliente();
void buscar_cliente();
void menu_clientes();

//Definição das funções do arquivo alugueis.c
void registrar_aluguel();
void calcular_multa();
void devolver_filme();
void listar_filmes_alugados();
void menu_alugueis();

#endif