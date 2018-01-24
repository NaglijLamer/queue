#include "Job.hpp"

Job::Job(void){
	this->_foo = nullptr;
}

Job::Job(double (*foo)(int), int arg){
	this->_foo = foo;
	this->_arg = arg;
	this->_result_lock.lock();
}

int Job::call(void){
	if (this->_foo == nullptr)
		return (-1);
	this->_result = this->_foo(this->_arg);
	this->_result_lock.unlock();
	return (0);
}

double Job::result(){
	this->_result_lock.lock();
	double res = (this->_result);
	/*really? I think, Job object will die with Spinlock object
	  We need this, if Job will be reusable object*/ 
	//this->_result_lock.unlock();
	return (res);
}
