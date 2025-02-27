#include "cabecalho.h"

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

 // Função que remove um cliente da árvore binária
 void remover_cliente(int cpf){
    No *pai = NULL;
    No *atual = raiz;

    while(atual != NULL && atual -> cliente.cpf_cliente != cpf){
        pai = atual;
        if(cpf < atual -> cliente.cpf_cliente){
            atual = atual -> esq;
        }
        else{
            atual = atual -> dir;
        }
    }
    if(atual == NULL){
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

        if(pai == NULL){
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

        if(pai_sucessor -> esq == sucessor){
            pai_sucessor -> esq = sucessor -> dir;
        }
        else{
            pai_sucessor -> dir = sucessor -> dir;
        }
        free(sucessor);     
    }
 }

// Função para buscar um cliente
void buscar_cliente(){
    int cpf;
    printf("Digite o CPF do cliente a ser buscado:\n> ");
    scanf("%d", &cpf);
    No *cliente = buscar(cpf, raiz);

    if(cliente != NULL){
        printf("Cliente encontrado:\n");
        printf("Nome: %s\n", cliente->cliente.nome_cliente);
        printf("Telefone: %d\n", cliente->cliente.telefone_cliente);
        printf("CPF: %d\n", cliente->cliente.cpf_cliente);
        printf("Idade: %d\n", cliente->cliente.idade_cliente);
        printf("Endereco:\n");
        printf("  Rua: %s\n", cliente->cliente.endereco_C.rua);
        printf("  Numero: %d\n", cliente->cliente.endereco_C.numero);
        printf("  Bairro: %s\n", cliente->cliente.endereco_C.bairro);
    } else{
        printf("Cliente nao encontrado.\n");
    }
}
 
// Função para adicionar um cliente
void adicionar_cliente(){
    Clientes_struct cliente;
    printf("Digite o nome do cliente:\n> ");
    scanf(" %[^\n]s", cliente.nome_cliente);
    printf("Digite o telefone do cliente:\n> ");
    scanf("%d", &cliente.telefone_cliente);
    printf("Digite o CPF do cliente:\n> ");
    scanf("%d", &cliente.cpf_cliente);
    printf("Digite a idade do cliente:\n> ");
    scanf("%d", &cliente.idade_cliente);
    printf("Digite o endereco do cliente:\n");
    printf("Rua:\n> ");
    scanf(" %[^\n]s", cliente.endereco_C.rua);
    printf("Numero:\n> ");
    scanf("%d", &cliente.endereco_C.numero);
    printf("Bairro:\n> ");
    scanf(" %[^\n]s", cliente.endereco_C.bairro);

    No *novo = malloc(sizeof(No)); 
    novo -> cliente = cliente;  
    novo -> esq = NULL;  
    novo -> dir = NULL;
    
    if(raiz == NULL){
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

        if(cliente.cpf_cliente < pai -> cliente.cpf_cliente){
            pai -> esq = novo;
        }
        else{
            pai -> dir = novo;
        }
    }

    printf("Cliente adicionado com sucesso!\n");
}

// Função para listar os clientes
void listar_clientes(No *aux){
    if(aux != NULL){
        listar_clientes(aux->esq);
        printf("Nome: %s\n", aux->cliente.nome_cliente);
        printf("Telefone: %d\n", aux->cliente.telefone_cliente);
        printf("CPF: %d\n", aux->cliente.cpf_cliente);
        printf("Idade: %d\n", aux->cliente.idade_cliente);
        printf("Endereco:\n");
        printf("  Rua: %s\n", aux->cliente.endereco_C.rua);
        printf("  Numero: %d\n", aux->cliente.endereco_C.numero);
        printf("  Bairro: %s\n", aux->cliente.endereco_C.bairro);
        listar_clientes(aux->dir);
    }
}

// Função que exibe o menu de clientes e gerencia as opções escolhidas pelo usuário
void menu_clientes(){
    int op = -1;

    while(op != 0){
        printf("\nGerenciamento de Clientes:\n\n");
        printf("1 - Adicionar Cliente\n2 - Listar Clientes\n3 - Remover Cliente\n4 - Buscar Cliente\n0 - Voltar\n\n");
        printf("Digite a opcao desejada:\n> ");
        scanf("%d", &op);

        switch(op){
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