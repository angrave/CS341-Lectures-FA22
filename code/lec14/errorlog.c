#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
// gcc errorlog.c -pthread && ./a.out
// head log.txt 
// uniq log.txt

static FILE* file;


void log(char*mesg, int errnum) {
 	char* error = strerror(errnum);
 	if(!file) {
 	    file =fopen("log.txt","w");
 	}
  // usleep(10); // deliberately give the other thread a chance to overwrite the buffer
 	fprintf(file,"%s because '%s'\n",  mesg, error);
}
void * demo(void*unused) {
  // Choose error numbers where strerror uses its internal buffer (just one for the whole process)
  while(1) log("strerror says 5000?", 5000); // strerror(5000) = "Unknown error: 5000"
}
void * stress(void*unused) {
  
  // Will also overwrite the internal storage of strerror 
  while(1) strerror(5123); //  strerror(5123) = "Unknown error: 5123"
}

int main() {
  pthread_t tid1,tid2,tid3,tid4;
  for(int i = 0 ; i <= 10;i++)
    printf("strerror(%d) = \"%s\"\n",i, strerror(i));
  sleep(1);
  puts("Writing the log file...");
  pthread_create(&tid4, NULL, demo, NULL);
  sleep (1);
  puts("Starting stress test");
  pthread_create(&tid1, NULL, stress, NULL);
  
  sleep(1);
  return 0; 
}
