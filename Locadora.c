#include<stdio.h>

void menu(){
    printf("BEM VINDO A LOCADORA DOS FÃS DE VALÉRIA\n");
    printf("Temos os melhores filmes da região!!!\n");
    printf("Aqui você encontra os melhores filmes de comédia, ação, romance e muito mais!!!\n");
    printf("Escolha uma opção:\n");
    printf("1.Terror\n");
    printf("2.Comédia\n");
    printf("3.Ação\n");
    printf("4.Romance\n");
    printf("5.Aventura\n");
    Printf("_________________________________________________________________________");


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
    menu();
    return 0;
}