#include <xmmintrin.h>
#include <functional>
#include "Active_Object.hpp"
#include <stdio.h>

Active_Object::Active_Object(){
	mpscq_node_t *stub = new mpscq_node_t();
	mpscq_create(&(this->queue), stub);
}

Active_Object::~Active_Object(){
	/*should delete all nodes if queue has any*/
	mpscq_node_t *node;
	while ((node = mpscq_pop(&(this->queue))) != 0)
		delete node;
	delete this->queue.tail;
}

pthread_t Active_Object::activate(){
	pthread_t thread;
	pthread_create(&thread, NULL, Active_Object::call_next, (void*)this);
	return (thread);
}

void *Active_Object::call_next(void *ao){
	Active_Object *th = (Active_Object*)ao;
	mpscq_node_t *node;
	while(1){
		node = mpscq_pop(&(th->queue));
		if (node != NULL){
			int res = ((Task*)(node->state))->call();
			delete node;
			if (res == -1) break;
		}
		_mm_pause();
		continue;
	}
	return (NULL);
}

void Active_Object::add_task(Task *t){
	mpscq_node_t *next = new mpscq_node_t();
	next->state = (void*)t;
	mpscq_push(&(this->queue), next);
}
