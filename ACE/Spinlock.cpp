#include "Spinlock.hpp"

Spinlock::Spinlock(void){
	spin_init(&(this->_spinlock), 0);
}

int Spinlock::lock(){
	return (spin_lock(&(this->_spinlock)));
}

int Spinlock::unlock(){
	return (spin_unlock(&(this->_spinlock)));
}
