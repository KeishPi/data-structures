

default: prog

a0part2.o: a0part2.c
	gcc -Wall -std=c99 -c a0part2.c

prog: a0part2.o
	gcc -Wall -std=c99 -o prog a0part2.o

clean:
	rm a0part2.o

cleanall: clean
	rm prog
