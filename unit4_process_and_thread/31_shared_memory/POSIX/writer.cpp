#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#define SHM_NAME "/shared_memory_example"
#define SHM_SIZE 1024
int main() {

    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        exit(1);
    }   

    char* shared_memory = (char*)mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE,
    MAP_SHARED, shm_fd, 0);
    if (shared_memory == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    fgets(shared_memory, SHM_SIZE, stdin);

    munmap(shared_memory, SHM_SIZE);
    close(shm_fd);
    getchar();
}