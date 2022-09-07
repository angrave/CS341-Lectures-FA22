#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
int pleasequit = 0;


void wakeup(int signal) {
  // signal == SIGALRM
  pleasequit = 1;
}

int main() {

  printf("My pid is %d\n", getpid() );
  
  int i = 60;
  while(--i) { 
    write(1, ".",1);
    sleep(1);
  }
  write(1, "Done!",5);
  return 0;
}
