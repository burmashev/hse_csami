#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fds[2];
    int parent_num;
    int child_num;
    long long int ans = 0;
    if (pipe(fds) == -1) {
        return 1;
    }
    pid_t pid1, pid2;
    if ((pid1 = fork()) == -1) {
        return 1;
    } else if (!pid1) {
        // pid1
        close(fds[1]);
        if ((pid2 = fork()) == -1) {
            return 1;
        } else if (!pid2) {
            // pid2 
            while (read(fds[0], &child_num, sizeof(child_num))) {
                ans += child_num;
            }
            printf("%lld\n", ans);
            exit(0);
        }
        // pid1
        waitpid(pid2, NULL, 0);
        exit(0);
    }
    // parent
    while (scanf("%d", &parent_num) == 1) {
        write(fds[1], &parent_num, sizeof(parent_num));
    }
    close(fds[0]);
    close(fds[1]);
    waitpid(pid1, NULL, 0);
    return 0;
}