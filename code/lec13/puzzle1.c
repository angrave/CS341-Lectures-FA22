#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void* myfunc(void*ptr) {
  int val =  * ((int*)ptr);
  printf("My thread id is %p and I'm starting at %d\n", pthread_self(), val);
  
  return NULL;
}

pthread_t tid[10];
int main() {
  for(int i =0; i < 10; i++) {
    int *yourmem = malloc( sizeof(int));
    *yourmem = i;
    pthread_create( &tid[i], NULL, myfunc, yourmem);  
    free(yourmem);   
  }
  pthread_exit(NULL); 
  return 0;
}

