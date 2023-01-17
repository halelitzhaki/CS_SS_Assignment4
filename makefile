all: graph

graph : main.o algo.o
	gcc -Wall -g -o graph main.o algo.o

main.o: main.c algo.h
	gcc -Wall -g -c main.c

algo.o: algo.c algo.h
	gcc -Wall -g -c algo.c

.PHONY: clean all

clean:
	rm *.o graph