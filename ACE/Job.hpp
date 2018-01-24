/*
 * Job.hpp - definition of class Job.
 * Object of class Task can calculate set of Job-objects.
 * foo - pointer to function, which will be calculate in Task.
 * arg - argument for this function, should be void* in better class.
 * result - variable to store result of calculation, also should be void*.
 * result_lock - spinlock for waiting of result. 
 */

#ifndef _JOB_HPP
#define _JOB_HPP

#include "ace/Method_Request.h"
#include "Spinlock.hpp"

class Job : public ACE_Method_Request{
public:
	Job(void);
	Job(double (*foo)(int), int arg);
	virtual int call(void);
	double result();
private:
	double (*_foo)(int);
	int _arg;
	double _result;
	Spinlock _result_lock;
};

#endif /*_JOB_HPP*/
