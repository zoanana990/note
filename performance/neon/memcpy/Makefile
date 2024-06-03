CC = gcc
CFLAGS = -O3 -mfpu=neon

all: benchmark

benchmark: benchmark.o
	$(CC) $(CFLAGS) -o benchmark benchmark.o

benchmark.o: benchmark.c
	$(CC) $(CFLAGS) -c benchmark.c

clean:
	rm -f benchmark benchmark.o
