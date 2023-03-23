#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>

enum { BUF_SIZE = 1001 };

int main(void) {
    char host[BUF_SIZE];
    char service[BUF_SIZE];
    while (scanf("%s %s", host, service) != EOF) {
        struct addrinfo hints = {}; // обнуляем структуру
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

        struct addrinfo *result;
        int err = getaddrinfo(host, service, &hints, &result);
        if (err) {
            fprintf(stdout, "%s\n", gai_strerror(err));
            continue;
        }

        struct sockaddr_in *ans = NULL;
        for (struct addrinfo *res = result; res != NULL; res = res->ai_next) {
            struct sockaddr_in *ain = (struct sockaddr_in *) res->ai_addr;
            if (ans == NULL) {
                ans = ain;
                continue;
            }
            if (ntohl(ain->sin_addr.s_addr) < ntohl(ans->sin_addr.s_addr)) {
                ans = ain;
            }
        }
        printf("%s:%d\n", inet_ntoa(ans->sin_addr), ntohs(ans->sin_port));
        freeaddrinfo(result); 
    }
    return 0;
}