#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//Declaração das funções
void menu ();
char* insert_name (char* names);
char* remove_name (char* names);
void list_names (char* names);
void read_name (char* name);

int main (){
    menu(); //Chama o menu pela primeira vez
}

void menu (){  
    char* names = NULL; //String que  vai armazenar todos os nomes //Inicializa com tamanho zero
    char* aux = NULL;
    char option[1];
    while (toupper(option[0]) != 'S'){
        printf ("\n(I) - Inserir nome\n(R) - Remover nome\n(L) - Listar nomes\n(S) - Sair\nEscolha uma opção: ");
        scanf("%s", option);
        switch (toupper(option[0]))
        {
        case 'I':
            aux = insert_name(names);
            names = aux;
            break;
        case 'R':
            aux = remove_name(names);
            names = aux;
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

//Incluir o nome + ";" 
char* insert_name (char* names){
    char* name = (char*) malloc(50); //Tamanho máximo do nome
    read_name(name);
    if (names == NULL){
        names = (char*) malloc(strlen(name) + 1); //Primeiro nome
        strcpy (names,name);
        strcat(names,";");
    }else {
        names = (char*) realloc(names,strlen(names) + strlen(name) + 1); //Redimensionou
        strcat(names,name);
        strcat(names,";");
    }
    return names;
}

char* remove_name (char* names){
    char* name = (char*) malloc(50); //Tamanho máximo do nome
    char* new_names = NULL;
    int cont = 0; //Conta quantas vezes o número que se deseja ser excluído aparece
    read_name(name);
    if (names == NULL){
        printf ("Nenhum nome foi inserido.\n\n");
    }else{
        for (int i=0; i <= strlen(names)-1; i++){ //Percorre toda a String
            char* comp = (char*) malloc(50);
            int j = 0;
            while (names[i] != ';'){
                comp[j] = names[i];
                i++;
                j++;
            }if ((strcmp(comp,name))==0){ //Compara o nome q se quer excluir com um nome da String
                cont++;
            }else{
                if (new_names == NULL){
                    new_names = (char*) malloc(strlen(comp) + 1); //Primeiro nome
                    strcpy (new_names,comp);
                    strcat(new_names,";");
                }else{
                    new_names = (char*) realloc(new_names,strlen(names) + strlen(comp) + 1); //Redimensionou
                    strcat(new_names,comp);
                    strcat(new_names,";");
                }           
            }
        }
        names = (char*) realloc(names,strlen(names) - ((strlen(name) - 1)*cont));   //Diminui o names 
        names = new_names; //Passa os nomes que não serão excluídos para a String
    }
    return names;
}




void list_names (char* names){
    if (names == NULL){
        printf ("Nenhum nome foi inserido.\n\n");
    }else{
        printf ("\nNomes Listados:\n");
        for (int i=0; i <= strlen(names)-1; i++){ //Percorre toda a String
            while (names[i] != ';'){
                printf("%c",names[i]);
                i++;
            }
            printf ("\n"); //Pula a linha quando encontra um ";"
        }
    }
}

void read_name (char* name){
    printf ("\nNome: ");
    scanf("%s", name);
}