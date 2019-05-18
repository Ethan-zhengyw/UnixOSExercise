#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/signal.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#define check(expr) if (!(expr)) { perror(#expr); kill(0, SIGTERM); }

void enable_keepalive(int sock) {
    int yes = 1;
    check(setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &yes, sizeof(int)) != -1);

    int idle = 1;
    check(setsockopt(sock, IPPROTO_TCP, TCP_KEEPIDLE, &idle, sizeof(int)) != -1);

    int interval = 1;
    check(setsockopt(sock, IPPROTO_TCP, TCP_KEEPINTVL, &interval, sizeof(int)) != -1);

    int maxpkt = 10;
    check(setsockopt(sock, IPPROTO_TCP, TCP_KEEPCNT, &maxpkt, sizeof(int)) != -1);
}

int main(int argc, char** argv) {
    check(argc == 2);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    check(inet_pton(AF_INET, argv[1], &addr.sin_addr) != -1);

    int server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    check(server != -1);

    int yes = 1;
    check(setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) != -1);

    check(bind(server, (struct sockaddr*)&addr, sizeof(addr)) != -1);
    check(listen(server, 1) != -1);

    if (fork() == 0) {
        int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        check(client != -1);
        check(connect(client, (struct sockaddr*)&addr, sizeof(addr)) != -1);
        printf("connected\n");
        pause();

        if (fork() == 0) {
            int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            check(client != -1);
            check(connect(client, (struct sockaddr*)&addr, sizeof(addr)) != -1);
            printf("connected\n");
            pause();
        }
        else {
            int client = accept(server, NULL, NULL);
            check(client != -1);
            enable_keepalive(client);
            printf("accepted\n");
            wait(NULL);
        }
    }
    else {
        int client = accept(server, NULL, NULL);
        check(client != -1);
        enable_keepalive(client);
        printf("accepted\n");
        wait(NULL);
    }

    return 0;
}
