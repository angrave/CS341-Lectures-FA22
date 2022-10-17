#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
  
  while(1) {
    printf("Hello!\n");
    fflush(stdout);
    usleep(1E5);
  }
}