#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
   int signal = atoi(argv[1]);
   pid_t pid = atoi( argv[2] );

  if(signal && pid) kill(pid, signal);
  return 0;
} 

