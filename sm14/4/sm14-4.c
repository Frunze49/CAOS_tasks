#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

enum { BUFF_SIZE = 1024 };

void sayhi(int signo) {
    exit(0);
}

int create_listener(char *service) {
    struct addrinfo *res = NULL;
    int gai_err;
    struct addrinfo hint = {
        .ai_family = AF_INET6,
        .ai_socktype = SOCK_STREAM,
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
        if (listen(sock, SOMAXCONN) < 0) {
            perror("listen");
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

    int fd[2];
    if (pipe(fd) < 0) {
        perror("pipe\n");
    }

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

    int sock = create_listener(argv[1]);
    if (sock < 0) {
        return 1;
    }
    char *arg_list[argc];
    for (int i = 2; i < argc; ++i) {
        arg_list[i - 2] = argv[i];
    }
    arg_list[argc - 2] = NULL;
    char tmp[BUFF_SIZE];
    int connection = accept(sock, NULL, NULL);
//    while (1) {
    if (!fork()) {
        printf("2\n");
        dup2(connection, STDIN_FILENO);
        close(connection);
        execvp(argv[2], arg_list);
        printf("10\n");
        exit(1);
    }
    printf("3\n");
    wait(NULL);
    printf("4\n");
    close(connection);
    connection = accept(sock, NULL, NULL);
//    }
    return 0;
}