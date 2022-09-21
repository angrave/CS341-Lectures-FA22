#include <pthread.h>
#include <stdio.h>

int sharedcounter=0;
pthread_mutex_t m  = PTHREAD_MUTEX_INITIALIZER;

void* myfunc1(void*param) {
     int i=0; // stack variable
     pthread_mutex_lock(&m); // may block!
     for(; i < 100000;i++) {
       //printf("Thread %p i=%d\n", (void*)pthread_self() , i);
       sharedcounter ++;  
     }
     pthread_mutex_unlock(&m);
     return NULL;
}


pthread_t tid1, tid2;

int main() {
  //pthread_mutex_init(&m, NULL);
  
      pthread_create(&tid1, 0, myfunc1, NULL);      
      pthread_create(&tid2, 0, myfunc1, NULL);

      pthread_join(tid1,NULL); // will block until thread finishes

      pthread_join(tid2,NULL); // will block until thread finishes
      
      printf("%d\n", sharedcounter );
      return 0;
}
