#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
  // asprintf
  // strncmp
  char* fileToServe = 0;
  asprintf( &fileToServe ,"%s/%s", "sub1", "sub2/cat.jpg");
  
  
  char* path = realpath(fileToServe, NULL); 
  char *basepath = realpath("sub1", NULL);
  if(path) {
    puts(path);
    if (0==strncmp(path, basepath, strlen(basepath))) {
      puts("Looks valid to me!");
    }
  } else {
    puts("No such path!");
  }
  free(fileToServe);
  free(path);
  
  return 0;
}
