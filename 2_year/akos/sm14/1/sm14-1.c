#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

volatile sig_atomic_t cnt = 0;

static void handler(int signum) {
    printf("%d\n", cnt);
    fflush(stdout);
    ++cnt;
    if (cnt == 4) {
        exit(0);
    };
}

int main(void) {
    struct sigaction sa = {};
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    if (sigaction(SIGINT, &sa, NULL) < 0) {
        return 1;
    };
    printf("%d\n", getpid());
    fflush(stdout);
    sigprocmask (SIG_BLOCK, &mask, &oldmask);
    while (1) { 
        sigsuspend(&oldmask);
    }
    sigprocmask (SIG_UNBLOCK, &mask, NULL);
    return 0;
}