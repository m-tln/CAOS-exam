#include <seccomp.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
void seccomp_setup() {
    scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_ALLOW);
    if (ctx == nullptr) {
        std::cout << "seccomp_init failed" << std::endl;
        exit(1);
    }
    if (seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(clone), 0) != 0) {
        std::cout << "seccomp_rule_add failed" << std::endl;
        seccomp_release(ctx);
        exit(1);
    }
    if (seccomp_load(ctx) != 0) {
        std::cout << "seccomp_load failed" << std::endl;
        seccomp_release(ctx);
        exit(1);
    }
    seccomp_release(ctx);
}

int main() {
    seccomp_setup();
    fork();
    std::cout << errno;
}