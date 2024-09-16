#include "connection.h"


int main(int argc, char ** argv){
    /* Handle SIGINT and SIGTERM to delete the socket file, if triggered*/
    if(signal(SIGINT, signal_handler) == SIG_ERR || signal(SIGTERM, signal_handler) == SIG_ERR){
        handle_error("Signal handling failed");
    }
    /* Check for existing socket files bearing the same name. If found, clear them out */
    unlink(SERVER_PATH);
    /* Create the socket */
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sockfd == -1){
        handle_error("Server:: Socket creation failed!");
    }
    printf("Server:: Telephone line established! (socket created)\n");
    
    struct sockaddr_un myserver;
    memset(&myserver, 0, sizeof(struct sockaddr_un));
    /* Define SOCKET ADDRESS FAMILY */
    myserver.sun_family = AF_UNIX;
    /* Define the SOCKET PATH */
    strncpy(myserver.sun_path, SERVER_PATH, sizeof(SERVER_PATH) - 1);
    /* Bind socket to an address */
    if(bind(sockfd, (struct sockaddr *)&myserver, sizeof(struct sockaddr_un)) == -1){
        handle_error("Server:: Bind failed");
    }
    printf("Server:: Telephone line got its own telephone number (Bind successful)\n");

    /* Start listening for any telephone trinking */
    if(listen(sockfd, 5) == -1){
        handle_error("Server:: Listen failed");
    }
    printf("Server:: Server telephone up to pickup calls (listen active)\n");
    /* Start picking up the calls pending in the queue */
    int data_socket = accept(sockfd, NULL, NULL);    
        if(data_socket == -1){
            handle_error("Server:: Accept failed");
        }
        printf("Server:: Picked up a call (accept succesful)\n");    
    while(1){
        /* Read data sent from client */
        int no_of_bytes_received = read(data_socket, buf, BUFFER_SIZE);
        if(no_of_bytes_received == -1){
            handle_error("Server:: Read failed");
        }
        printf("Server:: Received bytes from the client\n");
        PRINT_BYTES(no_of_bytes_received);

        printf("Server:: Heard what the call said! (read from accept)\n");
        buf[BUFFER_SIZE - 1] = '\0';    //Null terminate the buf

        /* Send the received packet */
        int no_of_bytes_sent = write(data_socket, buf, no_of_bytes_received);
        if(no_of_bytes_sent == -1){
            handle_error("Server:: Write failed");
        }
        printf("Server:: bytes sent to client\n");
        PRINT_BYTES(no_of_bytes_sent);        

    }
    /* Cut the telephone line */
        /* Close the data socket */
        printf("Server:: Open for next call to pickup! (close the accept socket)\n");        
        if(close(data_socket) == -1){
            handle_error("Server:: close data socket failed");
        }    
    if(close(sockfd) == -1){
        handle_error("Server:: Connection socket could not be closed!");
    }
    unlink(SERVER_PATH);
    printf("Server:: Telephone line cut! Time for a break! (closed socket)\n");
    return 0;
}


void signal_handler(int signo){
    if(signo == SIGINT || signo == SIGTERM){
        printf("Forced termination requested!\n");
        exit(EXIT_SUCCESS);        
    }
}