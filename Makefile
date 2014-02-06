
CC      = mpicc
CFLAGS  = -Wall -ansi -O2

OBJECTS = as3.o common.o

all: primes

primes : $(OBJECTS)
	$(CC) -o $@  $(OBJECTS) -L/sw/lib/gmp5 -lgmp

clean:
	rm *.o primes*

