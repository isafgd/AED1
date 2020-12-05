#include <stdio.h>

int main (){
    int n;
    printf ("n = ");
    scanf("%d",&n);
    if(n==0) {printf("%d", n);}
    int i , j;
    for ( i = j = 1; i<2 *n-1 ; i+=2, j +=i);
    printf("j = %d",j);
    return 0;
}
