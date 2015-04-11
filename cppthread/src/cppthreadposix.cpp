/*
 * cppthreadposix.cpp
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
	// thread_id_safe_destroy(this->tid); --> on posix id = handle
	thread_handle_safe_destroy(this->handle);
}

/* TODO : pthread_create and CreateThread should start the thread in suspended mode
[ ] pthread_create ->
*/
int CppThread::threadInit() {
	int rc = pthread_create(this->tid, &this->attr, this->func, this->args);
	if(rc==0) {
		this->handle = this->tid;
	}
	return rc;
}


int CppThread::start() {
	return threadInit();
}
int CppThread::join() {
	Thread_Join(*(this->handle),NULL);
}


