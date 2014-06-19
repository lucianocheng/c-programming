CC=gcc
OPTIONS=-Wall -g -O0 -D_GNU_SOURCE


all:	clean
	$(CC) $(OPTIONS) -c ctester.c cassert.c
	ar -q libctester.a ctester.o cassert.o

clean:
	rm -f *.o libctester.a

