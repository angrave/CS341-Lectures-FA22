#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
   char** lineptr;
   size_t size;
   size = getline(lineptr, &size, stdin);
   execlp(lineptr);
   return 0;
}
