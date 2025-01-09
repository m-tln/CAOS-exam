#include <sys/mman.h>
#include <unistd.h>

int main() {
    void* ptr = mmap(NULL, 1024, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    munmap(ptr, 1024);
}