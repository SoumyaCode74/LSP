#ifndef __CONN_H__
#define __CONN_H__

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>       
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


#define handle_error(msg)           { \
                                        perror(msg); \
                                        exit(EXIT_FAILURE); \
                                    }
#define SERVER_PATH                 "/workspaces/LSP/soumyadeep_server"
#define BUFFER_SIZE                 50

#define PRINT_BYTES(no_of_bytes)        for(int i = 0; i < no_of_bytes; i++){ \
                                            printf("%#x ", buf[i]); \
                                        } \
                                        printf("\n");

char buf[BUFFER_SIZE];

void signal_handler(int signo);

#endif