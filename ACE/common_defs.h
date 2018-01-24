/*
 * common_defs.h - i don't know, why this defines are common.
 * Some asm and C stuff to work with RDTSC-timers.
 */

#ifndef _COMMON_DEFS_H
#define _COMMON_DEFS_H

#include <inttypes.h>

#define TIMESPEC_TO_DOUBLE(x) (1000.0 * x.tv_sec + 1e-6 * x.tv_nsec)

#define RDTSC_START(cycles_high, cycles_low) \
	__asm __volatile(			\
	"cpuid\n\t"				\
	"rdtsc\n\t"				\
	"mov %%edx, %0\n\t"			\
	"mov %%eax, %1\n\t"			\
	: "=r" (cycles_high), "=r" (cycles_low)	\
	:					\
	: "%rax", "%rbx", "%rcx", "rdx"		\
	)

#define RDTSC_FINISH(cycles_high, cycles_low) \
	__asm __volatile(			\
	"rdtscp\n\t"				\
	"mov %%edx, %0\n\t"			\
	"mov %%eax, %1\n\t"			\
	"cpuid\n\t"				\
	: "=r" (cycles_high), "=r" (cycles_low)	\
	:					\
	: "%rax", "%rbx", "%rcx", "rdx"		\
	)

#define CALC_CYCLES(cycles_high, cycles_low) (((uint64_t)(cycles_high) << 32) | (cycles_low))

#endif
