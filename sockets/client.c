#include "connection.h"

int argc = 0;
char ** argv = NULL;

void signal_handler(int);

int main(int argc, char ** argv){
    argc = argc;
    argv = argv;
    /* Initiating signal handler */
    if(signal(SIGPIPE, signal_handler) == SIG_ERR){
        printf("Signal handler initialization failed\n");
        exit(EXIT_FAILURE);
    }
    /* Create client socket */
    struct sockaddr_un client_socket_address;
    int sockfd_client;
    int datafd_client;
    sockfd_client = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sockfd_client == -1){
        handle_error("Client:: Socket could not be created");
    }
    printf("Client:: Socket open\n");

    client_socket_address.sun_family = AF_UNIX;
    strncpy(client_socket_address.sun_path, SERVER_PATH, sizeof(client_socket_address.sun_path) -1);

    /* Connect to the server */
    if(connect(sockfd_client, (struct sockaddr *)&client_socket_address, sizeof(struct sockaddr_un) - 1) == -1){
        handle_error("Client:: Failed to connect to server");
    }
    printf("Client:: Connected to server!\n");
    while(1){
        /* Send to server */
        struct msg{
            unsigned int a;
            unsigned short b;
        };
        struct msg M_TO_SEND = {
            .a = 0xFF001234,
            .b = 0x1234
        };
        printf("Client:: M_TO_SEND.a = %#x\n", M_TO_SEND.a);
        printf("Client:: M_TO_SEND.b = %#x\n", M_TO_SEND.b);        
        char msg_to_send[sizeof(struct msg)];
        memcpy(msg_to_send, &M_TO_SEND, sizeof(struct msg));
        msg_to_send[sizeof(struct msg) - 1] = 0;
        int no_of_bytes_written = write(sockfd_client, msg_to_send, sizeof(struct msg));
        if(no_of_bytes_written == -1){
            handle_error("Client:: Cannot send to server");
        }
        printf("Client:: %d bytes sent to server\n", no_of_bytes_written);
        /* Receive from server */
        int no_of_bytes_received = read(sockfd_client, buf, BUFFER_SIZE);
        if(no_of_bytes_received == -1){
            handle_error("Client:: Cannot receive from server");
        }
        printf("Client:: Received %d bytes from server\n", no_of_bytes_received);
        struct msg M_RECEIVED;
        memcpy(&M_RECEIVED, buf, sizeof(struct msg));
        printf("Client:: M_RECEIVED.a = %#x\n", M_RECEIVED.a);
        printf("Client:: M_RECEIVED.b = %#x\n", M_RECEIVED.b);        
        sleep(2);
    }
    close(sockfd_client);
}

void signal_handler(int signo){
    static int count_retries = 0;
    if(signo == SIGPIPE){
        if(count_retries <= 5){
            sleep(5);
            main(argc, argv);
        }
        else{
            printf("Server not reachable! Terminating client application");
            exit(EXIT_FAILURE);
        }
    }
}