CC=clang

# Hint: You can use 'find /usr -name 'openssl' to search for the openssl library

OPENSSL_DIR=/usr/local/opt/openssl
CPPFLAGS=-I$(OPENSSL_DIR)/include -Wno-pointer-sign
LDFLAGS=-lpthread -lcrypto -L$(OPENSSL_DIR)/lib

all : miner-singlethread  miner-attempt miner-solution

miner-singlethread : miner-singlethread.c
	$(CC) $(CPPFLAGS) $(LDFLAGS) miner-singlethread.c -o miner-singlethread
	
miner-attempt: miner-attempt.c
	$(CC) $(CPPFLAGS) $(LDFLAGS) miner-attempt.c -o miner-attempt

miner-solution : miner-solution.c
	$(CC) $(CPPFLAGS) $(LDFLAGS) miner-solution.c -o miner-solution

clean:
		rm miner-singlethread miner-attempt miner-solution 2>/dev/null || true