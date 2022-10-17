#include <stdio.h>
#include <unistd.h>
#include <assert.h>

int main() {
  size_t bytes_sent = 0;
  
  int mypipe[2];
  pipe(mypipe);
  
  while(1) {
    printf("Bytes sent so far: %zu\n", bytes_sent);
    
    assert( write( mypipe[1], ".", 1 ) == 1);
  
    bytes_sent ++;
  }
  return 0;
}
