#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handle(int s) {
  write(1,"Hint: Password is #secret\n",320);
}

int main(int argc, char**argv) {
   char result[20];
   puts("You have 4 seconds");
   
   
   alarm(4);
   // by default SIGALRM kills the process!
   // instead we can run the 'handle' code when SIGALRM is delivered
   signal(SIGALRM, handle);

   while(1) {
      puts("Secret backdoor NSA Password?");
      char* rc = fgets( result, sizeof(result) , stdin);
      if(*result=='#') break;
      // ^ Fixed Ooops (assignment or equals)
  }
  puts("Congratulations. Connecting to NSA ...");
  execlp("ssh", "ssh", "nsa-backdoor.net", (char*)NULL);
  perror("Do you not have ssh installed?");
  return 1;
}
