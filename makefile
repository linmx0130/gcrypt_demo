CC = gcc
CFLAGS = `libgcrypt-config --cflags` -Wall -g -std=gnu99
LIBS = `libgcrypt-config --libs`
OBJS = crypt decrypt common.o crypt.o decrypt.o

all: $(OBJS)
common.o: common.c
	$(CC) -c -o common.o common.c $(CFLAGS) 

crypt.o: crypt.c
	$(CC) -c -o crypt.o crypt.c $(CFLAGS) 

crypt: crypt.o common.o
	$(CC) -o crypt crypt.o common.o $(CFLAGS) $(LIBS)
decrypt.o: decrypt.c
	$(CC) -c -o decrypt.o decrypt.c $(CFLAGS)
decrypt: decrypt.o common.o
	$(CC) -o decrypt decrypt.o common.o $(CFLAGS) $(LIBS)

clean:
	rm $(OBJS)
