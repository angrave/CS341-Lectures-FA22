#include <unistd.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>


int main () {
  puts("It'sa Friday let's go!");
  
  pid_t result = fork();
  printf("%d Im alive. my parent is %d \n",getpid(), getppid());
  if(result == 0) { // Me child
    * (char*) 0 = '!';
    execl("ls","ls",NULL);
    perror("Ooops");
    exit(5);
  }
  // I'm the parent
  int status;
  waitpid(result, &status, 0); // BLOCK UNTIL the process finishes
  printf("Result is %d\n",status);
  return 0;
}