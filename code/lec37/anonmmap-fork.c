#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Example of using mmap to share data between child and parent process
// But this example suffers from poor synchronization issues. Can you see why?

void quit(char*mesg) {
  fprintf(stderr,"%s\n",mesg);
  exit(1);
}


void child(char* shared) {
  for(int i = 0; i < 100;i++) {
    sprintf(shared,"! The value of i is %d\n",i);
    sleep(1);
  }
}

void parent(char*shared) {
  while(1) {
    if(*shared) {
      puts(shared);
      *shared = 0;
    }
    sleep(1);  
  }  
}


int main() {
  // int fd = open("datafile", O_RDWR, 0x600);
  //
  // struct stat s;
  // fstat(fd, &s);
  //
  // // Map the file contents into memory
  // Use MAP_ANON instead of MAP_FILEs.st_size
  size_t size = 4096;
  
  char *shared_mem = mmap(NULL, size, 
    PROT_READ | PROT_WRITE, 
    MAP_ANON | MAP_SHARED, 0, 0);
    
  if (shared_mem == (char*)-1) quit("mmap failed");
  
  // Look how easy to get the contents - just use the pointer 
  pid_t pid = fork();
  if(pid ==0) {
    child(shared_mem);
  } else {
    parent(shared_mem);
  }
  exit(1);  
}
