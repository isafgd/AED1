#include <stdio.h>
#include <stdlib.h>

void separaPalavra (char *linha);
void imprimePalavra (char *palavra);

int main (){
    char *linha = malloc (80 * sizeof(char)); //Vetor que vai armazenar 80 caracteres
    printf ("Qual sua frase? ");
    gets(linha);
    separaPalavra (linha);
    return 0;
}

void separaPalavra (char *linha){
    int i = 0;
    int j = 0;
    char *palavra = malloc (80 * sizeof(char));
    while (linha[i]!='\0'){
        if (linha[i] == ' '){
            palavra[j] = '|';
            i++;
            j++;
        }
        palavra[j] = linha [i];
        j++;
        i++;
    }
    imprimePalavra(palavra);
}

void imprimePalavra (char *palavra){
    int i = 0;
    while (palavra[i] != '\0'){
        if (palavra[i]=='|'){
            printf ("\n");
            i++;
        }
        printf("%c",palavra[i]);
        i++;
    }
}