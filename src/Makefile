CC=gcc
SEQ_CFLAGS=-Wall
PAR_CFLAGS=-Wall -lpthread
SEQ=seq_heapsort
PAR=par_heapsort

.DEFAULT_GOAL := all

all: seq par

seq: $(SEQ).c
	$(CC) $(SEQ_CFLAGS) $(SEQ).c -o $(SEQ)

par: $(PAR).c
	$(CC) $(PAR_CFLAGS) $(PAR).c -o $(PAR)

clean:
	rm -rf seq_heapsort par_heapsort
