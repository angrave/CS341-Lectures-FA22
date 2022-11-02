#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {
  int fd = open("alice.txt", O_RDONLY);
  
  struct stat s;
  fstat(fd, &s);
  
  // Map the file contents into memory

  char *ptr = mmap(NULL, s.st_size, 
    PROT_READ, 
    MAP_FILE | MAP_SHARED, fd, 0);

  // Look how easy to get the contents - just use the pointer 

  for(int i=0; i< s.st_size;i++)
     if(ptr[i] >31) 
        printf("%x %c\n",i, ptr[i]);
  
}

