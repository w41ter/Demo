
#include <netinet/in.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

typedef struct sockaddr *SA;

#define SERVER_PORT 1234

void doit(int sockfd) 
{
    printf("accept socket fd: %d.\n", sockfd);
}

int main(int argc, char **argv) 
{
    int serverfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverfd == -1) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in addrin = {
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT),
        .sin_addr.s_addr = htonl(INADDR_ANY)
    };
    if (bind(serverfd, (SA)&addrin, sizeof(addrin)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(serverfd, 14) == -1) {
        perror("listen");
        exit(1);
    }

    while (1) {
        struct sockaddr_in clientaddr;
        socklen_t len = sizeof(struct sockaddr_in);
        int sockfd = accept(serverfd, (SA)&clientaddr, &len);
        if (sockfd == -1) {
            perror("accept");
            continue;
        }

        doit(sockfd);

        close(sockfd);
    }
    close(serverfd);
    return 0;
}
