#include "cppthread.h"

CppThread::CppThread(threadfunc_t tFunc, thread_args_t tArgs) : func(tFunc), args(tArgs) {}

void CppThread::start() {
        // posix
        int rc = pthread_create(&this->threadid_t,null,this->func,this->args);
        // windows
}
void CppThread::join() {
}
CppThread::~CppThread() {
}

