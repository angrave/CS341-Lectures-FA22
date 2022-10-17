#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
  
  int fds[2];
  pipe(fds); // todo check okay
  int another[2];
  pipe(another);
  printf("fds[0] is %d\n", fds[0]);
  printf("fds[1] is %d\n", fds[1]);
  FILE* easy = fdopen(fds[1],"w");
  
  fflush(easy); // pre-fork
  fflush(stdin);
  fflush(stdout);
  
  pid_t child = fork();
  
  if( child ==0 ) { /* Me child!*/
    sleep(2);
    //write( fds[1], "Hello!",6);
    fprintf(easy, "Answer to life etc is %g\n", 3.14159);
    fflush(easy);
    
    
    char mybuf[100];
    ssize_t returned = read(another[0], mybuf, sizeof(mybuf)-1);
    printf("Number of bytes rec'd by child is %d\n", (int) returned);
    return 0;
    exit(0);
    
  }
   
  char* buffer[100];
  ssize_t numread = read( fds[0], buffer, sizeof(buffer)-1);
  printf("Number of bytes rec'd is %d\n", (int) numread);
  if(numread>0) {
    write(another[1], buffer, numread);  
  }
 
  
  return 0;
}