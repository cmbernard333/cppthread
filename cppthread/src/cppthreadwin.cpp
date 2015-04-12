/*
 * cppthreadwin.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: christian
 */
#include "cppthread.h"

CppThread::CppThread(thread_func_t tFunc, thread_args_t tArgs) : func(tFunc), args(tArgs) {
	thread_attr_init(&this->attr);
	thread_id_init(this->tid);
	thread_handle_init(this->handle);
}

CppThread::CppThread(thread_func_t tFunc, thread_attr_t attrs, thread_args_t tArgs) : func(tFunc), attr(attrs), args(tArgs) {
	thread_id_init(this->tid);
	thread_handle_init(this->handle);
}

CppThread::~CppThread() {
	thread_id_safe_destroy(this->tid);
	thread_handle_safe_destroy(this->handle);
}

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
	ResumeThread(this->handle);
}


int CppThread::start() {
	threadInit();
	return 0;
}




