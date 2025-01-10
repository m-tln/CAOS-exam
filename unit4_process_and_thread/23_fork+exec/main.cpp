#include <iostream>
#include <unistd.h>

int main() {
    int pid = fork();
    if (pid == 0) {
        std::cout << "Hello I'm child\n";
    } else if (pid > 0) {
        sleep(1);
        std::cout << "Hello I'm parent\n";
        char* argv[] = {"/bin/ls", "/Users/matveitulin", NULL};
        char* envp[] = {NULL};
        std::cout << "execve:\n";
        int err = execve("/bin/ls", argv, envp);
        if (err == -1) {
            std::cout << "Execve failed with errno: " << errno;
            return 1;
        }
    } else {
        std::cout << "Fork failed with errno: " << errno;
        return 1;
    }
}