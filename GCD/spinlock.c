#include "spinlock.h"

int spin_lock(spinlock_t *lock){
	__asm __volatile(
	"1:\tlock; decl %0\n\t"
	"jne 2f\n\t"
	".subsection 1\n\t"
	".align 16\n"
	"2:\tpause\n\t"
	"cmpl $0, %0\n\t"
	"jg 1b\n\t"
	"jmp 2b\n\t"
	".previous"
	: "=m" (*lock)
	: "m" (*lock));
	return 0;
}

int spin_unlock(spinlock_t *lock){
	__asm __volatile(
	"movl $1, %0\n\t"
	: "=m" (*lock)
	: "m" (*lock));
	return 0;
}

/*int spin_init(spinlock_t *lock, int ignore) __attribute__ ((weak, alias("spin_unlock")));*/

int spin_init(spinlock_t *lock, __attribute__ ((unused)) int ignore){
        __asm __volatile(
        "movl $1, %0\n\t"
        : "=m" (*lock)
        : "m" (*lock));
        return 0;
}
