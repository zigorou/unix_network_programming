#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "error.h"

#define MAXLINE 1000

int main(int argc, char **argv) {
    int                listenfd, connfd;
    socklen_t          len;
    struct sockaddr_in servaddr, cliaddr;
    char               buff[MAXLINE];
    time_t             ticks;

    if ( ( listenfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0 )
        err_sys("socket error");

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(13);

    if ( bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0 )
        err_sys("bind error");

    if ( listen(listenfd, SOMAXCONN) < 0 )
        err_sys("listen error");

    for (;;) {
        len = sizeof(cliaddr);
        if ( ( connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &len) ) < 0 )
            err_sys("accept error");

        printf("Connection from %s, port %d\n", 
            inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)), 
            ntohs(cliaddr.sin_port)
        );

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));
        close(connfd);
    }

    exit(0);
}
