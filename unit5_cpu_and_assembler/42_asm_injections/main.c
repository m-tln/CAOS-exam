#include <stdio.h>

unsigned long long get_cycles() {
    unsigned int count_low, count_high;

    asm volatile (
        "mrc p15, 0, %0, c9, c13, 0;"   // Read the cycle count (low part)
        "mrc p15, 0, %1, c9, c13, 1;"   // Read the cycle count (high part)
        : "=r"(count_low), "=r"(count_high)   // Output operands
        :
        : "memory"  // Memory is clobbered
    );

    // Combine the high and low parts to get the full cycle count
    return ((unsigned long long)count_high << 32) | count_low;
}

int main() {
    int a = 5, b = 10;

    // asm (
    //     "mov %0, %eax;"
    //     "mov %1, %0;" 
    //     "mov %%eax, %1;"
    //     : "=r"(a), "=r"(b)
    //     : "0"(a), "1"(b)  
    //     : "eax"          
    // );

    printf("a = %d, b = %d\n", a, b);


    unsigned long long start, end;

    start = get_cycles();
    for (int i = 0; i < 1000000; ++i) {
        for (int j = 0; j < 1000000; ++j) {
            if (i == j) {
                i = j;
            }
        }
    }
    end = get_cycles();

    printf("CPU Cycles: %llu\n", end - start);

    return 0;
}