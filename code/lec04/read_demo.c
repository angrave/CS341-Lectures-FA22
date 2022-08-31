#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( int argc, char** argv) {
  char buffer[4096];
  
  ssize_t result = read( 0 , buffer, sizeof(buffer) -1 );

  printf("result is %d", (int) result);
   if( result == -1 ) {
      fprintf(stderr,"Could not read from stdin!\n");
     exit(1); //fflush(stdout);
     }
  buffer[ result ] = '\0';

  printf("and you gave me:%s\n", buffer );
  puts(buffer); // same as printf("%s\n",buffer)
  printf("Hello! no newline" );
  sleep(2);
  return 0; // exit(0)
}
