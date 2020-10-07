#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
void menu ();
char* insert_name (char* names);
void remove_name (char* names);
void list_names (char* names);
void read_name (char* name);

int main (){
    menu(); //Chama o menu pela primeira vez
}

void menu (){  
    char* names = NULL; //String que  vai armazenar todos os nomes //Inicializa com tamanho zero
    char* ret = NULL;
    char option[1];
    while (toupper(option[0]) != 'S'){
        printf ("\n(I) - Inserir nome\n(R) - Remover nome\n(L) - Listar nomes\n(S) - Sair\nEscolha uma opção: ");
        scanf("%s", option);
        printf("Inicio: %s",names);
        switch (toupper(option[0]))
        {
        case 'I':
            ret = insert_name(names);
            printf("Saida: %s",ret);
            names = ret;
            break;
        case 'R':
            remove_name(names);
            break;
        case 'L':
            list_names(names);
            break;
        case 'S':
            exit(0);
        default:
            printf("\nOpção inválida!\n");
        }
    }
}

//Incluir o nome + ";" + "\0"
char* insert_name (char* names){
    printf("Entrada: %s",names);
    char* name = (char*) malloc(50); //Tamanho máximo do nome
    read_name(name);
    if (names == NULL){
        names = (char*) malloc(strlen(name) + 2); //Primeiro nome
        strcpy (names,name);
        strcat(names,";");
        return names;
    }else {
        names = (char*) realloc(names,strlen(names) + strlen(name) + 2); //Redimensionou
        strcat(names,name);
        strcat(names,";");
        return names;
    }
    printf ("%s", names);
    free(name);
}

void remove_name (char* names){
    
}

void list_names (char* names){

}

void read_name (char* name){
    printf ("\nNome: ");
    scanf("%s", name);
}
