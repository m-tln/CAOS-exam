#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/mman.h>

int main() {
    int fd = open("file.txt", O_RDWR);
    if (fd == -1) {
        std::cout << "Can't open file. Errno:" << errno;
        return 1;
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        std::cout << "Can't info about file. Errno" << errno;
        return 1;
    }

    char* str = (char*)mmap(NULL , st.st_size , 
                                PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); //MAP_PRIVATE
    if (str == MAP_FAILED) {
        std::cout << "Can't allocate data. Errno" << errno;
        return 1;
    }
    printf("%s\n", str);
    str[0] = 'M';
    if (msync(str, st.st_size, MS_SYNC) == -1) {
        std::cout << "Can't sync. Errno" << errno;
        return 1;
    }
    if (munmap(str, st.st_size) == -1) {
        std::cout << "Can't deallocate data. Errno" << errno;
        return 1;
    }
}