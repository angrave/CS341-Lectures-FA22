#include <stdio.h>

int main() {
  FILE*file = fopen("data.csv","r");
  //goto end
  fseek(file, 0, SEEK_END);
  long position = ftell(file);
  
//  fseek(file, 0, SEEK_SET);
//or  fseek(file, -position, SEEK_CUR);
//or   fseek(file, -position, SEEK_END);
  rewind(); // go to the beginning of the file
  
  void* buffer = malloc(position);

}