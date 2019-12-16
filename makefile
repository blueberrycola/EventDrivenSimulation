proj2: proj2.o queue.o
	gcc proj2.o queue.o -lm -o proj2
proj2.o: proj2.c queue.h
queue.o: queue.c queue.h

test:
	./proj2
