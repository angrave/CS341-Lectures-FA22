#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <arpa/inet.h>
#include <ifaddrs.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** C code by Angrave. Meme picture from http://frankchen.xyz/2017/04/01/programmer-humor-week-1/ */

//https://github.com/angrave/SystemProgramming/wiki/Networking%2C-Part-5%3A-Reusing-ports#getnameinfo-example-whats-my-ip-address
void printmyip(int required_family) {
    // required_family = AF_INET6 or AF_INET; // Change to AF_INET6 for IPv6
    struct ifaddrs *myaddrs, *ifa;
    getifaddrs(&myaddrs);
    char host[256], port[256];
    for (ifa = myaddrs; ifa != NULL; ifa = ifa->ifa_next) {
        int family = ifa->ifa_addr->sa_family;
        if (family == required_family && ifa->ifa_addr) {
            if (0 == getnameinfo(ifa->ifa_addr,
                                (family == AF_INET) ? sizeof(struct sockaddr_in) :
                                sizeof(struct sockaddr_in6),
                                host, sizeof(host), port, sizeof(port)
                                 , NI_NUMERICHOST | NI_NUMERICSERV  )) {
                puts(host);
            }
        }
    }
}

void handle_sigpipe(int signal) {
  char mesg[1000];
  sprintf(mesg, "\n****** SIGPIPE  - no one is listening :-( ******\n");
  write(1, mesg, strlen(mesg));
}

ssize_t write_all(int fd, void* buf, size_t bytes) {
  size_t sent = 0;
  while(sent < bytes) {
    ssize_t result = write(fd, buf + sent, bytes - sent);
    if( result == -1 && errno == EINTR) {
      continue; // just restart
    }
    if(result < 0 ) {
      return result;
    }
    sent += result;
  }
  return sent;
}

int read_request_headers(int fd, char* buffer, size_t buffer_size) {
  size_t bytes_read = 0;
  while(bytes_read < buffer_size -1) {

    ssize_t result = read(fd, buffer + bytes_read, buffer_size - bytes_read - 1);
    if(result == -1 && errno == EINTR) {
      continue; // just restart;
    }

    if(result < 0) return -1;

    if(result == 0) break; // stream-end

    bytes_read += result;
    
    if(buffer[bytes_read-4] == '\r' && buffer[bytes_read-3] == '\n' && buffer[bytes_read-2] == '\r' && buffer[bytes_read-1] == '\n') {
      break; // End of request header \r\n\r\n
    }
  }
  buffer[bytes_read] = '\0';
  return bytes_read;
}


int main(int argc, char** argv)
{
    signal(SIGPIPE,handle_sigpipe);
    printmyip(AF_INET);
    
    FILE*file = fopen("meme.jpg","r");
    if( ! file) {
      perror("Could not pre-load image");
      exit(1);
    }
    
    // Or better - use stat!
    fseek(file,0, SEEK_END);
    long picture_size = ftell(file);
    fseek(file,0,SEEK_SET);
    
    char* picture_buf = malloc(picture_size);
    
    fread(picture_buf,1,picture_size,file);
    
    
    int s;
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct addrinfo hints, *result;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    s = getaddrinfo(NULL, "1234", &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(1);
    }
    // New: Reuse port using SO_REUSEADDR-
    int optval = 1;
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    if ( bind(sock_fd, result->ai_addr, result->ai_addrlen) != 0 )
    {
        perror("bind()");
        exit(1);
    }

    if ( listen(sock_fd, 10) != 0 )
    {
        perror("listen()");
        exit(1);
    }

    struct sockaddr_in * result_addr = (struct sockaddr_in*) result->ai_addr;
    printf("Listening on file descriptor %d, port %d\n", sock_fd, ntohs(result_addr->sin_port));

    while(1) {
        printf("Waiting for connection...\n");
        int client_fd = accept(sock_fd, NULL, NULL);
        
        printf("Connection made: client_fd=%d\n", client_fd);

        char request_buffer[10000];
        
        ssize_t bytes_read = read_request_headers(client_fd, request_buffer, sizeof(request_buffer));
        if(bytes_read <0) {
          close(client_fd);
          continue;
        }
        
        printf("Request: %s\n", request_buffer);
         
        char response[2048];
          
        if( strstr(request_buffer,"GET /meme.jpg " ) ) {
          puts("Sending picture");
          sprintf( response, "HTTP/1.0 200 OK\r\n"
              "Content-Type: image/jpeg\r\n"
              "Content-Length: %ld\r\n\r\n" , picture_size);

          write_all(client_fd, response, strlen(response));
          
          printf("Sending picture as %ld bytes\n", picture_size);
          write_all(client_fd, picture_buf, picture_size);
        } else if( strstr(request_buffer,"GET / " ) ) {
          puts("Sending html");
          dprintf(client_fd,"HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n");
          dprintf(client_fd,"<html><body><h1>My favorite Meme ...</h1><img src='meme.jpg'></body></html>");
        } else {
          dprintf(client_fd,"HTTP/1.0 404 MISSING\r\n\r\n");
        }
        shutdown(client_fd , SHUT_RDWR);
        close(client_fd);
    }
    return 0;
}
