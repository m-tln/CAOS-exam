#include <iostream>
#include <sys/mman.h>
#include <sched.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>

class Thread {
    using Callable = void(*)();
public:
    Thread(Callable func) : func(func), stack(nullptr), pid(-1) {
        stack = mmap(nullptr, STACK_SIZE, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
        if (stack == MAP_FAILED) {
            perror("mmap");
            throw std::runtime_error("Failed to allocate stack memory");
        }

        pid = clone(threadRoutine, static_cast<char*>(stack) + STACK_SIZE,
                    CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND |
                    CLONE_SYSVSEM | SIGCHLD, reinterpret_cast<void*>(func));
        if (pid == -1) {
            perror("clone");
            munmap(stack, STACK_SIZE);
            throw std::runtime_error("Failed to create thread");
        }
    }

    void join() {
        if (pid > 0) {
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
            }
            pid = -1;
        }
    }

    ~Thread() {
        if (pid > 0) {
	    std::terminate();
        }
        if (stack) {
            munmap(stack, STACK_SIZE);
        }
    }

private:
    static int threadRoutine(void* arg) {
        Callable routine = reinterpret_cast<Callable>(arg);
        routine();
        return 0;
    }

    static const int STACK_SIZE = 8 * 1024 * 1024; // 8 MB
    Callable func;
    void* stack;
    pid_t pid;
};

void f() {
    for (int i = 0; i < 100; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    try {
        Thread t(f);
        f();
        t.join();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

