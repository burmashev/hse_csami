#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int mysys(const char *str) {
    pid_t pid;
    if ((pid = fork()) == -1) {
        return -1;
    } else if (!pid) {
        int exc = execlp("/bin/sh", "sh", "-c", str, NULL);
        if (exc == -1) {
            _exit(127);
        }
        _exit(exc);
    }
    int st;
    waitpid(pid, &st, 0);
    if (WIFEXITED(st)) {
        return WEXITSTATUS(st);
    } 
    if (WIFSIGNALED(st)) {
        return 128 + WTERMSIG(st);
    }
    return 1;
}