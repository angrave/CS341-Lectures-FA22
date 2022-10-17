#include <stdio.h>

typedef struct _FILE {
   int fd;
   void* buffer;
   size_t capacity, size;
   int mode; // _IONBF _IOLBF _IOFBF, see setvbuf
} FILE;
// hint  fseek or fflush and lseek are useful here
void rewind(FILE*f) {
  fflush(f);
  lseek(f->fd, 0 , SEEK_SET);

}

//hint: use and reset the buffer content
// Use write
void fflush(FILE*f) {
  write(f->fd, f->buffer, f->size);
  f->size=0;
}

