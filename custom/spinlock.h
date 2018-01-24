/*
 * spinlock.h - oldschool posix-spinlock on asm.
 * Non-crossplatform.
 */

#ifndef _SPINLOCK_H
#define _SPINLOCK_H

typedef volatile int spinlock_t;

int spin_init(spinlock_t *lock, int ignore);
int spin_lock(spinlock_t *lock);
int spin_unlock(spinlock_t *lock);

#endif
