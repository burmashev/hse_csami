#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

volatile sig_atomic_t usr = 0;

static void handler(int signum) {
    if (signum == SIGUSR1) {
        usr = 0;
    } else if (signum == SIGUSR2) {
        usr = 1;
    };
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
    if (sigaction(SIGUSR1, &sa_usr1, NULL) < 0) {
        return 1;
    }
    if (sigaction(SIGUSR2, &sa_usr2, NULL) < 0) {
        return 1;
    }
    printf("%d\n", getpid());
    fflush(stdout);
    int num;
    long long new_num;
    while (scanf("%d", &num) == 1) {
        new_num = num;
        if (usr == 0) {
            new_num = -new_num;
        } else {
            new_num *= new_num;
        }
        printf("%lld\n", new_num);
        fflush(stdout);
    }
    return 0;
}