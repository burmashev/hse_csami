#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int mysys(const char *str, const char * filename) {
    int fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0600);
    pid_t pid;
    if ((pid = fork()) == -1) {
        return 0;
    } else if (!pid) {
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execlp("/bin/sh", "sh", "-c", str, (char*) 0);
        return 0;
    }
    close(fd);
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
    if (mysys(argv[1], argv[3])) {
        return 0;
    }
    mysys(argv[2], argv[3]);
    return 0;
}