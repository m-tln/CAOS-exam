#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHM_SIZE 1024
int main() {
    key_t key = 1234;
    int shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }
    char *data = (char *)shmat(shmid, NULL, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }
    printf("Read msg: %s", data);
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
}