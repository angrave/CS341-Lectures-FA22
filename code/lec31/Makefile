CC=clang
LDFLAGS = -lm -lSDL2 -L ${HOME}/localinstall/lib

all : mmap1 mmap2 strings-fseekfgetc strings-mmap 

mmap1 : mmap1.c 
	$(CC) $(CFLAGS)  $(LDFLAGS) mmap1.c -o $@

mmap2 : mmap2.c 
	$(CC) $(CFLAGS)  $(LDFLAGS) mmap2.c -o $@

strings-fseekfgetc : strings-fseekfgetc.c 
	$(CC) $(CFLAGS)  $(LDFLAGS) strings-fseekfgetc.c -o $@

strings-mmap : strings-mmap.c 
	$(CC) $(CFLAGS)  $(LDFLAGS) strings-mmap.c -o $@

clean :
	rm mmap1 mmap2 strings-fseekfgetc strings-mmap 2>/dev/null || true
