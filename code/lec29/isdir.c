#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include  <errno.h> 
int main(int argc, char**argv) {
  char*path = argv[1];
  struct stat s;
  if(stat(path, &s) != 0) {
     fprintf(stderr,"stat failed:%s\n", strerror(errno));
     return 1;
  }
  if( S_ISDIR(s.st_mode) ) puts("Is a directory!");
  return 0;
}
