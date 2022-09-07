#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// A program to run many commands in parallel
// Lines that start with an ! are executed
int main(int argc, char** argv) {
  if(argc!=2) {
     printf("Usage: %s commandfile\n", * argv ); 
     exit(1); 
  }
  size_t capacity = 200;
  char* buffer  = malloc(capacity);
  ssize_t bytes;
  FILE *file = fopen(argv[1],"r");
  if( ! file) { 
      perror("Could not read file"); 
      return 1; // ==== exit(1);
  }
  while( 1 ) {
     bytes = getline(& buffer, & capacity , file );
     if(bytes== -1) break; /* TEST EARLY */
     
     if(bytes>0 && buffer[bytes-1] == '\n') {
        buffer[bytes-1] = 0;
     }
     puts(buffer);
     if(/**/ ! strcmp(buffer, "END") ) break;
     if(*buffer == '!') {
        fflush(stdin);
        fflush(file);
        if( ! fork() ) { 
           execlp( "bash","bash", buffer +1 , (char*) NULL); 
           perror("failed to exec");
           exit(1);
        }
     }
  }
  /* Free resources */
  free(buffer); buffer = NULL;
  fclose(file); file = NULL;
  return 0;
}

