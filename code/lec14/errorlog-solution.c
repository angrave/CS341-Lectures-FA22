#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
// gcc errorlog.c -pthread && ./a.out
// head log.txt 
// uniq log.txt

static FILE* file;
int pleaseQuit;
// Solution 1, use strerror_r
void logsolution1(char*mesg, int errnum) {
  char buffer[256];
  // Use strerror_r
 	strerror_r(errnum, buffer, sizeof(buffer)-1);
  
  // If multiple threads use this function then we should put a mutex lock around our lazy
  // creation of the file
 	if(!file) {
 	    file =fopen("log.txt","w");
 	}
  // usleep(10); // deliberately give the other thread a chance to overwrite the buffer
 	fprintf(file,"%s because '%s'\n",  mesg, buffer);
}
void * demo1(void*unused) {
  // Choose error numbers where strerror uses its internal buffer (just one for the whole process)
  while(!pleaseQuit) logsolution1("strerror_r says 5000?", 5000); // strerror(5000) = "Unknown error: 5000"
}
void * stress1(void*unused) {
  
  // Will also overwrite the internal storage of strerror 
  while(!pleaseQuit) strerror(5123); //  strerror(5123) = "Unknown error: 5123"
}

// Solution2, use a mutex lock

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void logsolution2(char*mesg, int errnum) {
  pthread_mutex_lock(&mutex);
 	char* error = strerror(errnum);
 	if(!file) {
 	    file =fopen("log.txt","w");
 	}
  // usleep(10); // deliberately give the other thread a chance to overwrite the buffer
 	fprintf(file,"%s because '%s'\n",  mesg, error);
  pthread_mutex_unlock(&mutex);
}
// ------ Soltuion 2 use a ,mutex lock to protect out critical sections ------
void * demo2(void*unused) {
  // Choose error numbers where strerror uses its internal buffer (just one for the whole process)
  while(!pleaseQuit) logsolution2("strerror says 5000?", 5000); // strerror(5000) = "Unknown error: 5000"
}
void * stress2(void*unused) {
 
  // This will also overwrite the internal storage of strerror 
  while(!pleaseQuit) {
    pthread_mutex_lock(&mutex);
    strerror(5123); //  strerror(5123) = "Unknown error: 5123"
    pthread_mutex_unlock(&mutex);
  }
}

int main() {
  pthread_t tid1,tid2;
  for(int i = 0 ; i <= 10;i++)
    printf("strerror(%d) = \"%s\"\n",i, strerror(i));
  sleep(1);
  puts("Writing the log file...");
  pthread_create(&tid1, NULL, demo2, NULL);

  puts("Starting stress test");
  pthread_create(&tid2, NULL, stress2, NULL);
  
  sleep(1);
  // Shutdown gracefully
  pleaseQuit = 1;
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  return 0; 
}
