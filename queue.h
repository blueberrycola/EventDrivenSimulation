/* A linked list implementation of a queue */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define FULL 10000
//typedef and function prototypes for queue.c
//data is the current time the customer showed up
typedef  double	data;
typedef enum {false, true} boolean;

struct elem {
	data d;
	
	struct elem *next;
};
typedef struct elem elem;
struct queue {
	int count; //Count of elements
	elem *front; //ptr to front of queue
	elem *rear; //ptr to back of queue
};

typedef struct queue queue;
void initialize(queue *q);
void enqueue(data d, queue *q);
data dequeue(queue *q);
data front(const queue *q);
boolean empty(const queue *q);
boolean full(const queue *q);
data rear(const queue *q);


