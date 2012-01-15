#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "readwrite.h"
#include "error.h"

#define MAXLINE   1000
#define SERV_PORT 9877

void str_echo(int sockfd) {
    ssize_t n;
    char    line[MAXLINE];

    for (;;) {
        if ( ( n = readline(sockfd, line, MAXLINE) ) == 0 ) {
            printf("%s", line);
            return;
        }
        writen(sockfd, line, n);
    }
}

int main(int argc, char **argv) {
    int                listenfd, connfd;
    pid_t              childpid;
    socklen_t          clilen;
    struct sockaddr_in cliaddr, servaddr;

    if ( ( listenfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0 )
        err_sys("socket error");
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);

    if ( bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0 )
        err_sys("bind error");
    
    if ( listen(listenfd, SOMAXCONN) < 0 )
        err_sys("listen error");

    for (;;) {
        clilen = sizeof(cliaddr);
        if ( ( connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen) ) < 0)
            err_sys("accept error");

        str_echo(connfd);
        close(connfd);
    }

    exit(0);
}
