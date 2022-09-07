#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
// There is no good reason why exit() should reset the file pos when feof is set
//
//Re. fflush(file)-"        For input streams associated with seekable files (e.g., disk files, but not pipes or terminals), fflush() discards any buffered data that has
//       been fetched from the underlying file, but has not been consumed by the application.
#include <gnu/libc-version.h>

int main(int argc, char**argv) {
 printf("GNU libc version: %s\n", gnu_get_libc_version());
   printf("Expected output is three lines (A,B,C):\n");
   FILE*f = fopen("test.txt","w");
   fprintf(f,"A\nB\nC\n");
   fclose(f);
   f= NULL;
   
   int test = argc > 1 ? atoi(argv[1]) : 0;

   size_t buffer_cap = 0;
   char * buffer = NULL;

   FILE * file = fopen("test.txt","r");
   int count = 0;
   while(count < 10) {
      ssize_t size = getline( &buffer, &buffer_cap, file);
      if(size <0) break;

      printf("%d %s", count++, buffer);
      if(test == 1) fflush(file); // workaround; shh! don't let exit() notice buffer at eof

      if(fork() ==0) { 
         if(test == 2) fclose(file); //workaround
         if(test == 3) _exit(0); // workaround

         exit(0); // bad exit() no cookie. You didnt need to lseek at the eof
      }
      wait( NULL);
   }
   return 0;
}
