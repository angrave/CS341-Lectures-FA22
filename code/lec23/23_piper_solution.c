#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// example use: ./a.out 23_rewind.c wc
// Hint: Hint:  open, pipe, read returns 0, write, fork, dup2(int current_fd, int new_fd); 
int main(int argc, char** argv) {
 if(argc != 3) {
   fprintf(stderr,"Usage: %s inputfile program\n", argv[0] );
   exit(1);
 }
 char*file = argv[1];
 char*prog = argv[2];
 
 int array[2];
 pipe( array );
 
 pid_t p = fork();
 
 if( p == 0) { // Me child
   dup2( array[0], 0); // set the input(stdin) of this process
   // read() will now read from our pipe 
   close( array[1] ); // child process will never write() to the pipe (but parent can still write)
   execlp( prog, prog, (char*) NULL); // prog's stdin is the pipe!
   fprintf(stderr,"Failed to exec");
   exit(1);
}
int fd = open( file,O_RDONLY);
char buffer[4096];
close( array[0] ); // Close the end of the pipe we're not using
while(1) {
   ssize_t bytesread = read(fd, buffer, 4096); // -1 (FAIL) 0=END of file
   if(bytesread <=0) break;
   
   ssize_t pipe_result= write( array[1], buffer, bytesread);
   if (pipe_result <0) break;
}
close( array[1] );  // now child process can discover when it has read last byte
waitpid( p, NULL, 0);
close(fd);
return 0;
}  
