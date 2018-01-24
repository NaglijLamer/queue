#include "Task.hpp"
#include "Job.hpp"

Task::Task(void) : Task(1)
{}

Task::Task(int threads) {
	if (this->activate(THR_NEW_LWP, threads) == -1) {
		ACE_ERROR((LM_ERROR, "%p\n", "smth wrong"));
	}
}

Task::~Task(void){
	/*ACE_DEBUG?*/
}

int Task::svc(void){
	while(1){
		ACE_Method_Request *request = this->_queue.dequeue();
		if (request == nullptr)
			return (-1);
		int result = request->call();
		if (result != 0) break;
	}
	return (0);
}

/*is enqueue have overloading with ACE_Time_Value arg?*/
int Task::put(Job *job, ACE_Time_Value *tv){
	return (this->_queue.enqueue(job));
}
