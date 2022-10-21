#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void dirlist(char*path) {
  
  struct dirent* dp;
  DIR* dirp = opendir(path);

  while ((dp = readdir(dirp)) != NULL) {

     char newpath[strlen(path) + strlen(dp->d_name) + 1];

     sprintf(newpath,"%s/%s", newpath, dp->d_name);

     printf("%s%s \n", dp->d_name);

     dirlist(newpath);
  }
}

int main(int argc, char**argv) { dirlist(argv[1]);return 0; }
