#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
  char* basepath = ".";
  
  char* canon_basepath = realpath(basepath, NULL);
  if(argc == 1 ) {
    printf("Example use:  %s %s     [will be ALLOWED!]\n   or,        %s ../..       [will be DENIED!]\n", argv[0],argv[0],argv[0]);
    return 0;
  }
  while( * (++argv) ) {
    char* url = *argv;
    char* file;
    asprintf( &file, "%s/%s", canon_basepath , url ); 

    printf("\nRequesting file\n\"%s\"\n", file);
     
    char* canon_request = realpath(file,NULL); // return null
    
    printf("... canonical: %s\n",canon_request);
    
    if( ! canon_request) {
      puts("... 404 no such file");
      continue;
    }
    // check the requested resource includes the full basepath
    if( 0 == strncmp(canon_basepath, canon_request, strlen(canon_basepath) ) ) {
      puts("... is Allowed");
    } else {
      puts("... is Denied");
    }
    free(canon_request);
  }
  return 0;
}
