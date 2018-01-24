#include "queue.hpp"

void mpscq_create(mpscq_t *self, mpscq_node_t *stub){
    stub->next = 0;
    self->head = stub;
    self->tail = stub;
}

void mpscq_push(mpscq_t *self, mpscq_node_t *n){
    n->next = 0;
    //mpscq_node_t *prev = XCHG(&self->head, n); // serialization-point wrt producers, acquire-release
	mpscq_node_t *prev = __sync_lock_test_and_set(&(self->head), n);
    prev->next = n; // serialization-point wrt consumer, release
}

mpscq_node_t *mpscq_pop(mpscq_t *self){
    mpscq_node_t *tail = self->tail;
    mpscq_node_t *next = tail->next; // serialization-point wrt producers, acquire
    if (next){
        self->tail = next;
        tail->state = next->state;
        return (tail);
    }
    return (0);
} 
