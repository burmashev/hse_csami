#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    int n = strtol(argv[1], NULL, 10);
    int num;
    int fd1[2];
    int fd2[2]; 
    if (pipe(fd1) == -1) {
        return 1;
    }
    if (pipe(fd2) == -1) {
        return 1;
    }
    FILE * r1 = fdopen(fd1[0], "r");
    FILE * r2 = fdopen(fd2[0], "r");
    FILE * w1 = fdopen(fd2[1], "w");
    FILE * w2 = fdopen(fd1[1], "w");
    fprintf(w2, "%d\n", 1);
    fflush(w2);
    pid_t pid1, pid2;
    if ((pid1 = fork()) < 0) { // error 
        fclose(r1);
        fclose(r2);
        fclose(w1);
        fclose(w2);
        return 1;
    } else if (!pid1) { 
        fclose(r2);
        fclose(w2);
        while (fscanf(r1, "%d", &num) == 1) {
            if (num == n) {
                break;
            }
            printf("%d %d\n", 1, num);
            fflush(stdout);
            fprintf(w1, "%d\n", num + 1);
            fflush(w1);
        }
        fclose(w1);
        exit(0);
    }
    if ((pid2 = fork()) < 0) { // error
        fclose(r1);
        fclose(w1);
        fclose(r2);
        fclose(w2); 
        return 1;
    } else if (!pid2) {
        fclose(r1);
        fclose(w1);
        while (fscanf(r2, "%d", &num) == 1) {
            if (num == n) {
                break;
            }
            printf("%d %d\n", 2, num);
            fflush(stdout);
            fprintf(w2, "%d\n", num + 1);
            fflush(w2);
        }
        fclose(w2); 
        exit(0);
    }
    fclose(r1);
    fclose(r2);
    fclose(w1);
    fclose(w2);
    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]); 
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    printf("%s\n", "Done");
    return 0;
}