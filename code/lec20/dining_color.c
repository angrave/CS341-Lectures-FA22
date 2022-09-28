#include <string.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

// Demonstration of dining philosophers problem
// gcc dining_color.c -pthread -lm

typedef struct philData {
    pthread_mutex_t *fork_lft, *fork_rgt;
    const char *name;
    pthread_t thread;
    int   fail;
    int x , y; // Screen position
} Philosopher;

int slow_motion = 0;
int slow_pickup = 0;

int running = 1;
void *PhilPhunction(void *p);

int main(int argc, char**argv)
{
    
    slow_motion = argc >1 && strchr(argv[1] , 's');
    slow_pickup = argc >1 && strchr(argv[1] , 'p');
 
    setvbuf(stdout, 0, _IONBF, 0); // no buffering
    printf("\033[H\033[J"); //Clear
    
    const char *nameList[] = { "A","B","C","D","E"};
    
    pthread_mutex_t forks[5];
    Philosopher philosophers[5];
    Philosopher *phil;
    int i;
    int failed;
    
    for (i=0;i<5; i++) {
        failed = pthread_mutex_init(&forks[i], NULL);
        if (failed) {
            printf("Failed to initialize mutexes.");
            exit(1);
        }
    }
    
    for (i=0;i<5; i++) {
        phil = &philosophers[i];
        phil->name = nameList[i];
        phil->fork_lft = &forks[i];
        phil->fork_rgt = &forks[(i+1)%5];
        phil->x = 40 + 20* sin( (i+0.5) *3.14159 *2. /5 );
        phil->y = 10 + 7* cos( (i+0.5) *3.14159 *2. /5 );
        phil->fail = pthread_create( &phil->thread, NULL, PhilPhunction, phil);
    }
    
    sleep(40);
    running = 0;
    printf("cleanup time\n");
    
    for(i=0; i<5; i++) {
        phil = &philosophers[i];
        if ( !phil->fail && pthread_join( phil->thread, NULL) ) {
            printf("error joining thread for %s", phil->name);
            exit(1);
        }
    }
    return 0;
}
//http://rosettacode.org/wiki/Dining_philosophers#C 
void *PhilPhunction(void *p) {
    Philosopher *phil = (Philosopher*)p;
    int failed;
    int tries_left;
    pthread_mutex_t *fork_lft, *fork_rgt, *fork_tmp;
    
    while (running) {
        printf("\033[32m\033[%d;%dH%s is sleeping   ", phil->y,phil->x, phil->name);
        
        
        if(slow_motion) sleep(1); else usleep( 1+ rand()%8);
        
        fork_lft = phil->fork_lft;
        fork_rgt = phil->fork_rgt;
        printf("\033[31m\033[%d;%dH%s is hungry     ", phil->y,phil->x, phil->name);
        tries_left = 0;   /* try twice before being forceful */
        do {
            failed = pthread_mutex_lock( fork_lft);
            if(slow_pickup) usleep( rand() % 30); // ADDITIONAL SLEEP TO DEMONSTRATE DEADLOCK
            failed = (tries_left>0)? pthread_mutex_trylock( fork_rgt )
                                    : pthread_mutex_lock(fork_rgt);
            
            if (failed) {
                pthread_mutex_unlock( fork_lft);
                fork_tmp = fork_lft;
                fork_lft = fork_rgt;
                fork_rgt = fork_tmp;
                tries_left -= 1;
            }
        } while(failed && running);
        
        if (!failed) {
            printf("\033[35m\033[%d;%dH%s is eating\n", phil->y,phil->x,phil->name);
            
            if(slow_motion) sleep(1); else usleep( 1+ rand() % 8);
            
            pthread_mutex_unlock( fork_rgt);
            pthread_mutex_unlock( fork_lft);
        }
    }
    return NULL;
}




