#include <unistd.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>

int CreateEpollOrDie()
{
	int epollfd = epoll_create(1);
	if (epollfd == -1) {
		perror("epoll_create");
		exit(1);
	}
	return epollfd;
}

int CreateServerSocketOrDie(int port)
{
	int serverfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (serverfd == -1) {
		perror("socket");
		exit(1);
	}

	struct sockaddr_in addr;
	socklen_t len = sizeof(add);
	if (bind(serverfd, &addr, len) == -1) {
		perror("bind");
		exit(1);
	}

	return serverfd;
}

void ListenSocketOrDie(int fd, int backlog) 
{
	if (listen(fd, backlog) == -1) {
		perror("listen");
		exit(1);
	}
}

int main(int argc, char **argv)
{
	int epollfd = CreateEpollOrDie();
	int serverfd = CreateSocketOrDie()

	close(epollfd);
    return 0;
}

