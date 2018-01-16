CC=gcc
CFLAGS=-Wall -std=c99

all: prog

prog: dynamicArray.o dynamicArrayMain.o
	gcc -g -Wall -std=c99 -o prog dynamicArray.o dynamicArrayMain.o
dynamicArray.o: dynamicArray.c dynArray.h
	gcc -g -Wall -std=c99 -c dynamicArray.c
dynamicArrayMain.o: dynamicArrayMain.c dynArray.h
	gcc -g -Wall -std=c99 -c dynamicArrayMain.c

clean:
	-rm *.o

cleanall: clean
	-rm prog
