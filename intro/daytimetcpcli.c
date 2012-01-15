#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "error.h";

#define MAXLINE 1000

int main(int argc, char **argv) {
    int sockfd, n;
    char recvline[MAXLINE - 1];
    struct sockaddr_in servaddr;

    if (argc != 2)
        err_quit("Usage: %s <ipaddress>", argv[0]);

    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
        err_sys("Socket error");

    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(13);
   
    if ( inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        err_quit("inet_pton error for %s", argv[1]);

    if ( connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0 )
        err_sys("Connect error");
    
    while ( (n = read(sockfd, recvline, MAXLINE)) > 0 ) {
        recvline[n] = '\0';
        if ( fputs(recvline, stdout) == EOF )
            err_sys("fputs error");
    }

    if ( n < 0 )
        err_sys("read error\n");

    exit(0);
}
