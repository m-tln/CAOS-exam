#include <stdio.h>

int main() {
    int a = 5, b = 10;

    asm (
        "mov %0, %eax;"
        "mov %1, %0;" 
        "mov %%eax, %1;"
        : "=r"(a), "=r"(b)
        : "0"(a), "1"(b)  
        : "eax"          
    );

    printf("a = %d, b = %d\n", a, b);


    return 0;
}
