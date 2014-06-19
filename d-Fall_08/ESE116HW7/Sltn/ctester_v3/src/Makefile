CC=gcc
OPTIONS=-Wall -g -O0 -D_GNU_SOURCE

all: library

library: clean
	#Compile the archive
	$(CC) $(OPTIONS) -Wall -c cgrader.c ctester.c cassert.c stringbuf.c ese_malloc.c problem.c linked_list.c test.c
	
	#Pack the archive
	ar -q libctester.a cgrader.o ctester.o cassert.o stringbuf.o ese_malloc.o problem.o linked_list.o test.o
	ranlib libctester.a
	
	#Copy Headers / library to previous directory
	cp ./*.h ../include
	cp ./*.a ../lib

clean:
	rm -f *.o libctester.a