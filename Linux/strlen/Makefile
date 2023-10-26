CC = gcc
CFLAGS = -Wall -O2
LDFLAGS =

all: strlen_perf

strlen_perf: main.c strlen.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ 2> log.Makefile

clean:
	rm -f strlen_perf *.log *.png log.Makefile

.PHONY: all clean plot

check: strlen_perf
	./strlen_perf
plot:
	gnuplot -e "set terminal png; set output 'strlen_perf.png'; plot 'strlen_perf.log' using 1:2 with lines title 'strlen linux', 'strlen_perf.log' using 1:3 with lines title 'strlen gcc'"
