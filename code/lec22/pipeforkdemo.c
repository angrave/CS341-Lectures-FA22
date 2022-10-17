#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void pipe_closed(int s) {
  #define MESG "SIGPIPE!SORRY WRITER,  THE PIPE CLOSED - NO ONE WANTS YOUR BYTES!\n"
  write(1,MESG, sizeof(MESG));
}

int main() {

    signal(SIGPIPE, pipe_closed );

    int fds[2];
    
    pipe( fds );

    pid_t child = fork();
    if(child ==0) { 
    
      close(fds[1]); // The child will never write to this pipe
      puts("Child has closed the pipe for writing");
        
      char buffer[80];
      ssize_t bytesread = read(fds[0] , buffer, sizeof(buffer));
        
      close(fds[0]); // done reading
      puts("Child has closed the pipe for reading");
        
      printf("\n%d bytes read\n", (int) bytesread);
        // do something with the bytes read
        write( 1, buffer, bytesread);
  
        
    } else {
      
      close(fds[0]); // Parent will never read from this pipe
      puts("Parent has closed the pipe for reading");
      
      sleep(2);
      puts("Sending message 2...");
      //fdopen(int fd, const char *mode);
      FILE* f = fdopen(fds[1],"w");
      fprintf(f,"Message 1!\n");
      fflush(f); // now write(fds[1] ...) is called
        
      sleep(1);
      puts("Sending message 2... (after both processes have closed the read end)");
      fprintf(f,"Message 2\n");
      puts("The fflush will call write - which result in SIGPIPE");
      fflush(f); // now write(fds[1] ...) is called
        
    }
    sleep(2);
    puts("Processes are closing down byeee...");
    return 0;
}
