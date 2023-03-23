#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>


#include <stdio.h>
int main(int argc, char* argv[]) {
    int n = 0;
    char* arg1[argc];
    int ar1 = 1;
    char* arg2[argc];
    int ar2 = 1;
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], ";") == 0) {
            n = i;
        }
        if (n == 0) {
            arg1[ar1] = argv[i];
            ar1++;
        }
        if (n > 0 && i > n+1) {
            arg2[ar2] = argv[i];
            ar2++;
        }

    }
    arg1[0] = argv[1];
    arg2[0] = argv[n + 1];
    arg1[n - 1] = NULL;
    arg2[argc - n - 1] = NULL;
    
    pid_t  child1;
    if ((child1 = fork()) < 0) {
        return 1;

    } else if (child1 == 0) {
        int cm1 = execvp(argv[1], arg1);
        if (cm1 == -1) {
            return 1;
        }
    }

    pid_t  child2;
    if ((child2 = fork()) < 0) {
        return 1;

    } else if (child2 == 0) {
        int cm2 = execvp(argv[n+1], arg2);
        if (cm2 == -1) {
            return 1;
        }
    }

    pid_t num = wait(NULL);
    if (num ==  child1) {
        kill(child2, SIGTERM);
    } else {
        kill(child1, SIGTERM);
    }
}

/*#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
    if (argc < 3) {
        return 1;
    };
    int separator = 1;
    for (int i = 2; i != argc; ++i) { // find ';'
        if (argv[i][0] == ';') {
            separator = i;
            break;
        }
    };
    // 1(cmd1) 2...sep-1(argv1) sep(;) sep+1(cmd2) sep+2...argc(argv2)
    char * cmd1 = argv[1];
    char * cmd2 = argv[separator + 1];
    char * argv1[separator];
    char * argv2[argc - separator];
    for (int i = 0; i != separator - 1; ++i) {
        argv1[i] = argv[i + 1];
    }
    for (int i = separator; i != argc - 1; ++i) {
        argv2[i - separator] = argv[i + 1];
    }
    // argv[] должен заканчиваться NULL
    argv1[separator - 1] = NULL;
    argv2[argc - 1 - separator] = NULL;
    int pid1, pid2;
    int stop;
    if ((pid1 = fork()) < 0) {
        return 1;
    } else if (!pid1) {
        execvp(cmd1, argv1);
        exit(1);
    }
    if ((pid2 = fork()) < 0) {
        return 1;
    } else if (!pid2) {
        execvp(cmd2, argv2);
        exit(1);
    }
    if ((stop = wait(NULL)) == pid1) {
        kill(pid2, SIGKILL);
    } else {
        kill(pid1, SIGKILL);
    };
    return 0;
}
*/