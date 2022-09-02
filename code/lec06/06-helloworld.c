#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
char * m = "World";
int main() {
 	pid_t f = fork();
 	  
	if(f == -1) { perror("fork failed!"); exit(1); }

 	if( f ==0 ) {   /* child process */ m = "Hello"; }

 	else { // I'm the parent
 		//printf("Waiting for %ld to finish\n", (long)f);
    int status;

    waitpid( f, &status, 0);
    if(WIFEXITED(status) ) {
      printf("My child exited normally with %d\n", WEXITSTATUS(status));
    }

 	  }
 	printf("%s\n",m); //both child & parent run these lines of code
 	return 42;
 	}
