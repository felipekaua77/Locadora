#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct cadastro_pessoa {
    char *nome;
    int id;
    struct cadastro_filme_pessoa *prox;
}cadastro_pessoa;

typedef struct cadastro_filme {
    char *nome_filme;
    char *genero_filme;
    float preco_filme;
    struct cadastro_filme *prox;
}cadastro_filme;

typedef struct agendametos{
    int id;
    int id_filme;
    int id_pessoa;
    int data;
    int hora;
    agendamentos *prox;
}agendamentos;

cadastro_pessoa* adicionar_pessoa(cadastro_pessoa *aux, char *nome, int id){
    cadastro_pessoa *novo = (cadastro_pessoa*)malloc(sizeof(cadastro_pessoa));
    novo->nome = nome;
    novo->id = id;
    novo->prox = aux;
    return novo;
}

cadastro_filme* adicionar_filme(cadastro_filme *aux, char *nome_filme, char *genero_filme, float preco_filme){
    cadastro_filme *novo = (cadastro_filme*)malloc(sizeof(cadastro_filme));
    novo->nome_filme = nome_filme;
    novo->genero_filme = genero_filme;
    novo->preco_filme = preco_filme;
    novo->prox = aux;
    return novo;
}

agendamentos* adicionar_agendamento(agendamentos *aux, int id, int id_filme, int id_pessoa, int data, int hora){
    agendamentos *novo = (agendamentos*)malloc(sizeof(agendamentos));
    novo->id = id;
    novo->id_filme = id_filme;
    novo->id_pessoa = id_pessoa;
    novo->data = data;
    novo->hora = hora;
    novo->prox = aux;
    return novo;
}

//Esses prints podem ser meio inuteis no futuro, considerem isso ao codar.
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

void menu_filme_terror(){
    printf("1.Sexta feira 13\n");
    printf("2.O Exorcista\n");
    printf("3.Invocação do Mal\n");
    printf("4.O Chamado\n");
    printf("5.Hora do pesadelo\n");
    printf("6.sair\n");
    int opcao;
    scanf("%d", &opcao);   
    	
}

void menu_filme_comedia(){

}

void menu_filme_acao(){

}

void menu_filme_romance(){
    printf("Infelizmente estamos sem filmes desta categoria :c\n");
    pritnf("1.sair");
}

void menu_filme_aventura(){

}


int main(){
    srand(time(NULL));
    menu();
    return 0;
}