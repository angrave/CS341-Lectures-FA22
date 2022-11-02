#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> /*isprint*/

void quit(const char*mesg) {
  perror(mesg);
  exit(1);
}

int main(int argc, char**argv) {
  if(argc != 2) {
    fprintf(stderr, "Prints sequences of printable characters found in files\n");
    fprintf(stderr, "Usage: %s filename\n",argv[0]);
    exit(1);
  }
  FILE*file = fopen(argv[1],"r");
  if(!file) { quit("could not open file"); }
    
  int count = 0;
  while(1) {
    int ch = fgetc(file);
    if(ch <0) break;
    
     if(  isprint( ch ) ) {
       count ++;
     } else {
       if(count > 2) {
         fseek(file, - count -1, SEEK_CUR);
         for( ; count; count--) {
           ch = fgetc(file);
           if(ch == -1) break;
           putchar( ch );
         }
         putchar('\n');
       }
       count = 0;
     }
   }
   return 0;
}

