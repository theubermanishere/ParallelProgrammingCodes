#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

struct node_t{
  	Value *value;
  	Pointer *next;
};

struct pointer_t{
  	int count;
  	Node *nptr;
};

struct queue_t{
  	Pointer *head,*tail;;
};

Queue * q_initialize() {
  	Queue *queue = (Queue*)malloc(sizeof(Queue));
  	Node *node = (Node*)malloc(sizeof(Node));
  	Pointer *nodeptr = (Pointer*)malloc(sizeof(Pointer));

  	node->next = NULL;
  	node->value = NULL;
  	nodeptr->count = 1;
  	nodeptr->nptr = node;
  	queue->head = queue->tail = nodeptr;
  	__sync_synchronize();
  	return queue;
}

void qpush(Queue *queue,void *value) {

  	Pointer *next,*head,*tail;

  	Node *node = (Node*)malloc(sizeof(Node));

  	Pointer *nodeptr = (Pointer*)malloc(sizeof(Pointer));

  	node->value = value;
  	node->next = NULL;
  	nodeptr->count = 1;
  	nodeptr->nptr = node;

  	while(1){
    	head = queue->head;
    	tail = queue->tail;
    	next = tail->nptr->next;

    	if (tail == queue->tail) {
      		if(next == NULL){
				__sync_fetch_and_add(&(nodeptr->count),1);
				if (__sync_bool_compare_and_swap(&(tail->nptr->next),(long long unsigned int)next,nodeptr)){
	  				if (__sync_bool_compare_and_swap(&(queue->tail),(long long unsigned int)tail,nodeptr)){
	    				break;
	  				}
				}
      		} else {
				__sync_fetch_and_add(&(next->count),1);
				if (__sync_bool_compare_and_swap(&(queue->tail),(long long unsigned int)tail,next->nptr)){
				}
      		}
    	}
 	}
}

Value * qpop(Queue *queue,int thrd){

  	Pointer *head = NULL;
  	Pointer *tail = NULL;
  	Pointer *_next = NULL;
  	Pointer *tmp = NULL;
  	Value *val = NULL;

  	while (1){
    	head = queue->head;
    	tail = queue->tail;

    	if(head == tail) return NULL;

    	if (queue->head->count == 0) {
      		if (__sync_bool_compare_and_swap(&(queue->head->nptr),_next,_next)) return NULL;

      		Node *_nptr = (Node *) malloc(sizeof(Node));
      		_nptr->next = NULL;
      		_nptr->value = NULL;

      		__sync_bool_compare_and_swap(&(queue->tail->count),queue->tail->count,0);
      		while(1){ if(__sync_bool_compare_and_swap(&(queue->tail->nptr),queue->tail->nptr,_nptr)) break; }
      		while(1){ if(__sync_bool_compare_and_swap(&(queue->head),queue->head,queue->tail)) break; }
    	}

    	tmp = (Pointer *)queue->head->nptr->next;
    	_next = queue->head->nptr->next;
    	int count = head->count;

    	if (_next == NULL) return NULL;

    	if (head == queue->head){
      		if (head->nptr == tail->nptr){
				if (_next == NULL) return NULL;
				__sync_fetch_and_add(&(_next->count),1);
				if (!__sync_bool_compare_and_swap(&(queue->tail),(long long unsigned int)tail,_next)) continue;
      		} else {
				val = _next->nptr->value;
				__sync_synchronize();

				if (_next->nptr->next == NULL) {
	  				if (__sync_bool_compare_and_swap(&(queue->head->nptr),(long long unsigned int)queue->head->nptr,_next->nptr)) {
	    				__sync_bool_compare_and_swap(&(queue->tail),queue->tail,queue->head);	    
	    				__sync_synchronize();
	    				break;
	  				}
	  				break;
				}
				__sync_fetch_and_add(&(_next->count),1);
				if (__sync_bool_compare_and_swap(&(queue->head->nptr->next),(long long unsigned int)tmp,_next->nptr->next)) {
	  				__sync_synchronize();
	  				free(_next->nptr);
	  				free(_next);
	  				break;
				}
      		}
    	}
  	}


  	return val;
}

void queue_free(Queue *queue){
  	if (queue->head == queue->tail){
    	free(queue->head->nptr);
    	free(queue->head);
    	free(queue);
  	} else if(queue->head != NULL && queue->tail != NULL){
    	free(queue->head->nptr);
    	free(queue->head);
    	free(queue->tail->nptr);
    	free(queue->tail);
    	free(queue);
  	}
}
