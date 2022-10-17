#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Hint: Hint:  open, pipe, read returns 0, write, fork, dup2(int current_fd, int new_fd); 
int main(int argc, char** argv) {
 if(argc != 3) {
   fprintf(stderr,"Usage: %s inputfile program\n", argv[0] );
   exit(1);
 }
 char*file = argv[1];
 char*prog= argv[2];
 
 int fd = open( file, ? );
 
}
