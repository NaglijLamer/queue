/*
 * Task.hpp - definition of class Task.
 * Object of class Task can calculate set of Task-objects.
 * foo - pointer to function, which will be calculate in Task.
 * arg - argument for this function, should be void* in better class.
 * result - variable to store result of calculation, also should be void*.
 * result_lock - spinlock for waiting of result. 
 */

#ifndef _TASK_HPP
#define _TASK_HPP

#include "Spinlock.hpp"

class Task {
public:
	Task(void);
	Task(double (*foo)(int), int arg);
	int call(void);
	double result();
private:
	double (*_foo)(int);
	int _arg;
	double _result;
	Spinlock _result_lock;
};

#endif /*_TASK_HPP*/
