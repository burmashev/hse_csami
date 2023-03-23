#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t pid1, pid2;
    int fds[2];
    if (pipe(fds) == -1) {
        return 1;
    }
    if ((pid1 = fork()) == -1) {
        return 1;
    } else if (!pid1) {
        dup2(fds[1], 1);
        close(fds[0]);
        close(fds[1]);
        execlp(argv[1], argv[1], NULL);
        _exit(1);
    }
    close(fds[1]);
    if ((pid2 = fork()) == -1) {
        return 1;
    } else if (!pid2) {
        dup2(fds[0], 0);
        close(fds[0]);
        execlp(argv[2], argv[2], NULL);
        _exit(1);
    }
    close(fds[0]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}