#ifndef _QUEUE_HPP
#define _QUEUE_HPP

struct mpscq_node_t {
	mpscq_node_t* volatile next;
	void *state;
};

struct mpscq_t {
	mpscq_node_t* volatile head;
	mpscq_node_t *tail;
};

void mpscq_create(mpscq_t *self, mpscq_node_t *stub);
void mpscq_push(mpscq_t *self, mpscq_node_t *n);
mpscq_node_t *mpscq_pop(mpscq_t *self);

#endif /*_QUEUE_HPP*/
