#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {
    pid_t pid1, pid2;
    if ((pid1 = fork()) < 0) {
        exit(1);
    } else if (!pid1) {
        // son here 
        if ((pid2 = fork()) < 0) {
            exit(1);
        } else if (!pid2) {
            // son of son here 
            printf("%d ", 3);
            return 0;
        }
        wait(0);
        printf("%d ", 2);
        return 0;
    } 
    // parent here 
    wait(0);
    printf("%d\n", 1);
    return 0;
}