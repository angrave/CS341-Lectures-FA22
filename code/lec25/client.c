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
  hints.ai_socktype = SOCK_STREAM; // TCP like a POSIX pipes

  int s = getaddrinfo ("127.0.0.1", "8000", &hints, &result);
  
  //int s = getaddrinfo ("illinois.edu", "80", &hints, &result);
  if (s != 0)
  {
      fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));
      exit (1);
  }
  int sock_fd  = socket(result ->ai_family, result->ai_socktype, result->ai_protocol /* will be zero */);
  if(sock_fd == -1) {
    perror("socket failed");
    exit(1);
  }
  
  int connect_result = connect(sock_fd, result->ai_addr, result ->ai_addrlen);
  if(connect_result == -1) {
    perror("connect failed");
    exit(1);
  }
  
  puts("Connected!");

  
  #define MESG "GET / HTTP/1.0\r\nHOST: illinois.edu\r\n\r\n"
  
  write(sock_fd, MESG, strlen(MESG)); //TODo wrap this so partial writes, EINTR etc etc
  
  char buffer[1024];

  while(1){
    ssize_t bytes_recd = read(sock_fd, buffer, sizeof(buffer));
    if( bytes_recd>0) {
      write(1, buffer,bytes_recd );
    } else {
      break; // 0 = end, -1 = failure
    }
  }
  return 0;
}
