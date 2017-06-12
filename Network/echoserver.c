#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define EPOLL_SIZE 100
#define EPOLL_EVENT_SIZE 100;

#define PORT 1234

int create_server_socket(void) 
{
    int serverfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverfd < 0) {
        printf("create server socket failed!\n");
        exit(1);
    }
    return serverfd;
}

int create_epoll(void) 
{
    int fd = epoll_create(EPOLL_SIZE);
    if (fd < 0) {
        printf("create epoll failed!\n");
        exit(1);
    }
    return fd;
}

void bind_address(int sockfd, uint16_t port)
{
    struct sockaddr_in address;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr*)&address, 
        sizeof(struct sockaddr_in)) < 0) {
        printf("bind port %h failed!\n", port);
        exit(1);
    }
}

void listen_socket(int sockfd)
{
    if (listen(sockfd, BACK_QUEUE) < 0) {
        printf("listen failed!\n");
        exit(1);
    }
}

void set_nonbloking(int sockfd) 
{
    int opts = fcntl(sockfd, FGETFL);
    if (opts < 0) {
        printf("fcntl(F_GETFL) failed!\n");
        return;
    }

    opts |= O_NONBLOCK;
    if (fcntl(sockfd, F_SETFL, opt) < 0) {
        printf("fcntl(F_GETFL) failed!\n");
        return;
    }
}

void accept_socket(int serverfd, int epollfd)
{
    struct sockaddr_in address;
    int clientfd = accept(serverfd, (struct sockaddr*)
        &address, sizeof(struct sockaddr_in));
    
    if (clientfd < 0) {
        return;
    }

    struct epoll_event event;
    event.data.fd = clientfd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, clientfd, &event);
}

void read_socket(int sockfd)
{

}

void close_socket(int sockfd)
{

}

void dispatcher(int epollfd, int serverfd, 
    struct epoll_event *event) 
{
    if (evnet->data.fd == serverfd 
        && event->events & EPOLLIN) {
        accept_socket(serverfd, epollfd);
    }
    else if (event->events & EPOLLIN) {
        read_socket(serverfd);
    }
    else if (event->events & EPOLLHUP) {
        close_socket(event->data.fd);
    }
    else if (len == EAGAIN) {
        return;
    }
    else {
        printf("read socket failed!\n");
    }
}

void loop(int epollfd, int serverfd)
{
    struct epoll_event events[EPOLL_EVENT_SIZE];

    while (true) {
        int nums = epoll_wait(epollfd, 
            events, EPOLL_EVENT_SIZE, -1);
        for (int i = 0; i < nums; ++i) {
            dispatcher(epollfd, serverfd, events + i);
        }
    }
}

int main(int argc, char **argv) 
{
    int epollfd = create_epoll();

    int serverfd = create_server_socket();
    bind_address(serverfd, PORT);

    struct epoll_event event;
    event.data.fd = serverfd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, serverfd, &event);

    listen_socket(serverfd);

    loop(epollfd);
}