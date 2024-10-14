#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sock_init.h"
#include "xplatform_socket.h"
#include "hacking.h"

// raw sockets code would work only for linux
int main() 
{
    int i, recv_length, sockfd;

    unsigned char buffer[9000];

    sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_TCP);
    if (!ISVALIDSOCKET(sockfd)) {
        fprintf(stderr, "socket() failed (%d).\n", GETSOCKETERRNO());
        return 1;
    }

    for(i = 0; i < 3; ++i) {
        recv_length = recv(sockfd, buffer, 8000, 0);
        printf("Got a %d byte packet.\n", recv_length);
        dump(buffer, recv_length);
    }
}