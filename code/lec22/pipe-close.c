#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

char buffer[4096];

int main() {
  
  int fds[2];
  pipe(fds);
  int read_end = fds[0];
  int write_end = fds[1];
  
  pid_t child = fork();
  // use pipe to send bytes from the child to the parent
  
  
  if( child ==0) {
    write(write_end,"Hi",2);
    write(write_end,"There",5);
    close(write_end);
    return 0;
  }
  
  // parent will never write
  
  close(write_end);
  
  ssize_t bytesread;
  do {
    bytesread = read(read_end, buffer, sizeof(buffer));
    printf("Bytes read : %zu \n", bytesread);
  } while(bytesread);
  
  return 0;
}