#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

#include "error.h"

int main(int argc, char **argv) {
    union {
        short s;
        char  c[sizeof(short)];
    } un;
    struct utsname utsn;

    if ( uname(&utsn) < 0 )
        err_sys("uname error");

    un.s = 0x0102;

    printf("%s-%s-%s: ", utsn.machine, utsn.sysname, utsn.release);

    if ( sizeof(short) == 2 ) {
        if (un.c[0] == 1 && un.c[1] == 2) 
            printf("big-endian\n");
        else if (un.c[0] == 2 && un.c[1] == 1)
            printf("little-endian\n");
        else
            printf("unknown\n");
    }
    else
        printf("sizeof(short) = %d\n", (int) sizeof(short));

    exit(0);
}
