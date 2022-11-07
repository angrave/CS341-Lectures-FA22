#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MESG1 "ILLI"
#define MESG2 "NOIS!"


int main() {
  mkfifo("pipe1",0600);
  mkfifo("pipe2",0600);

  int fd1 = open("pipe1",O_WRONLY, 0600);
  int fd2 = open("pipe2",O_WRONLY, 0600);
  
  puts("Press 1 or 2 (and Return) to send a ILINI-gram");
  while(1) {
    switch( getchar() ) {
      case '1': write(fd1, MESG1, strlen(MESG1)); break;
      case '2': write(fd2, MESG2, strlen(MESG2)); break;
      case EOF: exit(0);
    }
  }
  return 0;
}