#include "cppthread.h"

CppThread::CppThread(threadfunc_t tFunc, thread_args_t tArgs) : func(tFunc), attr(nullptr), args(tArgs) {
	threadid_init(this->tid);
	thread_handle_init(this->handle);
}

CppThread::CppThread(threadfunc_t tFunc, thread_attr_t attrs, thread_args_t tArgs) : func(tFunc), attr(attrs), args(tArgs) {
	threadid_init(this->tid);
	thread_handle_init(this->handle);
}

CppThread::~CppThread() {
}

int CppThread::threadInit() {
#if defined(LINUX) || defined(UNIX)
	int rc = pthread_create(this->tid, &this->attr, this->func, this->args);
	if(rc==0) {
		this->handle = this->tid;
	}
	return rc;
#elif defined (WINDOWS) || defined (WIN32) || defined (win32)
	this->handle = CreateThread(this->attr, nullptr, this->func, this->args, nullptr, &this->tid)
	return ref!=nullptr ? 0 : 1;
#endif
}


int CppThread::start() {
	threadInit();
}
void CppThread::join() {
	Thread_Join(this->handle);
}


