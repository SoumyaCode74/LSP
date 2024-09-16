#if 0
       int socket(int domain, int type, int protocol);

       int bind(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen);               

           struct sockaddr_in {
               sa_family_t    sin_family; /* address family: AF_INET */
               in_port_t      sin_port;   /* port in network byte order */
               struct in_addr sin_addr;   /* internet address */
           };

           /* Internet address. */
           struct in_addr {
               uint32_t       s_addr;     /* address in network byte order */
           };
           int listen(int sockfd, int backlog);
           int accept(int sockfd, NULL, NULL);   

       ssize_t send(int sockfd, const void *buf, size_t len, int flags);
       ssize_t recv(int sockfd, void *buf, size_t len, int flags);                          
#endif

#include "connections.h"

int socket_fd, session_fd, received_bytes, sent_bytes;
unsigned char rbuf[BUFFER_LIMIT], wbuf[BUFFER_LIMIT];

void create_socket(int * socket_fd){
    *socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(*socket_fd == -1){
        print_error("Server:: socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Server:: Socket creation successful\n");
}

void name_socket(int * socket_fd, char * server_ip_address, unsigned int server_port){
    struct sockaddr_in saddr = {
        .sin_family = AF_INET,
        .sin_port = htons(server_port == 0 ? SERVER_PORT : server_port),
        .sin_addr.s_addr = server_ip_address == NULL ? INADDR_ANY : inet_addr(server_ip_address)
    };
    if(bind(*socket_fd, (struct sockaddr *)&saddr, sizeof(struct sockaddr)) == -1){
        int error = errno;
        print_error("Server:: Bind unsuccesful!");
        if(error == EADDRINUSE){
            printf("Server:: Address already in use. Switching to any address mode\n");
            saddr.sin_addr.s_addr = INADDR_ANY;
            if(bind(*socket_fd, (struct sockaddr *)&saddr, sizeof(struct sockaddr)) == -1){
                print_error("Server:: Bind unsuccessful even in any address mode!");
                close(*socket_fd);
                exit(EXIT_FAILURE);
            }
        }
        else{
            close(*socket_fd);
            exit(EXIT_FAILURE);
        }
    }
    printf("Server:: Bind successful at %s:%u\n", inet_ntoa(saddr.sin_addr), ntohs(saddr.sin_port));
}

void listen_socket(int * socket_fd, unsigned int no_of_requests_to_wait){
    if (listen(*socket_fd, no_of_requests_to_wait) == -1)
    {
        print_error("Socket:: Listen unsuccessful!");
        close(*socket_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server:: Listening to the opened socket\n");
}

void accept_socket(int * socket_fd, int * session_fd){
    if((*session_fd = accept(*socket_fd, NULL, NULL)) == -1){
        print_error("Server:: Accepting connection requests");
        close(*socket_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server:: Accepted connection\n");
}

int receive_session(int * session_fd, char * rbuf, unsigned int buf_len){
    int read_bytes = recv(*session_fd, rbuf, buf_len, 0);
    if(read_bytes == -1){
        print_error("Server:: Receive from client unsuccessful!");
        close(*session_fd);
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    received_bytes = read_bytes;
    printf("Server:: Received %d bytes from client\n", read_bytes);
    print_bytes(rbuf, read_bytes);
    return read_bytes;
}

int send_session(int * session_fd, char * wbuf, unsigned int buf_len){
    int write_bytes = send(*session_fd, wbuf, buf_len, 0);
    if(write_bytes == -1){
        print_error("Server:: Write to client unsuccessful!");
        close(*session_fd);
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server:: Sent %d bytes to client\n", write_bytes);
    print_bytes(wbuf, buf_len);
    return write_bytes;
}

void close_session(int * session_fd){
    if(close(*session_fd) == -1){
        print_error("Server:: Session close failed!");
        exit(EXIT_FAILURE);
    }
    printf("Server:: Session closed\n");
}

void close_socket(int * session_fd){
    if(close(*session_fd) == -1){
        print_error("Server:: Socket close failed!");
        exit(EXIT_FAILURE);
    }
    printf("Server:: Socket closed\n");
}

int main(){
    /* Create server socket */
    create_socket(&socket_fd);
    /* Name the socket */
    struct in_addr serv_addr = {
        .s_addr = INADDR_LOOPBACK
    };
    name_socket(&socket_fd, SERVER_IP_ADDRESS, SERVER_PORT);
    /* Start listening to the socket */
    listen_socket(&socket_fd, 5);
    while(1){
        /* Accept connection */        
        accept_socket(&socket_fd, &session_fd);
        /* Receive from client */
        receive_session(&session_fd, rbuf, 10);
        /* Respond to client */
        memcpy(wbuf, rbuf, received_bytes);
        send_session(&session_fd, wbuf, received_bytes);
        /* Close session */
        close_session(&session_fd);
    }
    close_socket(&socket_fd);

}