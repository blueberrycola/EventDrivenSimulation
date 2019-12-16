//Project 2: Event-Driven Simulation
//Name: Chase Johnston
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* function for initialization of LinkedList */

void init(queue *q) {
	
	q -> count = 0;
	q -> front = NULL;
	q -> rear = NULL;
}
/* remove person who is first in line */
data dequeue(queue *q) {
	data d;
	elem *p;
	d = q -> front -> d;
	p = q -> front;
	q -> front = q -> front -> next;
	q -> count--;
	free(p);
	return d;
}

void enqueue(data d, queue *q) {
	elem *p;

	p = malloc(sizeof(elem));
	p -> d = d;
	p -> next = NULL;
	if(!empty(q)) {
		q -> rear -> next = p;
		q -> rear = p;
		q -> count++;
	} else {
		q -> front = q -> rear = p;
		q -> count++;
	}
}

data front(const queue *q) {
	return(q -> front -> d);
}

data rear(const queue *q) {
	return(q -> rear -> d);
}

boolean empty(const queue *q) {
	return((boolean) (q -> count == EMPTY));
}
boolean full(const queue *q) {
	return((boolean) (q -> count == FULL));
}





