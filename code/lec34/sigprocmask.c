#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void ctrlcpressed(int signal) {
  write(1, "###", 3);
}

int main() {
  signal (SIGINT, ctrlcpressed);
  sigset_t set;
  // #1 - copy the current mask into 'set'
  sigprocmask(SIG_BLOCK /*ignored*/, NULL /* new */, &set /* current */);
  
  // #2 add SIGINT to the set of bits
  sigaddset(&set, SIGINT);
  
  // #3 Change the process's mask
  sigprocmask(SIG_SETMASK, &set, NULL);
  
  // Now CTRL-C will create a PENDING signal that is not delivered
  
  int count = 10;
  while(--count) {
    
    puts("Hi!");
    sleep(1);
    
    if( count == 5 ) {
      puts("Unlocking signal process mask");
      // Remove SIGINT from the set
      sigdelset(&set, SIGINT);
      // Change the process's mask
      // Now a pending SIGINT will be immediately delivered.
      sigprocmask(SIG_SETMASK, &set, NULL);
    }
  }
  puts("Exiting");
}