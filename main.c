#include "main.h"
#include "filmes.c"

//Função que inicia o menu principal do programa
void menu_principal(){
    int opcao = -1;

    while(opcao!=0){
        printf("\n////////// Menu Principal //////////\n\n");
        printf("1 - Gerenciar Filmes\n");
        printf("2 - Gerenciar Clientes\n");
        printf("3 - Gerenciar Alugueis\n");
        printf("0 - Encerrar o programa\n");
        printf("\nDigite a opcao desejada:\n> ");
        scanf("%d", &opcao);

        switch(opcao){
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            case 1:
                menu_filmes();
                break;
            case 2:
                menu_clientes();
                break;
            case 3:
                menu_alugueis();
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
}

int main(){
    menu_principal();

    return 0;
}