#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//Declarações da Lista Duplamente Encadeada
typedef struct SDado{
    char name[30];
    char number[15];
}SDado;

typedef struct SNodo{
    struct SNodo *pPrevious;
    SDado info;
    struct SNodo *pNext;
}SNodo; 

typedef struct SLista{
    SNodo *pFirst;
    SNodo *pLast;
}SLista;
//Fim das declarações

//Declarações da Fila de Ordenação
typedef struct STipoFila{
    SDado info; //Usa o mesmo tipo de dado que a lista duplamente encadeada
    struct STipoFila *pNext;
}STipoFila;

typedef struct SFila{
    STipoFila *pFirst;
    STipoFila *pLast;
}SFila;
//Fim das declarações

typedef struct general{
    char option[1]; //opção do menu
    char name[30]; //auxiliar
    int i; 
    int j;
    int contador; //número de contatos na agenda
}general;

void menu ();
void inicia_lista();
void insere_lista();
void apaga_lista();
void lista_ordenada();
void busca_lista();
void ordena_nome();
void ordena_telefone();
void imprime_fila(SFila *fila);
void push (SDado dado);
void push_number (SDado dado);
void libera_lista();
void libera_filas();

void *pBuffer;
general *variaveis;
SLista *lista;
SFila *fila;
SFila *fila_number;

int main (){
    pBuffer = malloc(sizeof(general));
    variaveis = pBuffer;
    variaveis->contador=0;
    inicia_lista();
    menu();
    return 0;
}

void menu (){
    while (toupper(variaveis->option[0]) != 'S'){
        printf ("\n(I) - Incluir\n(A) - Apagar\n(L) - Listar\n(B) - Buscar\n(S) - Sair\nEscolha uma opção: ");
        scanf("%s", variaveis->option);
        switch (toupper(variaveis->option[0])){ 
            case 'I':
                insere_lista();
                break;
            case 'A':   
                apaga_lista();
                break;
            case 'L':
                lista_ordenada();
                break;
            case 'B':
                busca_lista();
                break;
            case 'S':
                libera_lista();
                libera_filas();
                exit(0);
            default:
                printf("\nOpção inválida!\n");
        }
    }
}

void inicia_lista (){
    lista = (SLista*) malloc(sizeof(SLista));
    lista->pFirst = NULL;
    lista->pLast = NULL;
}

void insere_lista (){
    variaveis->contador += 1;
    SNodo *aux = (SNodo*) malloc(sizeof(SNodo));
    printf ("\nNome: ");
    scanf ("%s", aux->info.name);
    printf("\nTelefone: ");
    scanf("%s", aux->info.number);
    aux->pNext = NULL;

    if(lista->pFirst==NULL){ //Lista vazia
        aux->pPrevious = NULL; //Sem elementos antes 
        lista->pFirst =  aux;
        lista->pLast = aux;
    }else{
        aux->pPrevious = lista->pLast;
        lista->pLast->pNext = aux;
        lista->pLast = aux;
    }
}

void apaga_lista(){
    printf ("\nNome à ser excluído: ");
    scanf ("%s", variaveis->name);
    SNodo *aux = (SNodo*) malloc(sizeof(SNodo));
    if(lista->pFirst==NULL){
        printf("\nA agenda está vazia!\n");
    }else{
        aux = lista->pFirst; //aux apontando para o primeiro elemento da lista
        while (aux!=NULL){
            if(strcmp(aux->info.name,variaveis->name) == 0){
                if (aux==lista->pFirst){ //Se o elemento apagado for o primeiro da lista
                    lista->pFirst = aux->pNext;
                }else{
                    if(aux==lista->pLast){ //Se o elemento apagado for o último da lista
                        lista->pLast = aux->pPrevious;
                    }else{
                        aux->pPrevious->pNext = aux->pNext;
                        aux->pNext->pPrevious = aux->pPrevious;
                    }
                }
                free(aux);
                variaveis->contador--;                
            }
            aux = aux->pNext; //aux apontando para o próximo elemento da lista
        }
    }
}

void lista_ordenada(){
    printf("\nEscolha uma opção de ordenação: \n\n(1) - Ordem alfabética\n(2) - Ordem crescente de telefone\n\nOpção: ");
    scanf ("%d", &variaveis->i);
    if (variaveis->i==1){
        ordena_nome();
    }else{
        if (variaveis->i==2){
            ordena_telefone();
        }else{
            printf("\nOpção inválida\n");
        }
    }
}

void ordena_nome(){
    fila = (SFila*) malloc(sizeof(SFila)); //Fila ordenada é criada quando o usuário escolhe o padrão de ordenação
    fila->pFirst = NULL;
    fila->pLast = NULL;

    SNodo *aux = (SNodo*) malloc(sizeof(SNodo));
    SDado *dado = (SDado*) malloc(variaveis->contador * sizeof(SDado));
    SDado *aux_dado = (SDado*) malloc(sizeof(SDado));
    if(lista->pFirst==NULL){
        printf("\nA agenda está vazia!\n");
    }else{
        aux = lista->pFirst;
        for(variaveis->i=0;variaveis->i<variaveis->contador;variaveis->i++){
            strcpy(dado[variaveis->i].name,aux->info.name);
            strcpy(dado[variaveis->i].number,aux->info.number);
            aux = aux->pNext;
        }
        
        for(variaveis->i = 1; variaveis->i < variaveis->contador; variaveis->i++){
            for(variaveis->j = 1; variaveis->j < variaveis->contador; variaveis->j++){
                if (strcmp(dado[variaveis->j-1].name, dado[variaveis->j].name) > 0) {
                    strcpy(aux_dado->name, dado[variaveis->j-1].name);
                    strcpy(aux_dado->number, dado[variaveis->j-1].number);\

                    strcpy(dado[variaveis->j-1].name, dado[variaveis->j].name);
                    strcpy(dado[variaveis->j-1].number, dado[variaveis->j].number);

                    strcpy(dado[variaveis->j].name, aux_dado->name);
                    strcpy(dado[variaveis->j].number, aux_dado->number);
                }
            }
        }
        for(variaveis->i = 0; variaveis->i < variaveis->contador; variaveis->i++){
            push(dado[variaveis->i]);
        }
    }
    imprime_fila(fila);
}

