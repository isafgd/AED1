#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (){
    int* pont = (int*) malloc(sizeof(int));
    pont = realloc(pont,sizeof(int)*3);
    pont[0] = 1;
    pont[1] = 2;
    pont[2] = 3;
    printf ("%d\n%d\n%d\n",pont[0],pont[1],pont[2]);
    free(pont);
    return 0;
}

void *realloc (void *pont,size_t newSize){
    void *newPont = malloc(newSize);
    int tam = sizeof(pont);
    return memcpy(newPont,pont,tam);
    free(newPont);
}
