#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
   char *fileToServe = argv[1];
   char* path = realpath(fileToServe, NULL); 
   puts(path);
   free(path);
  return 0;
}
