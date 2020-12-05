#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void leNumeros(float *vetor, int n);
void excluiDuplicados(float *vetor, int n);
void imprimeNovoVetor(float *vetor, int n);

int main (){
    int n;
    printf ("Qual o número de elementos? ");
    scanf("%d", &n);
    float *vetor = malloc(n * sizeof(float));
    leNumeros(vetor, n);
}

void leNumeros(float *vetor, int n) {
    int i;
    for (i=0;i<n;i++){
        printf ("Qual o número? ");
        scanf("%f", &vetor[i]);
    }
    excluiDuplicados (vetor, n);
}

void excluiDuplicados(float *vetor, int n) {
    int i;
    int j;
    int k;
    int aux;
    for (i=0;i<n;i++){
        aux = vetor[i];
        for (j=i+1;j<n;j++){
            if (aux == vetor[j]){
                for (k=j;k<n;k++){
                    vetor[k] = vetor[k+1];
                }
                n--;
            }
        }
    }
    imprimeNovoVetor(vetor, n);
}

void imprimeNovoVetor(float *vetor, int n) {
    for (int i=0; i<n ; i++){
        printf("%.2f\n", vetor[i]);
    }
}