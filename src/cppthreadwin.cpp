/*
 * cppthreadwin.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: christian
 */
#include "cppthread.h"

/* TODO : pthread_create and CreateThread should start the thread in suspended mode
[X] create_thread -> CREATE_SUSPENDED
*/
int CppThread::threadInit() {
	/* first zero is stack-size which if set to 0 is now 1MB*/
	/* second zero is the creation flag which if set to 0 means the thread runs immediately*/
	*(this->handle) = CreateThread(this->attr, 0, this->func, this->args, CREATE_SUSPENDED, this->tid);
	return (*((this->handle))!=NULL ? 0 : 1);
}


int CppThread::start() {
	threadInit();
	return 0;
}




