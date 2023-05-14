#include <arpa/inet.h>
#include <limits.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

enum { KB = 1024, EIGHT = 8, SIXTEEN = 16, TFOUR = 24 };

int main() {
    char host[KB], service[KB];
    struct addrinfo hint = {
        .ai_family = AF_INET,
    };
    struct in_addr inp;
    while (scanf("%s%s", host, service) != EOF) {
        struct addrinfo *res = NULL;
        int gai_err;
        if ((gai_err = getaddrinfo(host, service, &hint, &res))) {
            printf("%s\n", gai_strerror(gai_err));
            continue;
        }
        unsigned int min = UINT_MAX;
        char min_str[KB];
        for (struct addrinfo *ai = res; ai; ai = ai->ai_next) {
            char buf[KB];
            struct sockaddr_in *inet;
            inet = (struct sockaddr_in *)ai->ai_addr;
            char now_str[KB];
            int now;
            sscanf(inet_ntop(ai->ai_family, &inet->sin_addr, buf, sizeof(buf)),
                   "%s", now_str);
            unsigned int ipbytes[4];
            sscanf(now_str, "%u.%u.%u.%u", &ipbytes[3], &ipbytes[2],
                   &ipbytes[1], &ipbytes[0]);
            now = ipbytes[0] | ipbytes[1] << EIGHT | ipbytes[2] << SIXTEEN |
                  ipbytes[3] << TFOUR;
            snprintf(now_str + strlen(now_str), KB, ":%u",
                     htons(inet->sin_port));
            inet_aton(
                inet_ntop(ai->ai_family, &inet->sin_addr, buf, sizeof(buf)),
                &inp);
            if (ntohl(inp.s_addr) < min) {
                min = now;
                sscanf(now_str, "%s", min_str);
            }
        }
        printf("%s\n", min_str);
        freeaddrinfo(res);
    }
}