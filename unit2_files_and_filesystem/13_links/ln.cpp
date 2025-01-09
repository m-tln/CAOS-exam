#include <unistd.h>
#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {
    int err;
    if (std::strcmp(argv[1], "-s") == 0) {
        err = symlink(argv[2], argv[3]);
    } else {
        err = link(argv[1], argv[2]);
    }
    if (err == -1) {
        std::cout << "Program failed with errno: " << errno;
    }
}