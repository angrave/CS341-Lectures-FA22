#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void quit(char*mesg) {
  perror(mesg);
  exit(1);
}

int main(int argc, char** argv) { // TCP Server

    struct addrinfo hints, *result;
    
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM; // ie TCP
    hints.ai_flags = AI_PASSIVE; // << We want a Server socket

    int gai_result = getaddrinfo(NULL, "0", &hints, &result); 
  
    if(gai_result != 0) {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai_result));
      exit(1);
    }
    int sock_fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    
    if(sock_fd < 0) quit("socket");
    
    if( bind(sock_fd, result->ai_addr, result->ai_addrlen) ) quit("bind");
         
    struct sockaddr_in sin;
    socklen_t socklen = sizeof(sin);
    if( getsockname(sock_fd, (struct sockaddr *)&sin, &socklen) ) quit("getsockname");
   
    printf("Bound to port %d\n", ntohs( sin.sin_port ) );  // network -> host
    
    if( listen (sock_fd,100) ) quit("listen");
    sleep(5);
    while(1) {
      printf("Calling accept - (will block if no new clients)\n");
      
      int client_fd = accept(sock_fd, NULL,NULL);
      
      printf("New Client! On file descriptor %d\n",client_fd);
      shutdown(client_fd, SHUT_RD);      
      write(client_fd,"Hi\n", 3 );
      shutdown(client_fd, SHUT_WR);
      close(client_fd);
    } 
    return 0;
}
