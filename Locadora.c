#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_GENEROS 5
#define MAX_FILMES 15

typedef struct filme{
    char nome_filme[100];
    float preco_filme;
    int disponivel; // 1 - Disponivel, 0 - Alugado
}Filme;
printf("faz o L");
typedef struct genero{
    char nome_genero[50];
    Filme filmes[MAX_FILMES];
    int num_filmes;
}Genero;

typedef struct endereco{
    char rua[100];
    int numero;
    char bairro[100];
    char cidade[100];
    char estado[100];
}Endereco_cliente;

typedef struct cliente{
    char nome_cliente[100];
    int telefone_cliente;
    int cpf_cliente;
    int idade_cliente;
    Endereco_cliente endereco_C;
}Clientes_struct;

typedef struct No{
    int valor;
    struct No * dir;
    struct No * esq;
}No;

No *raiz = NULL;
int tam = 0;

//buscar um valor na arvore
No * buscar(int valor, No *aux){
    if(aux == NULL){
        return NULL;
    }else if(valor == aux->valor){
        return aux;
    }else if(valor < aux->valor){
        //pode estar na esq
        if(aux->esq != NULL){
            return buscar(valor, aux->esq);
        }else{
            return aux; //pai do elemento se ele existisse
        }
    }else{
        //pode estar na dir
        if(aux->dir != NULL){
            return buscar(valor, aux->dir);
        }else{
            return aux; //pai do elemento se ele existisse
        }
    }
}

//adiciona um valor na arvore
void add(int valor){
    No *novo = malloc (sizeof(No));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    No* aux = buscar(valor, raiz);
    if(aux == NULL){
        raiz = novo;
    }else if(aux->valor == valor){
        printf("Adicao impossivel, chave duplicada! :'( \n");
        free(novo);
    }else if(valor < aux->valor){
        aux->esq = novo;
    }else{
        aux->dir = novo;
    }    
}

//remove um valor da arvore
void remover(int valor){
    No *pai = NULL;
    No *atual = raiz;

    while(atual != NULL && atual -> valor != valor){ //buscar no pra removr e seu respectivo pai 
        pai = atual; 

        if(valor < atual -> valor){
            atual = atual -> esq;
        }
        else{
            atual = atual -> dir;
        }
    }
    if (atual == NULL){ //caso o no nao seja encontrado
        printf("Essa valor nao foi encontrado!\n");
        return;
    }
    if(atual -> esq == NULL && atual -> dir == NULL){ //remocao da folha
        if(pai == NULL){  //caso seja a raiz
            raiz = NULL;
        }
        else if(pai -> esq == atual){
            pai -> esq = NULL;
        }
        else{
            pai -> dir = NULL;
        }
        free(atual);
    }
    else if(atual -> esq == NULL || atual -> dir == NULL){ //no com apenas um filho
        No *filho = (atual->esq != NULL) ? atual->esq : atual->dir;
        
        if (pai == NULL){ //se for removido a raiz
            raiz = filho;
        }
        else if(pai -> esq == atual){
            pai -> esq = filho;
        }
        else{
            pai -> dir = filho;
        }
        free(atual);
    }
    else{ //remocao de no com dois filhos
        No *sucessor = atual -> dir;
        No *paisucessor = atual;
    
        while(sucessor -> esq != NULL){ //encontrar o menor valor da sub-arvore q fica a direita
            paisucessor = sucessor;
            sucessor = sucessor -> esq;
        }

        atual -> valor = sucessor -> valor; //substituir valor do no que vai ser removido

        if (paisucessor->esq == sucessor) {
            paisucessor->esq = sucessor->dir;
        } else {
            paisucessor->dir = sucessor->dir;
        }
        free(sucessor);
    }
}
/*
void imprimir_in_ordem(No *aux){
    if(aux != NULL){
        imprimir_in_ordem(aux->esq);
        printf("%d\n", aux->valor);
        imprimir_in_ordem(aux->dir);
    }
}*/

Genero generos[MAX_GENEROS] = {
    {"Terror", {}, 0},
    {"Comedia", {}, 0},
    {"Acao", {}, 0},
    {"Romance", {}, 0},
    {"Drama", {}, 0}
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
        } else {
            printf("\nFilme invalido!\n");
        }
    } else {
        printf("\nGenero invalido ou nenhum filme cadastrado nesse genero!\n");
    }
}

// Função que exibe o menu principal e gerencia as opções escolhidas pelo usuário
void menu_filmes() {
    int op = -1;

    while (op != 0) {
        printf("\nGerenciamento de Filmes:\n\n");
        printf("1 - Cadastrar Filme \n2 - Listar Filmes\n3 - Remover Filme\n4 - Editar Filme\n0 - Sair\n\n");
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

// Função principal que inicializa o programa
int main() {
    srand(time(NULL));
    menu_filmes();

    return 0;
}