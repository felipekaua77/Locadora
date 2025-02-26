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

typedef struct genero{
    char nome_genero[50];
    Filme filmes[MAX_FILMES];
    int num_filmes;
}Genero;

typedef struct endereco{ // Estrutura de endereço para o cliente
    char rua[100];
    int numero;
    char bairro[100];
    char cidade[100];
    char estado[100];
}Endereco_cliente;

typedef struct cliente{ // Estrutura de cliente
    char nome_cliente[100];
    int telefone_cliente;
    int cpf_cliente;
    int idade_cliente;
    Endereco_cliente endereco_C;
}Clientes_struct;

typedef struct No{ // Estrutura de árvore binária
    Clientes_struct cliente;
    struct No * dir;
    struct No * esq;
}No;

Genero generos[MAX_GENEROS] = {
    {"Terror", {}, 0},
    {"Comedia", {}, 0},
    {"Acao", {}, 0},
    {"Romance", {}, 0},
    {"Drama", {}, 0}
};

No *raiz = NULL;

// Função que busca um cliente na árvore binária
No * buscar(int cpf, No *aux){
    if (aux == NULL){
        return NULL;
    }
    else if(cpf == aux -> cliente.cpf_cliente){
        return aux;
    }
    else if(cpf < aux -> cliente.cpf_cliente){
        if(aux -> esq != NULL){
            return buscar(cpf, aux -> esq);
        }
        else{
            return aux;
        }
    }
    else{
        if(aux -> dir != NULL){
            return buscar(cpf, aux -> dir);
        }
        else{
            return aux;
        }
    }
}

