#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> /*isprint*/

void quit(const char*mesg) {
  perror(mesg);
  exit(1);
}

int main(int argc, char**argv) {
  if(argc != 2) {
    fprintf(stderr, "Prints sequences of printable characters found in files\n");
    fprintf(stderr, "Usage: %s filename\n",argv[0]);
    exit(1);
  }
  int fd = open(argv[1], O_RDONLY);
  if(fd == -1) { quit("could not open file"); }
  
  struct stat s;
  if( fstat(fd, &s) != 0) { quit("Could not stat the file"); }
  
  // Map the file contents into memory

  char *ptr = mmap(NULL, s.st_size, 
    PROT_READ, 
    MAP_FILE | MAP_SHARED, 
    fd, 0);

  if(ptr == MAP_FAILED) { quit("Could not mmap the file"); }
    
  // Look how easy to use the file contents - just use the pointer e.g. ptr[i] 
  int count = 0;
  for(int i=0; i< s.st_size;i++) {
     if(  isprint( ptr[i] ) ) {
       count ++;
     } else {
       if(count > 2) {
         fwrite( ptr + i - count, 1, count, stdout);
        putchar('\n');
       }
       count = 0;
     }
   }
   return 0;
}

