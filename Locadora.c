#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct cadastro_pessoa {
    char *nome;
    int id;
    struct cad_filme_pessoa;
}cadastro_pessoa;

typedef struct cadastro_filme {
    char *nome_filme;
    char *genero_filme;
    float preco_filme;
}cadastro_filme;

typedef struct agendametos{
    int id;
    int id_filme;
    int id_pessoa;
    int data;
    int hora;
}agendamentos;

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
    //Felps
    srand(time(NULL));
    menu();
    return 0;
}