#include <iostream>
#include <sys/mman.h>
#include <sched.h>
#include <sys/wait.h>
class Thread {
using Callable = void(*)();
public:
Thread(Callable func): func(func) {
    // stack = mmap(
    //              NULL, STACK_SIZE, PROT_READ|PROT_WRITE,
    //              MAP_PRIVATE|MAP_ANONYMOUS|MAP_STACK,
    //              -1, 0);
    // pid = clone(
    //             threadRoutine, stack,
    //             CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_THREAD|
    //             CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|
    //             CLONE_CHILD_CLEARTID, (void*)func);
}
void join() {
    int status;
    waitpid(pid, &status, 0);
    pid = -1;
}
~Thread() {
    if (pid > 0) {
        std::terminate();
    }
    munmap(stack, STACK_SIZE);
}
private:
    static int threadRoutine(void* arg) {
        Callable routine = reinterpret_cast<Callable>(arg);
        routine();
        return 0;
    }
    static const int STACK_SIZE = 8392704;
    Callable func;
    void* stack;
    int pid = -1;
};
void f() {
    for (int i = 0; i < 100; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
int main() {
    Thread t(f);
    f();
    t.join();
}