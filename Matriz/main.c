#include <stdio.h>
#include <stdlib.h>

int ** criaMatriz (int m, int n);
void leiaMatriz (int **mat, int m, int n);
int somaMatriz (int **mat, int m, int n);
int* colunaMatriz (int **mat, int m, int n, int ncoluna);
void liberaMatriz (int **mat, int n);
void imprimeMatriz (int **mat, int m, int n);
void imprimeVetor (int *vet, int n);
void menu(int **mat);
void print();
void printNColuna();

int m, n, ncoluna;
int soma = 0;

int main(){
    int **matriz = NULL;
    menu(matriz);
    return 0;
}

void menu (int **mat){
    int option = 0;
    while (option != 6){
        printf ("\n(1) - Cria a Matriz\n(2) - Leitura da Matriz\n(3) - Adição dos elementos da Matriz\n(4) - Vetor de uma coluna da Matriz\n(5) - Imprimir a Matriz\n(6) - Sair\nEscolha uma opção: ");
        scanf("%d", &option);
        switch (option){ 
            case 1:
                if (mat != NULL){
                    liberaMatriz(mat,n);
                }
                print();
                mat = criaMatriz(m,n);
                break;
            case 2:
                leiaMatriz (mat,m,n);
                break;
            case 3:
                soma = somaMatriz (mat,m,n);
                printf ("\nSoma = %d\n", soma);
                break;
            case 4:
                printNColuna();
                int* coluna;
                coluna = colunaMatriz (mat,m,n,ncoluna);
                imprimeVetor (coluna,m);
                break;
            case 5:
                imprimeMatriz (mat,m,n);
                break;
            case 6:
                liberaMatriz (mat,n);
                exit(0);
            default:
                printf("\nOpção inválida!\n");
                break;
        }
    }
}

void print(){
    printf ("\n");
    printf ("Valor de M: ");
    scanf("%d", &m);
    printf ("Valor de N: ");
    scanf("%d", &n);
}

void printNColuna(){
    printf ("\n");
    printf ("Número da coluna: ");
    scanf("%d", &ncoluna);
}

int ** criaMatriz (int m, int n){
    int **mat;
    mat = (int**) malloc (m * sizeof(int*));
    for (int i=0;i<m;i++){
        mat[i] = (int*) malloc (n * sizeof(int));
    }
    return mat;
}

void leiaMatriz (int **mat, int m, int n){
    printf ("\n");
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            printf ("Posição (%d,%d): ", i,j);
            scanf ("%d", &mat[i][j]);
        }
    }
}

int somaMatriz (int **mat, int m, int n){
    int soma = 0;
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            soma += mat[i][j];
        }
    }
    return soma;
}

int* colunaMatriz (int **mat, int m, int n, int ncoluna){
    int *coluna = (int*) malloc(m * sizeof(int));
    for (int i=0;i<m;i++){
        coluna[i] = mat[i][ncoluna];
    }
    return coluna;
}

void imprimeVetor (int *vet, int n){
    for (int i=0;i<n;i++){
        printf ("\n%d",vet[i]);
    }
    printf ("\n");
}

void imprimeMatriz (int **mat, int m, int n){
    printf ("\n");
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            printf ("%d   ", mat[i][j]);
        }
        printf("\n");
    }
}

void liberaMatriz (int **mat, int n){
    for (int i=0;i<n;i++){
        free(mat[i]);
    }
    free(mat);
}


