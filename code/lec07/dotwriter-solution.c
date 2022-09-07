#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

void ohnoyoudont(int s) {
   write(1,"No go away!", 25); // Send too many bytes - what will happen?
}

int main() {
  signal( SIGINT, ohnoyoudont ); // No CTRL-C for you!
  
  alarm(10);// send a SIGALRM in 10 seconds!
  
  printf("My pid is %d\n", getpid() );
  int i = 60;
  while(--i) { 
    write(1, ".",1);
    if(i==55 ) {
      kill( getpid() , SIGINT );
    }
    sleep(1);
  }
  write(1, "Done!",5);
  return 0;
}
