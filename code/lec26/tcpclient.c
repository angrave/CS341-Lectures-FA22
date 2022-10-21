#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main ()
{
  struct addrinfo hints, *result;

  memset (&hints, 0, sizeof (struct addrinfo));

  hints.ai_family = AF_INET; // IPv4   (AF_INET6 for IPv6 addresses)
  hints.ai_socktype = SOCK_STREAM; // TCP

  int s = getaddrinfo ("127.0.0.1", "8000", &hints, &result);
  //int s = getaddrinfo ("www.cs.illinois.edu", "80", &hints, &result);
  if (s != 0)
    {
      fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));
      exit (1);
    }

  int sock_fd = socket (result->ai_family, result->ai_socktype, result->ai_protocol);
  
  int ok = connect (sock_fd, result->ai_addr, result->ai_addrlen);
  if( ok == -1) {
    perror("connect");
    exit(1);
  }
  puts("Connected!");

  
  #define HELLO "GET / HTTP/1.0\r\nHOST: www.cs.illinois.edu\r\n\r\n"

  //write (sock_fd, HELLO, strlen (HELLO));
  dprintf(sock_fd, "GET / HTTP/1.0\r\n\r\n");
  
  char buffer[1000];
  
  while(1) {
    ssize_t bytes = read (sock_fd, buffer, sizeof (buffer)); // TODO Handle SIGPIPE
    if( bytes <1) break; // TODO Handle -1 and errno is EINTR
    write (1 /*stdout*/, buffer, bytes);
  } 
  // TODO shutdown . TODO close sock_fd 
  return 0;
}
