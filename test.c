#include <stdio.h>



int main(void){


    int a = 500;
    int b =  100;
    printf("%d a ===> \n", a);
    printf("%d b =====> \n", b);

    a = a + b;
    b = a - b;
    a = a - b;

    printf("%d a ===> \n", a);
    printf("%d b =====> \n", b);
}