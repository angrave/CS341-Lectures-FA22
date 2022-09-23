#include <stdio.h>

int main() {
  printf("String at address %p \n", "I'm a string literal aka character array");
  
  int bad = (int) "Hi";
  printf("Hex bad = %x\n", bad);
  puts( (char*) bad);
  return 0;
}