// Função que adiciona um cliente na árvore binária
void add_cliente(Clientes_struct cliente){  
    No *novo = malloc(sizeof(No)); 
    novo -> cliente = cliente;  
    novo -> esq = NULL;  
    novo -> dir = NULL;
    
    if (raiz == NULL){
        raiz = novo;
    }
    else{
        No *aux = raiz;
        No *pai = NULL;

        while(aux != NULL){
            pai = aux;

            if(cliente.cpf_cliente < aux -> cliente.cpf_cliente){
                aux = aux -> esq;
            }
            else{
                aux = aux -> dir;
            }
        }

        if (cliente.cpf_cliente < pai -> cliente.cpf_cliente){
            pai -> esq = novo;
        }
        else{
            pai -> dir = novo;
        }
    }
 }

 // Função que remove um cliente da árvore binária
 void remover_cliente(int cpf){
    No *pai = NULL;
    No *atual = raiz;

    while (atual != NULL && atual -> cliente.cpf_cliente != cpf){
        pai = atual;
        if(cpf < atual -> cliente.cpf_cliente){
            atual = atual -> esq;
        }
        else{
            atual = atual -> dir;
        }
    }
    if (atual == NULL){
        printf("Cliente nao encontrado!\n");
        return;     
    }
    if(atual -> esq == NULL && atual -> dir == NULL){
        if(pai == NULL){
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
    else if(atual -> esq == NULL || atual -> dir == NULL){
        No *filho = (atual -> esq != NULL) ? atual -> esq : atual -> dir;

        if (pai == NULL){
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
    else{
        No *pai_sucessor = atual;
        No *sucessor = atual -> dir;

        while(sucessor -> esq != NULL){
            pai_sucessor = sucessor;
            sucessor = sucessor -> esq;
        }

        atual -> cliente = sucessor -> cliente;

        if (pai_sucessor -> esq == sucessor){
            pai_sucessor -> esq = sucessor -> dir;
        }
        else{
            pai_sucessor -> dir = sucessor -> dir;
        }
        free(sucessor);     
    }
 }

// Função para buscar um cliente
void buscar_cliente() {
    int cpf;
    printf("Digite o CPF do cliente a ser buscado:\n> ");
    scanf("%d", &cpf);
    No *cliente = buscar(cpf, raiz);
    if (cliente != NULL) {
        printf("Cliente encontrado:\n");
        printf("Nome: %s\n", cliente->cliente.nome_cliente);
        printf("Telefone: %d\n", cliente->cliente.telefone_cliente);
        printf("CPF: %d\n", cliente->cliente.cpf_cliente);
        printf("Idade: %d\n", cliente->cliente.idade_cliente);
        printf("Endereço:\n");
        printf("  Rua: %s\n", cliente->cliente.endereco_C.rua);
        printf("  Número: %d\n", cliente->cliente.endereco_C.numero);
        printf("  Bairro: %s\n", cliente->cliente.endereco_C.bairro);
        printf("  Cidade: %s\n", cliente->cliente.endereco_C.cidade);
        printf("  Estado: %s\n", cliente->cliente.endereco_C.estado);
    } else {
        printf("Cliente não encontrado.\n");
    }
}
 
// Função para adicionar um cliente
void adicionar_cliente() {
    Clientes_struct cliente;
    printf("Digite o nome do cliente:\n> ");
    scanf(" %[^\n]s", cliente.nome_cliente);
    printf("Digite o telefone do cliente:\n> ");
    scanf("%d", &cliente.telefone_cliente);
    printf("Digite o CPF do cliente:\n> ");
    scanf("%d", &cliente.cpf_cliente);
    printf("Digite a idade do cliente:\n> ");
    scanf("%d", &cliente.idade_cliente);
    printf("Digite o endereço do cliente:\n");
    printf("Rua:\n> ");
    scanf(" %[^\n]s", cliente.endereco_C.rua);
    printf("Número:\n> ");
    scanf("%d", &cliente.endereco_C.numero);
    printf("Bairro:\n> ");
    scanf(" %[^\n]s", cliente.endereco_C.bairro);
    printf("Cidade:\n> ");
    scanf(" %[^\n]s", cliente.endereco_C.cidade);
    printf("Estado:\n> ");
    scanf(" %[^\n]s", cliente.endereco_C.estado);

    add_cliente(cliente);
    printf("Cliente adicionado com sucesso!\n");
}

// Função para listar os clientes
void listar_clientes(No *aux) {
    if (aux != NULL) {
        listar_clientes(aux->esq);
        printf("Nome: %s\n", aux->cliente.nome_cliente);
        printf("Telefone: %d\n", aux->cliente.telefone_cliente);
        printf("CPF: %d\n", aux->cliente.cpf_cliente);
        printf("Idade: %d\n", aux->cliente.idade_cliente);
        printf("Endereço:\n");
        printf("  Rua: %s\n", aux->cliente.endereco_C.rua);
        printf("  Número: %d\n", aux->cliente.endereco_C.numero);
        printf("  Bairro: %s\n", aux->cliente.endereco_C.bairro);
        printf("  Cidade: %s\n", aux->cliente.endereco_C.cidade);
        printf("  Estado: %s\n", aux->cliente.endereco_C.estado);
        listar_clientes(aux->dir);
    }
}

// Função que exibe o menu de clientes e gerencia as opções escolhidas pelo usuário
void menu_clientes() {
    int op = -1;

    while (op != 0) {
        printf("\nGerenciamento de Clientes:\n\n");
        printf("1 - Adicionar Cliente\n2 - Listar Clientes\n3 - Remover Cliente\n4 - Buscar Cliente\n0 - Sair\n\n");
        printf("Digite a opcao desejada:\n> ");
        scanf("%d", &op);

        switch (op) {
            case 0:
                break;
            case 1:
                adicionar_cliente();
                break;
            case 2:
                listar_clientes(raiz);
                break;
            case 3:
                printf("Digite o CPF do cliente a ser removido:\n> ");
                int cpf;
                scanf("%d", &cpf);
                remover_cliente(cpf);
                break;
            case 4:
                buscar_cliente();
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }
}

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

// Função que exibe o menu principal e gerencia as opções escolhidas pelo usuário
void menu_principal() {
    int op = -1;

    while (op != 0) {
        printf("\nMenu Principal:\n\n");
        printf("1 - Gerenciar Filmes\n2 - Gerenciar Clientes\n0 - Sair\n\n");
        printf("Digite a opcao desejada:\n> ");
        scanf("%d", &op);

        switch (op) {
            case 0:
                break;
            case 1:
                menu_filmes();
                break;
            case 2:
                menu_clientes();
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
    menu_principal();

    return 0;
}