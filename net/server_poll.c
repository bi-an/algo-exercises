#include "wrap.h"
#include <poll.h>
#include <arpa/inet.h>
#include <strings.h>
#include <stdio.h>

static const int SERV_PORT = 7777;

int main() {
    struct pollfd poll_fd;
    struct sockaddr_in serv_addr;
    int listenfd, connfd, maxi, maxfd, clients[1024]; // TODO 
    char buf[BUFSIZ];

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);
    
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    Listen(listenfd, 128);

    while(1) {
        
    }

    

}