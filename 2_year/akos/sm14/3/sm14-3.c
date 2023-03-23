#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

volatile sig_atomic_t cnt1 = 0;
volatile sig_atomic_t cnt2 = 0;
volatile sig_atomic_t is_usr1 = 0;
volatile sig_atomic_t  is_term = 0;

static void handler(int signum) {
    if (signum == SIGUSR1) {
        is_usr1 = 1;
    } else if (signum == SIGUSR2) {
        ++cnt2;
    } else if (signum == SIGTERM) {
        is_term = 1;
    }
}

int main(void) {
    struct sigaction sa_usr1 = {};
    sa_usr1.sa_flags = SA_RESTART;
    sa_usr1.sa_handler = handler;
    sigemptyset(&sa_usr1.sa_mask);
    struct sigaction sa_usr2 = {};
    sa_usr2.sa_flags = SA_RESTART;
    sa_usr2.sa_handler = handler;
    sigemptyset(&sa_usr2.sa_mask);
    struct sigaction sa_term = {};
    sa_term.sa_flags = SA_RESTART;
    sa_term.sa_handler = handler;
    sigemptyset(&sa_term.sa_mask);
    if (sigaction(SIGUSR1, &sa_usr1, NULL) < 0) {
        return 1;
    };
    if (sigaction(SIGUSR2, &sa_usr2, NULL) < 0) {
        return 1;
    };
    if (sigaction(SIGTERM, &sa_term, NULL) < 0) {
        return 1;
    };
    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGTERM);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    sigprocmask(SIG_BLOCK, &mask, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) {
        sigsuspend(&oldmask);
        if (is_term) { // SIGTERM 
            exit(0);
        }
        if (is_usr1) {
            printf("%d %d\n", cnt1, cnt2); // SIGUSR1
            fflush(stdout);
            ++cnt1;
            is_usr1 = 0;
        }
    }
    return 0;
}