/*
 * Task.hpp - definition of class Task.
 * Task - an Active Object, which can calculate stuff in Job-objects.
 * queue - a queue of Job-objects, which should be calculated.
 */

#ifndef _TASK_HPP
#define _TASK_HPP

#include "ace/Task.h"
#include "ace/Activation_Queue.h"
#include "Job.hpp"

class Task : public ACE_Task_Base {
public:
	Task(void);
	Task(int threads);
	~Task(void);
	virtual int svc(void);
	int put(Job *job, ACE_Time_Value *tv = 0);
private:
	ACE_Activation_Queue _queue;
};

#endif /*_TASK_HPP*/
