#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <signal.h>
#include <sys/signalfd.h>

void work(int num, int fd[], int maximum, pid_t pid, int sfd, sigset_t mask) {
    struct signalfd_siginfo fdsi;
    sfd = signalfd(-1, &mask, 0);
    if (sfd == -1) {
        exit(1);
    } 
    while (1) {
        if (read(sfd, &fdsi, sizeof(fdsi)) < 0) {
            exit(1);
        };
        int buff;
        if (fdsi.ssi_signo == SIGUSR1) {
            if (read(fd[0], &buff, sizeof(buff)) < 0) {
                exit(1);
            };
            printf("%d %d\n", num, buff);
            fflush(stdout); 
            if (buff == maximum) {
                kill(pid, SIGINT);
                exit(0);
            }
            ++buff;
            if (write(fd[1], &buff, sizeof(buff)) < 0) {
                exit(1);
            };
            kill(pid, SIGUSR1);
        } else if (fdsi.ssi_signo == SIGINT) {
            exit(0);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    int n = strtol(argv[1], NULL, 10);
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGINT);
    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1) {
        return 1;
    };
    int sfd;
    sfd = signalfd(-1, &mask, 0);
    if (sfd == -1) {
        exit(1);
    } 
    int fd[2];
    if (pipe(fd) == -1) {
        return 1;
    }
    pid_t pid1, pid2;
    if ((pid1 = fork()) < 0) {
        exit(1);
    } else if (!pid1) {
        int s;
        if (read(fd[0], &s, sizeof(s)) < 0) {
            return 1;
        };
        work(1, fd, n, s, sfd, mask);
        exit(1);
    }
    if ((pid2 = fork()) < 0) {
        exit(1);
    } else if (!pid2) {
        work(2, fd, n, pid1, sfd, mask);
        exit(1);
    }
    if (write(fd[1], &pid2, sizeof(pid2)) < 0) {
        return 1;
    };
    int number = 1;
    kill(pid1, SIGUSR1);
    if (write(fd[1], &number, sizeof(number)) < 0) {
        return 1;
    };
    wait(NULL);
    wait(NULL);
    return 0;
}