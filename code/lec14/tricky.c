#include <stdio.h>
#include <pthread.h>

pthread_t tid1,tid2;
pthread_mutex_t spoon= PTHREAD_MUTEX_INITAILIZER;
  
int counter;

void* myfunc2(void*param) {
 int i = 0; // stack variable
 for(; i < 1000000;i++) {
   pthread_mutex_lock( &spoon);
   counter ++;
  
 }
 return NULL;
}

int main() {
//pthread_mutex_init( &spoon, NULL);
 pthread_create(&tid1, 0, myfunc2, NULL);
 pthread_create(&tid2, 0, myfunc2, NULL);
 pthread_join(tid1,NULL);
 pthread_join(tid2,NULL);
 printf("%d\n", counter );
return 0;
}
