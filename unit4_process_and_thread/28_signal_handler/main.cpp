#include <stdio.h>
#include <iostream>
#include <signal.h>

void handler(int signum) {
    std::cout << "caught " << signum << std::endl;
}

int main() {
    signal(SIGSEGV, &handler);
    int* p = nullptr;
    std::cout << *p;
}