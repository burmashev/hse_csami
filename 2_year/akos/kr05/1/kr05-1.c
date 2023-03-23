#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int interact(const char* cmd, const char* input) {
    int fds[2];
    if (pipe(fds) == -1) {
        return 1;
    }
	pid_t pid;
    if ((pid = fork()) == -1) {
        return 0;
    } else if (!pid) {
    	const char * child_cmd;
    	dup2(fds[1], 1);
        close(fds[0]);
        close(fds[1]);
        read(fds[0], &child_cmd, sizeof(child_cmd));
        execlp("/bin/sh", "sh", "-c", cmd, NULL);
        _exit(0);
    };
    write(fds[1], input, sizeof(input));
    wait(NULL);
    return 0;
};


int main() {
	int x = interact("wc", "abcde");
}