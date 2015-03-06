#ifndef __CPP_THREAD_H__
#define __CPP_THREAD_H__
#if defined(LINUX) || defined(UNIX)
#include <pthread>
typedef pthread_t threadid_t;
typedef pthread_attr_t thread_attr_t;
typedef void* thread_args_t;
typedef int thread_handle_t;
// Thread_create(tid,attr,routine,arg) pthread_create(ref, attr, routine, arg)
// Thread_join() pthread_join()
#endif
#if defined(WINDOWS) || defined(WIN32) || defined (win32)
#include <windows.h>
#pragma once
typedef LPDWORD threadid_t;
typedef LPSECURITY_ATTRIBUTES thread_attr_t;
typedef LPVOID thread_args_t;
typedef HANDLE thread_handle_t;
// Thread_create(tid,attr,routine,arg) CreateThread(attr, stack, routine, arg, create_flags, id)
// Thread_join() WaitForSingleObject(handle,INFINITE)
#endif
typedef void (*threadfunc_t)(void *);

class CppThread {
        public:
                // constr
                explicit CppThread(threadfunc_t func, thread_args_t);
                void start();
                void join();
                virtual ~CppThread();
        private:
                threadid_t tid;
                threadfunc_t func;

}; 
#endif
