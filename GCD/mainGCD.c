#include <stdio.h>
#include <pthread.h>
#include "spinlock.h"
#include <stdlib.h>
#include <dispatch/dispatch.h>

#include "global_metric.h"

/*
 * Struct task - this struct is used to passing arguments to queue_func.
 * result - field for result of execution of queue_func.
 * spin - is a sinlock for block reading of result until calculation is done.
 * arg - argument for calculated function.
 * foo - calculated function in dispatch_queue (should be void*(*foo)(void *) ).
 */
typedef struct {
	double result;
	spinlock_t spin;
	int arg;
	double (*foo)(int);
} task;

/*
 * Struct args - this struct is used to passing arguments to thread_func.
 * thr_count - is amount of iterations per thread.
 * arg - argument for calculated function.
 * foo - calculated function in dispatch_queue (should be void*(*foo)(void *) ).\
 * queue - is queue for active object realisation.
 */
typedef struct {
	dispatch_queue_t *queue;
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
 * queue_funcion - function for active object.
 * It is calling, when dispatcher get it from the top of queue.
 */
void queue_func(void *arg){
	task *t = (task*)arg;
	//t->result = factorial(t->arg);
	t->result = t->foo(t->arg);
	spin_unlock(&(t->spin));
}

/*
 * Thread main-function.
 */
void *thread_func(void *a){
	args *arg = (args*)a;
	int thr_count = arg->thr_count;
	int fact =arg->arg;
	dispatch_queue_t *queue = arg->queue;
	double res = 0.0;
	while (thr_count){
		task t;
		t.arg = fact;
		t.foo = arg->foo;
		spin_init(&(t.spin), 0);
		spin_lock(&(t.spin));
		dispatch_async_f(*queue, &t, queue_func);
		spin_lock(&(t.spin));
		res = t.result;
#ifdef _DEBUG
		printf("%f\n", res);
#endif /*_DEBUG*/
		thr_count--;
	}
	return (0);
}

/* USAGE: prog_name thr_amount iterations fact */
int main(int argc, char *argv[]){
	dispatch_queue_t queue;
	/* Create dispatch queue*/
	queue = dispatch_queue_create("some_queue", NULL);

	/*int amount_thr = 3;
	args arg;
	arg.queue = &queue;
	arg.thr_count = 840000 / 3;
	arg.arg = 13;
	arg.foo = factorial;*/
	/*dispatch_sync_f(queue, NULL, say_hello);*/
	
	/*Get arguments from argv*/
	args arg;
	int amount_thr = atoi(argv[1]);
	arg.thr_count = atoi(argv[2]) / amount_thr;
	arg.arg = atoi(argv[3]);
	arg.foo = factorial;
	arg.queue = &queue;

	/*Create threads*/
	pthread_t *threads;
	threads = malloc(sizeof(pthread_t) * amount_thr);
	for (int i = 0; i < amount_thr; i++)
		pthread_create(&(threads[i]), NULL, &thread_func, (void*)&arg);
	/*Wait for all threads*/
	for (int i = 0; i < amount_thr; i++)
		pthread_join(threads[i], NULL);

	/*Release dispatch_queue and finish its thread*/
	dispatch_release(queue);

	return (0);
}
