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

#define MAXLINE 1000

void err_doit(int useerrno, const char *fmt, va_list ap) {
    int errno_orig;
    char buf[MAXLINE + 1];

    errno_orig = errno;
    vsnprintf(buf, MAXLINE, fmt, ap);
    if (useerrno) {
        strcat(buf, ": ");
        strcat(buf, strerror(errno_orig));
    }
    strcat(buf, "\n");
    fputs(buf, stderr);

    return;
}

void err_quit(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, fmt, ap);
    va_end(ap);
    exit(1);
}

void err_sys(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, fmt, ap);
    va_end(ap);
    exit(1);
}

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
    
    while ( (n < read(sockfd, recvline, MAXLINE)) > 0 ) {
        recvline[n] = '\0';
        if ( fputs(recvline, stdout) == EOF )
            err_sys("fputs error");
    }

    if ( n < 0 )
        err_sys("read error\n");

    exit(0);
}
