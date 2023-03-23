#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int mysys(const char *str) {
    pid_t pid;
    if ((pid = fork()) == -1) {
        return 0;
    } else if (!pid) {
        execlp("/bin/sh", "sh", "-c", str, NULL);
        _exit(0);
    }
    int st;
    waitpid(pid, &st, 0);
    if (WIFEXITED(st)) {
        if (!WEXITSTATUS(st)) {
            return 1;
        }
    } 
    return 0;
}

int main(int argc, const char *argv[]) {
    if (argc < 4) {
        return 1;
    }
    if (mysys(argv[1])) {
        if (mysys(argv[3])) {
            return 0;
        }
        return 1;
    } 
    if (mysys(argv[2])) {
        if (mysys(argv[3])) {
            return 0;
        }
        return 1;
    }
    return 1;
}