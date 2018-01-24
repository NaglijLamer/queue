#ifndef _ACTIVE_OBJECT_HPP
#define _ACTIVE_OBJECT_HPP

#include "queue.hpp"
#include "Task.hpp"
#include <pthread.h>

class Active_Object{
public:
	Active_Object();
	~Active_Object();
	pthread_t activate();
	void add_task(Task *t);
private:
	mpscq_t queue;
	static void *call_next(void *ao);
};

#endif /*_ACTIVE_OBJECT_HPP*/
