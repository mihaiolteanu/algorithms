/* queue.h - Implementation of a generic queue data structure
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include "array.h"

typedef struct {
	array *a;
} queue;

// Init the already allocated queue q. The queue will hold elements
// of size tsize. 
extern int queue_init(queue *q, size_t tsize);

// Insert element x at the back of the queue q. The sizeof x should
// be equal to tsize from the queue_init function
extern int queue_enqueue(queue *q, void *x);

// Return and remove the front item from the queue q. If queue is empty
// returns NULL. The returned pointer should be cast to the type used
// to initialize the queue with. The returned pointer should be freed once
// it is no longer needed.
extern void *queue_dequeue(queue *q);

extern void queue_destroy(queue *q);

#endif // QUEUE_H
