/*
 * Spinlock.hpp - definition of class Spinlock.
 * Simple C++style wrapper for C-style spinlock in spinlock.h
 */

#ifndef _SPINLOCK_HPP
#define _SPINLOCK_HPP

#include "spinlock.h"

class Spinlock {
public:
	Spinlock(void);
	int lock();
	int unlock();
private:
	spinlock_t _spinlock;
};

#endif /*_SPINLOCK_HPP*/
