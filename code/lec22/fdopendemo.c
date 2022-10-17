#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  FILE*f = fdopen( 1, "w");
  write( 1, "simple", 6);
  fprintf( f, "%g", 3.141 * 13.123);
  fclose(f);
  return 0;
}
