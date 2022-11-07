CC=clang

all :  epoll1  Makefile  nonblockread  pipewriter

epoll1 : epoll1.c 
	$(CC) $(CFLAGS)  $(LDFLAGS) epoll1.c -o $@

nonblockread : nonblockread.c 
	$(CC) $(CFLAGS)  $(LDFLAGS) nonblockread.c -o $@

pipewriter : pipewriter.c 
	$(CC) $(CFLAGS)  $(LDFLAGS) pipewriter.c -o $@

clean :
	rm pipe1 pipe2 epoll1 nonblockread  pipewriter 2>/dev/null || true
