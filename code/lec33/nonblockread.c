#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>

void make_nonblocking(int fd) {
  int flags = fcntl(fd, F_GETFL);
  fcntl(fd, F_SETFL, flags | O_NONBLOCK); // errno=EAGAIN is now yours
}

  
void ignore(int signal) {

}

int main() {
  int fd = 0;
  make_nonblocking( fd );

  signal(SIGINT, ignore);

  while( 1 ) {
     char buffer[4096];
     ssize_t result = read( fd, buffer, sizeof(buffer) );

     if(result > 0) {
       printf("Processing %d characters\n",(int)result);
     }

     if(result == 0) break;

     if(result == -1) {
       switch(errno) {
         case EAGAIN: puts("EAGAIN"); break;
         case EINTR: puts("EINTR"); break;
         default : printf("%d\n", errno);
       }
     }
     sleep(2);
  }     
  return 0;
}
