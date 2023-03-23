#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid; 
    pid_t prog = getpid();
    int number, st;
    while (scanf("%d", &number) == 1) {
        if ((pid = fork()) < 0) { // error
            exit(1);
        } else if (pid) { // parent
            waitpid(pid, &st, 0); 
            if (WIFEXITED(st)) { 
                if (!WEXITSTATUS(st)) { // child is finished, so we can print number
                    printf("%d\n", number);
                    exit(0);
                }
            }
            if (getpid() == prog) {
                printf("%d\n", -1);
                while (wait(0) > 0) {};
                return 0;
            }
            exit(1);
        }
        // child goes to next iter
    }
    return 0;
}
