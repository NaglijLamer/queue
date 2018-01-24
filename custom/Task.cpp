#include "Task.hpp"

Task::Task(void){
	this->_foo = nullptr;
}

Task::Task(double (*foo)(int), int arg){
	this->_foo = foo;
	this->_arg = arg;
	this->_result_lock.lock();
}

int Task::call(void){
	if (this->_foo == nullptr)
		return (-1);
	this->_result = this->_foo(this->_arg);
	this->_result_lock.unlock();
	return (0);
}

double Task::result(){
	this->_result_lock.lock();
	double res = (this->_result);
	/*really? I think, Task object will die with Spinlock object
	  We need this, if Task will be reusable object*/ 
	//this->_result_lock.unlock();
	return (res);
}
