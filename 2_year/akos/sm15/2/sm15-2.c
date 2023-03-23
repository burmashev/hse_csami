#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    signal(SIGPIPE, SIG_IGN);
    char *host = argv[1];
    char *service = argv[2];
    char *key = argv[3];
    struct addrinfo hints = {}; // обнуляем структуру
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    struct addrinfo *result = NULL;
    int err = getaddrinfo(host, service, &hints, &result);
    if (err) {
        return 0;
    }
    int sfd;
    if ((sfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        freeaddrinfo(result);
        return 0;
    }
    if (connect(sfd, result->ai_addr, result->ai_addrlen) < 0) {
        freeaddrinfo(result);
        return 0;
    };
    int dupsfd;
    if ((dupsfd = dup(sfd)) < 0) {
        freeaddrinfo(result);
        return 0;
    }
    FILE * rfile = fdopen(sfd, "r");
    FILE * wfile = fdopen(dupsfd, "w");;
    if (fprintf(wfile, "%s\n", key) == EOF) {
        freeaddrinfo(result);
        fclose(rfile);
        fclose(wfile);
        return 0;
    }
    fflush(wfile);
    int k = 0;
    if (fscanf(rfile, "%d", &k) != 1) {
        freeaddrinfo(result);
        fclose(rfile);
        fclose(wfile);
        return 0;
    }
    for (int num = 0; num != k + 1; ++num) {
        if (fprintf(wfile, "%d\n", num) == EOF) {
            freeaddrinfo(result);
            fclose(rfile);
            fclose(wfile);
            return 0;
        }
        fflush(wfile);
    }
    uint64_t ans = 0;
    if (fscanf(rfile, "%" SCNd64, &ans) != 1) {
        freeaddrinfo(result);
        fclose(rfile);
        fclose(wfile);
        return 0;
    }
    printf("%" PRIu64, ans);
    fclose(rfile);
    fclose(wfile);
    freeaddrinfo(result);
    return 0;
}