#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <inttypes.h>

uint8_t frobnicate(uint8_t a, uint8_t b);

int main(int argc, char* argv[]) {
    pid_t pid1, pid2;
    pid_t prog = getpid();
    uint8_t sum = 0;
    int st1, st2;
    int N = strtol(argv[1], NULL, 10);
    for (int i = 0; i != N; ++i) {
        if (!(pid1 = fork())) { // first 
            exit(i * 2 + 1);
        }
        if (!(pid2 = fork())) { // second 
            if (i == N - 1) {
                exit(i * 2 + 2);
            }
        } else if (pid2) {
            wait(&st1);
            wait(&st2);
            uint8_t a = WEXITSTATUS(st1);
            uint8_t b = WEXITSTATUS(st2);
            uint8_t xyzy = frobnicate(a, b);
            if (getpid() == prog) {
                sum += xyzy;
                break;
            }
            exit(xyzy);
        }
    }
    printf("%d\n", sum);
    return 0;
}