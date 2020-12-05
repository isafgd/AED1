#include<stdio.h>

int main()
{
    int mat[2][2] = {{1,2},{3,4}};
    int *p = &mat[0][0];
    int i;
    for (i=0;i<4;i++)
    printf("%d\n",*(p+i));
    system("pause");
}