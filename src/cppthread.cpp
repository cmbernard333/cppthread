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
	threadit_safe_destroy(this->tid); 
	thread_handle_safe_destroy(this->handle);
}

/* TODO : pthread_create and CreateThread should start the thread in suspended mode
[ ] pthread_create ->
[X] create_thread -> CREATE_SUSPENDED
*/
int CppThread::threadInit() {
#if defined(LINUX) || defined(UNIX)
	int rc = pthread_create(this->tid, &this->attr, this->func, this->args);
	if(rc==0) {
		this->handle = this->tid;
	}
	return rc;
#elif defined (WINDOWS) || defined (WIN32) || defined (win32)
	/* first zero is stack-size which if set to 0 is now 1MB*/
	/* second zero is the creation flag which if set to 0 means the thread runs immediately*/
	*(this->handle) = CreateThread(this->attr, 0, this->func, this->args, CREATE_SUSPENDED, this->tid);
	return (*((this->handle))!=NULL ? 0 : 1);
#endif
}


int CppThread::start() {
	threadInit();
	return 0;
}
void CppThread::join() {
	Thread_Join(this->handle);
}


