CC=gcc
SEQ_CFLAGS=-Wall
PAR_CFLAGS=-Wall -lpthread -lm
SEQ=seq_heapsort
PAR=par_heapsort
OS:= $(shell uname -s)

ifeq ($(OS), Darwin)
	PAR_CFLAGS += -Xpreprocessor -fopenmp -lomp
	SEQ_CFLAGS += -Xpreprocessor -fopenmp -lomp
else
	PAR_CFLAGS += -fopenmp
	SEQ_CFLAGS += -fopenmp
endif

.DEFAULT_GOAL := all

all: seq par

seq: $(SEQ).c
	$(CC) $(SEQ_CFLAGS) $(SEQ).c -o $(SEQ)

par: $(PAR).c
	$(CC) $(PAR_CFLAGS) $(PAR).c -o $(PAR)

clean:
	rm -rf seq_heapsort par_heapsort
