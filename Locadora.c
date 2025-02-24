#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct cadastro_pessoa {
    char *nome;
    int id;
    struct cad_filme_pessoa;
}cadastro_pessoa;

typedef struct filme{
    char nome_filme[100];
    char genero_filme[50];
    float preco_filme;
    int disponivel;// 1 - Disponivel, 0 - Alugado
}Filme;

typedef struct agendametos{
    int id;
    int id_filme;
    int id_pessoa;
    int data;
    int hora;
}agendamentos;

void gerenciar_filme(){
    int op = 0;
    printf("Gerenciamento de Filmes:\n\n");
    printf("1 - Cadastrar Filme \n2 - Editar Filme \n3 - Excluir Filme \n4 - Listar Filmes \n5 - Voltar\n\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &op);

    switch(op){
        case 1:
            cadastrar_filme();
            break;
        case 2:
            break;
        case 3:
            excluir_filme();
            break;
        case 4:
            listar_filmes();
            break;
        case 5:
            menu();
            break;
        default:
            printf("Opção invalida.\n");
            break;
    }
}

void cadastrar_filme(){
    Filme *novo_filme = malloc(sizeof(Filme));
    printf("Digite o nome do filme: ");
    scanf("%s", novo_filme->nome_filme);
    printf("Digite o genero do filme: ");
    scanf("%s", novo_filme->genero_filme);
    printf("Digite o preco do filme: ");
    scanf("%f", novo_filme->preco_filme);
    novo_filme->disponivel = 1;
}

void editar_filme(Filme* filme){
    printf("Digite o nome do filme: ");
    scanf("%s", filme->nome_filme);
    printf("Digite o genero do filme: ");
    scanf("%s", filme->genero_filme);
    printf("Digite o preco do filme: ");
    scanf("%f", filme->preco_filme);
}

void menu(){
    int op = 0;
    printf("BEM VINDO A LOCADORA DOS FÃS DE VALÉRIA\n");
    printf("Temos os melhores filmes da região!!!\n");
    printf("Aqui você encontra os melhores filmes de comédia, ação, romance e muito mais!!!\n");
    printf("Escolha uma opção:\n");
    printf("1.Terror\n");
    printf("2.Comédia\n");
    printf("3.Ação\n");
    printf("4.Romance\n");
    printf("5.Aventura\n");
    printf("Digite aqui: ");
    scanf("%d", &op);
    return 0;
}

//Felps
int main(){
    srand(time(NULL));
    int linhas = 10;
    int colunas = 10;
    
    menu();

    return 0;
}