#include <sys/types.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/version.h>

char* explain(int e) {
  static char result[1024]; // not thread safe (but static so we can return a pointer)
  *result = '\0';

  if(e & EPOLLOUT) { strcat(result, ",EPOLLOUT" ); e -= EPOLLOUT; }
  if(e & EPOLLIN) { strcat(result, ",EPOLLIN" ); e -= EPOLLIN; }
  if(e & EPOLLRDHUP) { strcat(result, ",EPOLLRDHUP"); e -= EPOLLRDHUP; }
  if(e & EPOLLERR) { strcat(result, ",EPOLLERR"); e-= EPOLLERR; }
  if(e & EPOLLHUP) { strcat(result, ",EPOLLHUP"); e -= EPOLLHUP; }
  // The remainder will not be returned by epoll_wait
  // but are options for epoll mod
  if(e & EPOLLET) { strcat(result, ",EPOLLET"); e -= EPOLLET; }
  if(e & EPOLLONESHOT) { strcat(result, ",EPOLLONESHOT"); e -= EPOLLONESHOT; }
  if(e & EPOLLWAKEUP) { strcat(result, ",EPOLLWAKEUP"); e -= EPOLLWAKEUP; }
  #if LINUX_VERSION_CODE >= KERNEL_VERSION(4,5,0)
  if(e & EPOLLEXCLUSIVE) { strcat(result, ",EPOLLEXCLUSIVE"); e -= EPOLLEXCLUSIVE; }
  #endif

  // Print the value of unidentified flags
  if(e) sprintf( strlen(result) + result, ",%d",e);

  if(strlen(result) == 0) strcpy(result,",none");

  *result = '['; // overwrites unnecessary ','
  strcat(result,"]");
  return result;
}


#define QUIT {fprintf(stderr,"Quit at line %d\n",__LINE__); perror("");exit(1);}

char buffer[2];

int main() {
  puts("Creating pipes");
  mkfifo("./pipe1",0600);
  mkfifo("./pipe2",0600);

  puts("Opening pipes"); 
  int fd1 = open("pipe1",O_RDONLY | O_NONBLOCK);
  int fd2 = open("pipe2",O_RDONLY | O_NONBLOCK);
  
  if(fd1 == -1 || fd2 == -1) {QUIT}
  printf("File descriptors %d and %d\n",fd1,fd2);
  puts("Creating epoll");
 
  int epollfd = epoll_create(42 /*positive*/);
  
  struct epoll_event ev1 = {.events = EPOLLIN, .data.fd = fd1};
  struct epoll_event ev2 = {.events = EPOLLIN, .data.fd = fd2};
  
  epoll_ctl(epollfd, EPOLL_CTL_ADD, fd1, &ev1);
  epoll_ctl(epollfd, EPOLL_CTL_ADD, fd2, &ev2);
    
  
  while(1) {
    int timeout = 10; // -1 == forever
    
    struct epoll_event array[100];
    int num_events = epoll_wait(epollfd , array, 100 /* max events */, 1000 /* timeout ms*/);
    
    printf("epoll_wait returned %d events\n", num_events); // expect -1,0, or 1
  
    if(num_events == -1)  { QUIT }
  
    for(int i= 0 ; i < num_events; i++) {
        int fd = array[i].data.fd;
        int event = array[i].events;

        printf("\tEvent %d on file descriptor %d : %d %s\n", i, fd, event, explain(event));
        sleep(1);
        // One or more flags may be set, so we wont use switch
        //
        if(event & EPOLLIN) {   
          ssize_t bytes = read(array[i].data.fd, buffer, sizeof(buffer));
          printf("\t\tread(fd=%d) returned %d.\n", array[i].data.fd, (int)bytes);
          if(bytes>0) fwrite(buffer, 1, bytes,stdout);
        }

        if( event & ( EPOLLHUP | EPOLLRDHUP | EPOLLERR)) {
          puts("\t\tRemoving fd from epoll set");
          epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
        }
        printf("\n");
        sleep(1);
    }
  } 
}
