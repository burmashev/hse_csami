#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int port;
    if (sscanf(argv[1], "%d", &port) != 1) {
        return 1;
    }
    if (port <= 0 || port > 65535) {
        return 1;
    }
    int lfd;
    if ((lfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return 1;;
    }
    int sopt = 1;
    if (setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &sopt, sizeof(sopt)) < 0) {
        perror("setsockopt");
        return 1;
    }
    if (setsockopt(lfd, SOL_SOCKET, SO_REUSEPORT, &sopt, sizeof(sopt)) < 0) {
        perror("setsockopt");
        return 1;
    }
    struct sockaddr_in baddr, aaddr;
    baddr.sin_family = AF_INET;
    baddr.sin_port = htons(port);
    baddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(lfd, (struct sockaddr *) &baddr, sizeof(baddr)) < 0) {
        perror("bind");
        return 1;
    }
    if (listen(lfd, 5) < 0) {
        perror("listen");
        return 1;
    }
    int ans = 0;
    int afd;
    socklen_t alen;
    while (1) {
        alen = sizeof(aaddr);
        if ((afd = accept(lfd, (struct sockaddr *) &aaddr, &alen)) < 0) {
            perror("accept");
            return 1;
        }

        int num;
        if (read(afd, &num, sizeof(num)) != sizeof(num)) {
            perror("read_error");
            return 1;
        } else {
            ans += ntohl(num);
            close(afd);
            if (num == 0) {
                break;
            }
        }
    }
    printf("%d\n", ans);
    close(lfd);
    return 0;
}