#ifndef __CONN_INET_H__
#define __CONN_INET_H__

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
 #include <arpa/inet.h>

#define BUFFER_LIMIT                    100
#define SERVER_IP_ADDRESS               "127.0.0.2"
#define SERVER_PORT                     9846
#define print_error(msg)                {   \
                                            perror(msg); \
                                            exit(EXIT_FAILURE); \
                                        }

static inline void print_bytes(char * buf, int no_of_bytes){
    for(int i = 0; i < no_of_bytes; i++){
        printf("%#2x ",buf[i]);
    }
    printf("\n");
}

#endif