#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

/*
 used:
 https://russianblogs.com/article/32201911960/
*/
# define BUFFER_LEN 4096

void copy(int fdin, int fdout) {
	char buffer[BUFFER_LEN];
	ssize_t size;
	while ((size = read(fdin, buffer, BUFFER_LEN)) != 0) {
		if (write(fdout, buffer, size) != size) {
			fflush(stdout);
			exit(1);
		};
	};
	if(size<0) {
		exit(1);
	};
};

static void handler(int signum) {
    if (signum == SIGTERM) {
    	fprintf(stdout, "%s\n", "We communicate on my terms.");
    	fflush(stdout);
    };
}

int main(int argc, const char * argv[]) {
	struct sigaction sa_term = {};
    sa_term.sa_flags = SA_RESTART;
    sa_term.sa_handler = handler;
    sigemptyset(&sa_term.sa_mask);
    if (sigaction(SIGTERM, &sa_term, NULL) < 0) {
        return 1;
    };
    copy(STDIN_FILENO, STDOUT_FILENO);
};