#include <stdio.h>
int x, y, z;

void func1(){
    int a = 1;
    int b = 2;
    x = 1;
    y = 2;
    z = 3;
    printf("%d, %d, %d, %d, %d\n",x, y, z, a, b);
}

void func2(){
    int a = 5;
    printf("%d, %d, %d, %d", x, y, z, a);
}