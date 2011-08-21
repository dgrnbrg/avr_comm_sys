
CC=gcc
DEPS=
CFLAGS=-std=gnu99

all: unix_signals_test

%.o: %.c $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

unix_signals_test: signals.o
	mv signals.o unix_signals_test