void push(SDado dado){
    STipoFila *pNovo;
    pNovo = (STipoFila*) malloc(sizeof(STipoFila));
    pNovo->info = dado;
    pNovo->pNext = NULL;

    if(fila->pLast != NULL){
        fila->pLast->pNext = pNovo;
    }else{
        fila->pFirst = pNovo;
    }

    fila->pLast = pNovo;
}

void push_number(SDado dado){
    STipoFila *pNovo;
    pNovo = (STipoFila*) malloc(sizeof(STipoFila));
    pNovo->info = dado;
    pNovo->pNext = NULL;

    if(fila_number->pLast != NULL){
        fila_number->pLast->pNext = pNovo;
    }else{
        fila_number->pFirst = pNovo;
    }

    fila_number->pLast = pNovo;
}

void ordena_telefone(){
    fila_number = (SFila*) malloc(sizeof(SFila)); //Fila ordenada é criada quando o usuário escolhe o padrão de ordenação
    fila_number->pFirst = NULL;
    fila_number->pLast = NULL;

    SNodo *aux = (SNodo*) malloc(sizeof(SNodo));
    SDado *dado = (SDado*) malloc(variaveis->contador * sizeof(SDado));
    SDado *aux_dado = (SDado*) malloc(sizeof(SDado));
    if(lista->pFirst==NULL){
        printf("\nA agenda está vazia!\n");
    }else{
        aux = lista->pFirst;
        for(variaveis->i=0;variaveis->i<variaveis->contador;variaveis->i++){
            strcpy(dado[variaveis->i].name,aux->info.name);
            strcpy(dado[variaveis->i].number,aux->info.number);
            aux = aux->pNext;
        }
        
        for(variaveis->i = 1; variaveis->i < variaveis->contador; variaveis->i++){
            for(variaveis->j = 1; variaveis->j < variaveis->contador; variaveis->j++){
                if (strcmp(dado[variaveis->j-1].number, dado[variaveis->j].number) > 0) {
                    strcpy(aux_dado->name, dado[variaveis->j-1].name);
                    strcpy(aux_dado->number, dado[variaveis->j-1].number);\

                    strcpy(dado[variaveis->j-1].name, dado[variaveis->j].name);
                    strcpy(dado[variaveis->j-1].number, dado[variaveis->j].number);

                    strcpy(dado[variaveis->j].name, aux_dado->name);
                    strcpy(dado[variaveis->j].number, aux_dado->number);
                }
            }
        }
        for(variaveis->i = 0; variaveis->i < variaveis->contador; variaveis->i++){
            push_number(dado[variaveis->i]);
        }
    }

    imprime_fila(fila_number);
}

void imprime_fila(SFila *fila){
    STipoFila *pNodo;
    if(fila->pFirst==NULL){
        printf("\nA agenta está vazia!\n");
    }else{
        for(pNodo = fila->pFirst; pNodo != NULL; pNodo = pNodo->pNext){
            printf ("\nNome: %s",pNodo->info.name);
            printf ("\n-->Telefone: %s\n", pNodo->info.number);
        }
    }
}

void busca_lista(){
    printf ("\nNome buscado: ");
    scanf("%s", variaveis->name);
    SNodo *aux = (SNodo*) malloc(sizeof(SNodo));
    if(lista->pFirst==NULL){
        printf("\nA agenda está vazia!\n");
    }else{
        aux = lista->pFirst; //aux apontando para o primeiro elemento da lista
        while (aux!=NULL){
            if(strcmp(aux->info.name,variaveis->name) == 0){
                printf ("\nNome: %s",aux->info.name);
                printf ("\n-->Telefone: %s\n", aux->info.number);
            }
            aux = aux->pNext; //aux apontando para o próximo elemento da lista
        }
    }
}

void libera_lista(){
    SNodo *aux = (SNodo*) malloc(sizeof(SNodo));
    SNodo *aux_free = (SNodo*) malloc(sizeof(SNodo));
    if(lista!=NULL){
        aux = lista->pFirst;
        while (aux!=NULL){
            aux_free = aux->pNext;
            free(aux);
            aux = aux_free;
        }
        free(aux_free);
        free(lista);
    }
}

void libera_filas(){
    STipoFila *pNodo;
    if(fila!=NULL){
        for(pNodo = fila->pFirst; pNodo != NULL; pNodo = pNodo->pNext){
            free(pNodo);
        }
        free(fila);
    }
    if(fila_number!=NULL){
        for(pNodo = fila_number->pFirst; pNodo != NULL; pNodo = pNodo->pNext){
            free(pNodo);
        }
        free(fila_number);
    }
    
}

