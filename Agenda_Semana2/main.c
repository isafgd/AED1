#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void menu ();
void incluir();
void listar ();
void print();

typedef struct pessoa{
    char nome[30];
    int idade;
    int altura;
}Pessoa;    

Pessoa* lista_pessoas;
void* pBuffer;
int tam;

int main(){
    tam = 0;
    pBuffer = (Pessoa *) malloc(sizeof(Pessoa));
    lista_pessoas = pBuffer;
    menu();
    return 0;
}

void menu (){
    char option[1];
    while (toupper(option[0]) != 'S'){
        printf ("\n(I) - Incluir\n(S) - Sair\nEscolha uma opção: ");
        scanf("%s", option);
        switch (toupper(option[0])){ 
            case 'I':
                incluir();
                break;
            case 'S':
                listar();
                free(pBuffer);
                exit(0);
            default:
                printf("\nOpção inválida!\n");
        }
    }
}

void incluir(){
    tam++;
    if (tam==1){
        print();
    }
    else {
        pBuffer = realloc(pBuffer,sizeof(Pessoa)*tam);
        lista_pessoas = pBuffer + sizeof(Pessoa)*(tam-1);
        print();
    }   
}

void listar (){
    lista_pessoas = pBuffer;
    for (int i = 0; i < tam; i++){
        printf ("\nNome: %s",lista_pessoas->nome);
        printf ("\n-->Idade: %d",lista_pessoas->idade);
        printf ("\n-->Altura: %d\n",lista_pessoas->altura);
        lista_pessoas++;
    }
}

void print(){
    printf("\nNome: ");
    scanf ("%s", lista_pessoas->nome);
    printf("\nIdade: ");
    scanf ("%d", &lista_pessoas->idade);
    printf("\nAltura: ");
    scanf ("%d", &lista_pessoas->altura);
}