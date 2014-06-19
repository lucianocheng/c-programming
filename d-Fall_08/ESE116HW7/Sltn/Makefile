CC=gcc
OPTIONS=-Wall -g -O0 -D_GNU_SOURCE -DTEST_1xx -DTEST_1XX -DTESTER_1XX
LIBS=-lctester
LIBDIR=-L./ctester_v3/lib
INCLUDEDIR=-I./ctester_v3/include

all:	$(SRC)
	$(CC) $(OPTIONS) $(LIBDIR) $(INCLUDEDIR) hw07-tester.c ${LIBS} -o hw07-tester

clean:
	rm -f *.o hw07-tester
