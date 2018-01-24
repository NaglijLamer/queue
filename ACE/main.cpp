#include "ace/OS_main.h"
#include "ace/OS_NS_stdio.h"
#include "Task.hpp"
#include "Job.hpp"
#include "global_metric.h"

/*
 * argc - structure for passing arguments to thread_func
 * we need task (active object), thr_count (iterations per thread)
 * arg - argument for calculated function
 * and foo - calculated function (factorial in this test).
 * (and yep, probably, it should be smthing like void*(*foo)(void *) ).
 */
struct args {
	Task *task;
	int thr_count;
	int arg;
	double (*foo)(int);
};

/*
 * Some sort of test function for Job
 */
double say_hello(int arg){
	ACE_OS::printf("%s %d\n", "kek", arg);
	return (1.0);
}

/*
 * Function for Job-object to calculate factorial
 */
double factorial(int arg){
	double m = 1.0;
	for (int i = 1; i <= arg; i++)
		m *= i;
	return (m);
}

/*
 * Threads main-function
 */
#ifdef _ACE_MAIN_THREADS
void *thread_func(args *arg){
#else
void *thread_func(void *a){
	args *arg = (args*)a;
#endif /*_ACE_MAIN_THREADS*/
	int thr_count = arg->thr_count;
	int fact = arg->arg;
	Task *task = arg->task;
	double res = 0.0;
	while (thr_count){
		//Job temp(factorial, fact); 
		Job temp(arg->foo, fact);
		task->put(&temp);
		res = temp.result();
#ifdef _DEBUG
		ACE_OS::printf("%f\n", res);
#endif /*_DEBUG*/
		thr_count--;
	}
	return (0);
}


/* USAGE: prog_name thr_amount iterations fact */
#ifdef _ACE_MAIN_THREADS
int ACE_TMAIN(int argc, ACE_TCHAR *argv[]){

	/*Task t;
	Job j(say_hello, 5);
	Job end;
	t.put(&j);
	t.put(&j);
	Job jj(factorial, 5);
	Job jjj(factorial, 10);
	t.put(&jj);
	t.put(&jjj);
	t.put(&end);
	t.wait();
	ACE_OS::printf("%f jj\n", jj.result());
	ACE_OS::printf("%f jjj\n", jjj.result());*/

	/*
	 * Get arguments from argv
	 */
	if (argc != 4) return (-1);
	args arg;
	int amount_thr = ACE_OS::atoi(argv[1]);
	arg.thr_count = ACE_OS::atoi(argv[2]) / amount_thr;
	arg.arg = ACE_OS::atoi(argv[3]);
	arg.foo = factorial;

	/*args arg;
	arg.fact = 12;
	arg.thr_count = 280000;*/
	//arg.thr_count = 420000;
	//arg.thr_count = 840000;
	//arg.thr_count = 28000;
	//arg.thr_count = 100000;
	//arg.thr_count = 10;

	/* Start new Active Object */
	arg.task = new Task();

	//ACE_Thread_Manager::instance()->spawn(ACE_THR_FUNC(thread_func), (void*)&task, THR_NEW_LWP | THR_DETACHED);
	/*ACE_Thread_Manager::instance()->spawn_n(3, ACE_THR_FUNC(thread_func), (void*)&arg, THR_NEW_LWP | THR_DETACHED);
	ACE_Thread_Manager::instance()->wait();*/
	/*ACE_Thread_Manager::instance()->spawn_n(3, ACE_THR_FUNC(thread_func), (void*)&arg, THR_NEW_LWP | THR_DETACHED,
		ACE_DEFAULT_THREAD_PRIORITY, 500);*/
	
	/* Start amount_thr threads and wait for them */
	ACE_Thread_Manager::instance()->spawn_n(amount_thr, ACE_THR_FUNC(thread_func), (void*)&arg, THR_NEW_LWP,
		ACE_DEFAULT_THREAD_PRIORITY, 500);
	ACE_Thread_Manager::instance()->wait_grp(500);

	/* 
	 * Terminate Task and then delete it 
	 * Object created by Job default constructor has nullptr as its function
	 * If Task-object sees that function is nullptr - it terminates
	 */
	Job end;
	arg.task->put(&end);
	arg.task->wait();
	delete arg.task;

	return (0);
}

#else

/*
 * This main function uses pthreads instead of ACE-threads for comparision with
 * other active object realisations.
 */

#include <pthread.h>

int main(int argc, char *argv[]){
	if (argc != 4) return (-1);
	args arg;
	int amount_thr = atoi(argv[1]);
	arg.thr_count = atoi(argv[2]) / amount_thr;
	arg.arg = atoi(argv[3]);
	arg.foo = factorial;
	arg.task = new Task();
	pthread_t *threads;
	threads = (pthread_t*)malloc(sizeof(pthread_t) * amount_thr);
	for (int i = 0; i < amount_thr; i++)
		pthread_create(&(threads[i]), NULL, &thread_func, (void*)&arg);
	for (int i = 0; i < amount_thr; i++)
		pthread_join(threads[i], NULL);
	Job end;
	arg.task->put(&end);
	arg.task->wait();
	delete arg.task;
	return (0);
}

#endif /*_ACE_MAIN_THREADS*/
