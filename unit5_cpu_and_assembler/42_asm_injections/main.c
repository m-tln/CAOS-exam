#include <stdio.h>
#include <stdint.h>

static inline uint64_t rdtsc() {
    uint32_t lo, hi;
    __asm__ volatile("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

int main() {
    uint64_t start, end;
    int i;
    int sum = 0;
    start = rdtsc();

    for (i = 0; i < 100000; i++) {
      sum += i;
    }

    end = rdtsc();

    printf("Elapsed cycles: %llu\n", (unsigned long long)(end - start));
    return 0;
}