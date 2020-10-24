#include <stdlib.h>

void *realloc (void *pont,size_t newSize){
    void *newPont = malloc(newSize);
    int tam = sizeof(pont);
    return memcpy(newPont,pont,tam);
}
