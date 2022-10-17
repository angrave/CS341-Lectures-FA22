#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

char buffer[4096];

void ohdear(int signalnum) {
  char* mesg = "SIGPIPE happened oh dear!\n";
  write(1, mesg, strlen(mesg));
  // _exit(1);
}

int main() {
  signal(SIGPIPE, ohdear);
  
  int fds[2];
  pipe(fds);
  int read_end = fds[0];
  int write_end = fds[1];
  
  pid_t child = fork();
  if(child  == 0) { 
    close(read_end);
    exit(0);
  }
  
  close(read_end);
  ssize_t bytes_written = write(write_end, "Hi", 2);
  if(bytes_written == -1) {
    printf("FAILED to write !");
  } else {
    printf("Bytes sent %d \n", (int) bytes_written);
  }
  return 0;
}