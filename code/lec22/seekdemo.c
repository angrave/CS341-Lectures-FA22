#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    FILE* f = fopen("data.csv","w");
    fprintf(f, "My password is 1234");
    fflush(f);
    
    long posn = ftell(f);
    printf("My position is %ld\n", posn);
    
    fflush(f);
    pid_t child = fork();
    if(child) {
      rewind(f);
      fflush(f);
      fclose(f);
      exit(0);
    }
    // parent
    sleep(1); // Mwa mwa . synchronization what's that?
    
    fprintf(f,"5678");
    fflush(f);
    
    fclose(f);
    return 0;
}
