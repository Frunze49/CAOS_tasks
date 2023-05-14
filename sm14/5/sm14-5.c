#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

enum { BUFF_SIZE = 2048 };

void sayhi(int signo) {
    exit(0);
}

int create_listener(char *service) {
    struct addrinfo *res = NULL;
    int gai_err;
    struct addrinfo hint = {
        .ai_family = AF_INET6,
        .ai_socktype = SOCK_DGRAM,
        .ai_flags = AI_PASSIVE,
    };
    if ((gai_err = getaddrinfo(NULL, service, &hint, &res))) {
        fprintf(stderr, "gai error: %s\n", gai_strerror(gai_err));
        return -1;
    }
    int sock = -1;
    for (struct addrinfo *ai = res; ai; ai = ai->ai_next) {
        sock = socket(ai->ai_family, ai->ai_socktype, 0);
        int one = 1;
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
        if (sock < 0) {
            perror("socket");
            continue;
        }
        if (bind(sock, ai->ai_addr, ai->ai_addrlen) < 0) {
            perror("bind");
            close(sock);
            sock = -1;
            continue;
        }
        break;
    }
    freeaddrinfo(res);
    return sock;
}

int main(int argc, char *argv[]) {

    sigset_t sigint, oldmask;
    sigemptyset(&sigint);
    sigaddset(&sigint, SIGTERM);
    sigprocmask(SIG_BLOCK, &sigint, &oldmask);

    struct sigaction sa = {
        .sa_handler = sayhi,
        .sa_flags = SA_RESTART,
    };
    sigaction(SIGTERM, &sa, NULL);
    sigprocmask(SIG_UNBLOCK, &sigint, &oldmask);

    char text[BUFF_SIZE], buf[BUFF_SIZE];
    int sock = create_listener(argv[1]);
    if (sock < 0) {
        return 1;
    }
    struct addrinfo hint = {
        .ai_family = AF_INET6,
        .ai_socktype = SOCK_DGRAM,
    };
    struct addrinfo *res = NULL;
    getaddrinfo(NULL, argv[1], &hint, &res);
    struct sockaddr_in6 *inet6;
    inet6 = (struct sockaddr_in6 *)res->ai_addr;

    struct sockaddr_in6 from;
    socklen_t fromsize = sizeof(from);
    while (1) {
        int ret = recvfrom(sock, text, BUFF_SIZE, 0, (struct sockaddr *)&from,
                           &fromsize);
        fromsize = sizeof(from);
        text[ret] = '\0';
        printf("[%s:%hu] %s\n",
               inet_ntop(res->ai_family, &inet6->sin6_addr, buf, sizeof(buf)),
               htons(from.sin6_port), text);
        fflush(stdout);
    }
}