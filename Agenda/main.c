#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void menu ();
void incluir ();
void apagar ();
void listar ();
void buscar ();

typedef struct agenda{
    char name[30];
    char number[15];
}agenda;

typedef struct general{
    char option[1]; //opção do menu
    char name[30]; //auxiliar
    int i; //for
    int contador; //número de contatos na agenda
    int apagados; //número de contatos apagados da agenda
}general;

void *pBuffer;
general *variaveis;
agenda *contatos;
agenda *contato_aux;

int main (){
    pBuffer = malloc(sizeof(general));
    variaveis = pBuffer;
    variaveis->contador=0;
    menu();
    return 0;
}

void menu (){
    while (toupper(variaveis->option[0]) != 'S'){
        printf ("\n(I) - Incluir\n(A) - Apagar\n(L) - Listar\n(B) - Buscar\n(S) - Sair\nEscolha uma opção: ");
        scanf("%s", variaveis->option);
        switch (toupper(variaveis->option[0])){ 
            case 'I':
                incluir();
                break;
            case 'A':   
                apagar();
                break;
            case 'L':
                listar();
                break;
            case 'B':
                buscar();
                break;
            case 'S':
                exit(0);
            default:
                printf("\nOpção inválida!\n");
        }
    }
}

void incluir (){
    variaveis->contador += 1;
    pBuffer = realloc(pBuffer,sizeof(general)+sizeof(agenda)*variaveis->contador);
    variaveis = pBuffer;
    contatos = pBuffer + sizeof(general)+sizeof(agenda)*variaveis->contador - sizeof(agenda); //perguntar pq não funciona o sizeof do pbuffer
    printf ("\nNome: ");
    scanf ("%s", contatos->name);
    printf("\nTelefone: ");
    scanf("%s", contatos->number);
}

void apagar(){
    variaveis->apagados = 0;
    contatos = pBuffer + sizeof(general);
    printf ("\nNome à ser excluído: ");
    scanf ("%s", variaveis->name);
    for(variaveis->i = 0; variaveis->i < variaveis->contador; variaveis->i++){
        if ((strcmp(contatos->name,variaveis->name))==0){
            while (variaveis->i < variaveis->contador){
                contato_aux = contatos;
                contato_aux++;
                strcpy(contatos->name,contato_aux->name);
                strcpy(contatos->number,contato_aux->number);
                contatos++;
                variaveis->i++;
            }
            variaveis->apagados++;
        }
        contatos++;
    }
    variaveis->contador = variaveis->contador - variaveis->apagados;
    pBuffer = realloc(pBuffer,sizeof(general)+sizeof(agenda)*variaveis->contador);
    variaveis = pBuffer;
}

void listar(){
    contatos = pBuffer + sizeof(general);
    for (variaveis->i = 0; variaveis->i < variaveis->contador; variaveis->i++){
        printf ("\nNome: %s",contatos->name);
        printf ("\n-->Telefone: %s\n",contatos->number);
        contatos++;
    }
}

void buscar(){
    contatos = pBuffer + sizeof(general);
    printf ("\nNome buscado: ");
    scanf("%s", variaveis->name);
    for (variaveis->i = 0; variaveis->i < variaveis->contador; variaveis->i++){
        if ((strcmp(contatos->name,variaveis->name))==0){
            printf ("\nNome: %s",contatos->name);
            printf ("\n-->Telefone: %s\n", contatos->number);
        }
        contatos++;
    }
}