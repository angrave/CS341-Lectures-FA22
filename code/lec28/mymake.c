#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>

int main() {
  struct stat src, tgt;
  int s_ok = stat("prog.c", & src);
  int t_ok = stat("a.out", & tgt);
  double delta = difftime( src.st_mtime, tgt.st_mtime);
// -ve if t1 before t2
  // Think carefully about what behavior you'd like if
  // * delta is zero i.e. mod time of source code is within the granularity of the file system timestamps
  // output file does not exist
  // unable to read the modification time (stat fails for any reason)
  
  if( s_ok != 0 || t_ok !=0  || delta >= 0) {
     puts("Compiling");
     system("clang prog.c");
  } else {
    puts("nothing to do");
  }
return 0;
}
