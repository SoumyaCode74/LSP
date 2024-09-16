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

int socket_fd, session_fd;
char rbuf[10], wbuf[10];

void create_socket(int * socket_fd){
    *socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(*socket_fd == -1){
        print_error("Client:: socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Client:: Socket creation successful\n");
}

void connect_socket(int * socket_fd, char * server_ip_address, unsigned int server_port){
    struct sockaddr_in saddr = {
        .sin_family = AF_INET,
        .sin_port = htons(server_port),
        .sin_addr.s_addr = inet_addr(server_ip_address)
    };
    
    if(connect(*socket_fd, (struct sockaddr *)&saddr, sizeof(struct sockaddr)) == -1){
        print_error("Client:: Connection unsuccesful!");
        close(*socket_fd);
        exit(EXIT_FAILURE);
    }
    printf("Client:: Connection successful at %s:%u\n", inet_ntoa(saddr.sin_addr), ntohs(saddr.sin_port));
}

int receive_session(int * socket_fd, char * rbuf, unsigned int buf_len){
    int read_bytes = recv(*socket_fd, rbuf, buf_len, 0);
    if(read_bytes == -1){
        print_error("Client:: Receive from server unsuccessful!");
        close(*socket_fd);
        exit(EXIT_FAILURE);
    }
    printf("Client:: Received %d bytes from server\n", read_bytes);
    print_bytes(rbuf, buf_len);
    return read_bytes;
}

int send_session(int * socket_fd, char * wbuf, unsigned int buf_len){
    int write_bytes = send(*socket_fd, wbuf, buf_len, 0);
    if(write_bytes == -1){
        print_error("Client:: Send to server unsuccessful!");
        close(*socket_fd);
        exit(EXIT_FAILURE);
    }
    printf("Client:: Sent %d bytes to server\n", write_bytes);
    print_bytes(wbuf, buf_len);
    return write_bytes;
}

void close_socket(int * session_fd){
    if(close(*session_fd) == -1){
        print_error("Client:: Socket close failed!");
        exit(EXIT_FAILURE);
    }
    printf("Client:: Socket closed\n");
}

int main(int argc, char * argv[]){
    int c = 0;
    struct data
    {
        unsigned int val;
    };
    struct data D = {
        .val = c
    };
    while(1){
        /* Create client socket */
        create_socket(&socket_fd);
        /* Connect to server */
        if(argc > 1){
            connect_socket(&socket_fd, argv[1], SERVER_PORT);
        }else
        {
            connect_socket(&socket_fd, SERVER_IP_ADDRESS, SERVER_PORT);
        }
        /* Write back to server */
        c++;
        D.val = c;
        memcpy(wbuf, &D, sizeof(D));
        send_session(&socket_fd, wbuf, sizeof(D));
        /* Read from server */
        receive_session(&socket_fd, rbuf, sizeof(D));        
        /* Close socket */
        close_socket(&socket_fd);
        /* Wait for 100 milliseconds */
        usleep(1000*100);        
    }
}