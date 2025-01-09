#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    const char* st_name = argv[1];
    const char* nd_name = argv[2];
    int st_fd = open(st_name, O_RDONLY);
    int nd_fd = open(nd_name, O_WRONLY);

    ftruncate(nd_fd, 0);

    const int N = 1024;
    char buf[N];
    int read_cnt;
    while ((read_cnt = read(st_fd, buf, N)) > 0) {
        int write_res = write(nd_fd, buf, read_cnt);
        if (write_res == -1) {
            const char* err = "Error in writing";
            write(2, err, strlen(err));
        }
    }
    if (read_cnt == -1) {
        const char* err = "Error in reading";
        write(2, err, strlen(err));
    }

    close(st_fd);
    close(nd_fd);
}