#include <unistd.h>

int main(int argc, char**argv) {
  chdir(argv[1]);
  execlp ("ls","ls",(char*)NULL);
  return 0;
}