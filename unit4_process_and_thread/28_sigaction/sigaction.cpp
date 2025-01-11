#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
void handler(int signum) {
    std::cout << "signal occurred\n";
    sleep(5);
}
int main() {
    struct sigaction sa;
    sa.sa_handler = &handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_NODEFER;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        std::cout << "sigaction";
        exit(1);
    }
    sleep(5);
    int* ptr = NULL;
    *ptr = 10;
    std::cout << "after segfault";

    sigfillset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR1);
    sigaction(SIGINT, &sa, NULL);
}