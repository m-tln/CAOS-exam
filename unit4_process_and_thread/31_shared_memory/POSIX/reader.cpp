#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#define SHM_NAME "/shared_memory_example"
#define SHM_SIZE 1024
int main() {

    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    char *shared_memory = (char*)mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE,
    MAP_SHARED, shm_fd, 0);
    if (shared_memory == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    printf("%s", shared_memory);

    munmap(shared_memory, SHM_SIZE);
    close(shm_fd);

    shm_unlink(SHM_NAME);
    return 0;
}