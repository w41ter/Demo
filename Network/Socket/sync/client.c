#include <arpa/inet.h>
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
    printf("connect to socket fd: %d.\n", sockfd);
}

int main(int argc, char **argv) 
{
    if (argc != 2) {
        printf("usage: xxx <IPaddress>\n");
        exit(1);
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in servaddr = {
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT),
    };
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) != 1) {
        perror("inet_pton");
        exit(1);
    }

    if (connect(sockfd, (SA)&servaddr, sizeof(servaddr)) == -1) {
        perror("connect");
        exit(1);
    }

    doit(sockfd);

    close(sockfd);
    return 0;
}