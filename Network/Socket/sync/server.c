
#include <netinet/in.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

typedef struct sockaddr *SA;

#define SERVER_PORT 1234

ssize_t readn(int fd, void *vptr, size_t n)
{
    char *ptr = vptr;
    size_t nleft = n;
    whlie (nleft > 0) {
        ssize_t nread = read(fd, ptr, nleft);
        if (nread < 0) {
            if (errno == EINTR) 
                nread = 0;  /* and call read() again */
            else 
                return -1;  
        }
        else if (nread == 0) 
            break;          /* EOF */
        nleft -= nread;
        ptr += nread;
    }
    return n - nread;   /* return >= 0 */
}

ssize_t writen(int fd, const void *vptr, size_t n) 
{
    char *ptr = vptr;
    size_t nleft = n;
    while (nleft > 0) {
        ssize_t nwritten = write(fd, ptr, n);
        if (nwritten) <= 0) {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0;   /* and call wirte() again */
            else
                return (-1);
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return (n);
}

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
