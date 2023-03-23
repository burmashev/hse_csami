#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        return 1;
    }
    pid_t pid;
    if ((pid = fork()) < 0) {
        exit(1);
    } else if (pid) {
        wait(NULL);
    } else if (!pid) {
        char * file1 = argv[2]; 
        int fdin = open(file1, O_RDONLY | O_CLOEXEC, S_IREAD | S_IWRITE);
        if (fdin == -1) {
            close(fdin);
            return 1;
        }
        int fdout = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0666);
        if (fdout == -1) {
            close(fdin);
            close(fdout);
            return 1;
        }
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        dup2(fdin, STDIN_FILENO);
        dup2(fdout, STDOUT_FILENO);
        int proc = execlp(argv[1], argv[1], NULL);
        if (proc == -1) {
            close(fdin);
            close(fdout);
            return 1;
        }
        close(fdin);
        close(fdout);
    }
    return 0;
}