#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

void sayhi(int signo) {
    _exit(0);
}

int create_connection(char *node, char *service) {
    struct addrinfo *res = NULL;
    int gai_err;
    struct addrinfo hint = {
        .ai_family = AF_UNSPEC,  // можно и AF_INET, и AF_INET6
        .ai_socktype = SOCK_STREAM,  // но мы хотим поток (соединение)
    };
    if ((gai_err = getaddrinfo(node, service, &hint, &res))) {
        fprintf(stderr, "gai error: %s\n", gai_strerror(gai_err));
        _exit(0);
    }
    int sock = -1;
    for (struct addrinfo *ai = res; ai; ai = ai->ai_next) {
        sock = socket(ai->ai_family, ai->ai_socktype, 0);
        if (sock < 0) {
            perror("socket");
            continue;
        }
        if (connect(sock, ai->ai_addr, ai->ai_addrlen) < 0) {
            perror("connect");
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
    sigaddset(&sigint, SIGPIPE);
    sigprocmask(SIG_BLOCK, &sigint, &oldmask);

    struct sigaction sa = {
        .sa_handler = sayhi,
        .sa_flags = SA_RESTART,
    };
    sigaction(SIGPIPE, &sa, NULL);
    sigprocmask(SIG_UNBLOCK, &sigint, &oldmask);

    if (argc != 4) {
        fprintf(stderr, "Usage: %s NODE SERVICE\n", argv[0]);
        _exit(0);
    }
    int sock = create_connection(argv[1], argv[2]);
    if (sock < 0) {
        return 1;
    }

    int sock2 = sock;
    dup2(sock, sock2);
    FILE *reader = fdopen(sock, "r");
    FILE *writer = fdopen(sock, "w");
    fprintf(writer, "%s\n", argv[3]);
    fflush(writer);
    int range = 3;
    if (!fscanf(reader, "%d", &range)) {
        _exit(0);
    }
    for (int i = 0; i <= range; ++i) {
        fprintf(writer, "%d\n", i);
    }
    fflush(writer);
    uint64_t ans = 1;
    if (fscanf(reader, "%lu", &ans) != 1) {
        _exit(0);
    }
    fprintf(stdout, "%lu\n", ans);
    fflush(stdout);
    close(sock);
}