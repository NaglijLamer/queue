#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "Task.hpp"
#include "Active_Object.hpp"

#include "global_metric.h"

/*
 * Struct args - this struct is used to passing arguments to thread_func.
 * thr_count - is amount of iterations per thread.
 * arg - argument for calculated function.
 * foo - calculated function in dispatch_queue (should be void*(*foo)(void *) ).\
 * ao - is active object realisation.
 */
typedef struct {
	Active_Object *ao;
	int thr_count;
	int arg;
	double (*foo)(int);
} args;

/*
 * Somee sort of test function.
 */
void say_hello(void *kek){
	printf("%s\n", "hello, sweety");
}

/*
 * Function for queue_func calculation in active object.
 */
double factorial(int arg){
	double m = 1.0;
	for (int i = 1; i <= arg; i++)
		m *= i;
	return (m);
}
/*
 * Thread main-function.
 */
void *thread_func(void *a){
	args *arg = (args*)a;
	int thr_count = arg->thr_count;
	int fact =arg->arg;
	Active_Object *ao = arg->ao;
	double res = 0.0;
	while (thr_count){
		Task temp(arg->foo, fact);
		ao->add_task(&temp);
		res = temp.result();
#ifdef _DEBUG
		printf("%f\n", res);
#endif /*_DEBUG*/
		thr_count--;
	}
	return (0);
}

/* USAGE: prog_name thr_amount iterations fact */
int main(int argc, char *argv[]){
	Active_Object *ao = new Active_Object();

	/*Get arguments from argv*/
	args arg;
	int amount_thr = atoi(argv[1]);
	arg.thr_count = atoi(argv[2]) / amount_thr;
	arg.arg = atoi(argv[3]);
	arg.foo = factorial;
	arg.ao = ao;
	
	pthread_t ao_thread = ao->activate();

	/*Create threads*/
	pthread_t *threads;
	threads = (pthread_t*)malloc(sizeof(pthread_t) * amount_thr);
	for (int i = 0; i < amount_thr; i++)
		pthread_create(&(threads[i]), NULL, &thread_func, (void*)&arg);
	/*Wait for all threads*/
	for (int i = 0; i < amount_thr; i++)
		pthread_join(threads[i], NULL);

	/*Send terminate task*/
	Task end;
	ao->add_task(&end);
	/*Should move this to destructor?..*/
	pthread_join(ao_thread, NULL);
	delete ao;

	return (0);
}
