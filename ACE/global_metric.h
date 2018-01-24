/*
 * global_metric.h - constructor and destructor functions to calculate execution time
 * in seconds and proc cycles. Executes before and after main program. 
 * Some sort of GNU C features, afaik.
 * Should define _METRIC to use it.
 */

#ifdef _METRIC
#ifndef _GLOBAL_METRIC_H
#define _GLOBAL_METRIC_H

#include <time.h>
#include <stdio.h>
#include "common_defs.h"

#define OUTPUTGL "Program execution time: %f\nCount of cycles: %lu\n"

struct timespec __start_time;
unsigned cycles_high, cycles_low, cycles_high_f, cycles_low_f;

int start_global_timer() __attribute__((constructor(102)));
int finish_global_timer() __attribute__((destructor(102)));

int start_global_timer(){
        clock_gettime(CLOCK_MONOTONIC, &__start_time);
	RDTSC_START(cycles_high, cycles_low);
        return 0;
}

int finish_global_timer(){
        struct timespec finish_time;
	RDTSC_FINISH(cycles_high_f, cycles_low_f);
        clock_gettime(CLOCK_MONOTONIC, &finish_time);
	uint64_t cycles = CALC_CYCLES(cycles_high_f, cycles_low_f) - CALC_CYCLES(cycles_high, cycles_low);
        double time = TIMESPEC_TO_DOUBLE(finish_time) - TIMESPEC_TO_DOUBLE(__start_time);
        fprintf(stderr, OUTPUTGL, time, cycles);
        return 0;
}

#endif
#endif
