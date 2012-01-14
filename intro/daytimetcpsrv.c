#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAXLINE 1000
#define LISTENQ 100

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
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;

    // fprintf(stderr, "socket");
    if ( ( listenfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0 )
        err_sys("socket error");

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);

    if ( bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0 )
        err_sys("bind error");

    if ( listen(listenfd, LISTENQ) < 0 )
        err_sys("listen error");

    for (;;) {
        if ( ( connfd = accept(listenfd, (struct sockaddr *) NULL, NULL) ) < 0 )
            err_sys("accept error");

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

        if ( write(connfd, buff, strlen(buff)) < 0 )
            err_sys("write error");

        close(connfd);
    }
}
