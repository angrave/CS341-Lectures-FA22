#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {

   int fd = open("alice.txt", O_RDWR, 0644);

   char *ptr = mmap(NULL, 4096,
           PROT_READ|PROT_WRITE,
            MAP_FILE|MAP_SHARED, fd, 0);

  if( (fork() ) ==0) {
    while(1) {
      sleep(2); 
      printf("\n100 bytes  at %p\n",ptr);
      fwrite( ptr , 1,100, stdout);
    }
  }
  else {
    int count = 0;
    while(count++ <100) {
      sleep(1);
      sprintf( ptr, "Hello from the other side! %d !", count);
    } 
  }
}

