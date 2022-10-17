// Read the first half of the file as a C string
// Hint fopen, fseek, ftell, fread, malloc, fclose
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char* half(char*filename);

int main(int argc, char** argv) {
  char* contents = half("23_half_solution.c");
  printf("%s",contents);
  free(contents);
  return 0;
}

char* half(char*filename) {
  FILE* f = fopen(filename, "r");
  if(!f) {
    perror(filename);
    exit(1);
  }
  fseek(f, 0, SEEK_END);
  long halfsize = ftell(f) / 2;
  rewind(f);
  
  char* result = malloc( halfsize + 1 );
  if(!result) {
    fprintf(stderr,"malloc failed");
    exit(2);
  }
  result[ halfsize ] = '\0';
  size_t numread = fread( result, 1, halfsize , f);
  if(numread != halfsize) {
    perror("fread");
    exit(3);
  }
  
  fclose(f);
  return result;
}

