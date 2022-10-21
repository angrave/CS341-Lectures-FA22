#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// A simple TCP server.
// Does not reuse reports; does not handle SIGPIPE; synchronous


int main(int argc, char** argv) { // TCP Server
    int s;
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct addrinfo hints, *result;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // << We want Server socket

    s = getaddrinfo(NULL, "8000", &hints, &result);
    if (s != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
            exit(1);
    }

    if ( bind(sock_fd, result->ai_addr, result->ai_addrlen) != 0 ) {
        perror("bind()"); exit(1);
    }
    if ( listen(sock_fd, 100) != 0)  {
        perror("listen()"); exit(1);
    }
    
    struct sockaddr_in * result_addr = (struct sockaddr_in*) result->ai_addr;
    printf("Listening on file descriptor %d, port %d\n", sock_fd,   ntohs(result_addr->sin_port));
    // network to host (short i.e. 16 bits)
    // host to network htons

    printf("Waiting for connection...\n");
    while(1) {
      int client_fd = accept(sock_fd, NULL, NULL);
      printf("Connection made: client_fd=%d\n", client_fd);
      if(client_fd <0) {
        perror("bad accept:");
        exit(1);
      }
    
      char buffer[1000];
      ssize_t len = read(client_fd, buffer, 999);
      if(len>0) {
        buffer[len] = '\0';

        printf("Read %d chars\n", (int)len);
        printf("===\n");
        printf("%s\n", buffer);
       }
       //write( client_fd, "Hello\n",6);
       // Or use dprintf ..
       dprintf( client_fd, "This server code was written in year %d.\n",2022);
       
       shutdown(client_fd, SHUT_RDWR); // We have no more to say, and we're not listening anymore (no more 'read')
       close(client_fd);
     }
    return 0;
}
