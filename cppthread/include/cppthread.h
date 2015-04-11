#ifndef __CPP_THREAD_H__
#define __CPP_THREAD_H__
#include <cstdlib>
#if defined(LINUX) || defined(UNIX)
#include <pthread.h>
// note: pthread_t on macosx is a struct while on linux it is an unsigned long
typedef pthread_t threadid_t;
typedef pthread_attr_t thread_attr_t;
typedef void* thread_args_t;
typedef void* (*threadfunc_t)(thread_args_t);
typedef pthread_t thread_handle_t;
#define Thread_Join(handle,pRetVal) pthread_join(handle,pRetVal)
/*TODO: this causes the thread exit but doesn't destroy the handle */
#define Thread_Close(handle) pthread_exit(nullptr)
#define thread_attr_init(attr) pthread_attr_init(attr) 
#endif

#if defined(WINDOWS) || defined(WIN32) || defined (win32)
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
typedef DWORD threadid_t;
typedef LPSECURITY_ATTRIBUTES thread_attr_t;
typedef LPVOID thread_args_t;
typedef HANDLE thread_handle_t;
typedef LPTHREAD_START_ROUTINE threadfunc_t;
/*TODO: thread joining is slightly different on windows because WaitForSingleObject returns the exit status while GetExitCodeThread actually gets the status*/
#define Thread_Join(handle,pRetVal) WaitForSingleObject(handle,INFINITE); GetExitCodeThread(handle,pRetVal)
/*TODO: this doesn't exit the thread it destroys the handle */
#define Thread_Close(handle) CloseHandle(handle)
#define thread_attr_init(attr) (LPSECURITY_ATTRIBUTES) malloc(SECURITY_DESCRIPTOR_MIN_LENGTH);
#endif

/* generalized aliases */
#define thread_id_init(id) id = (threadid_t*)malloc(sizeof(threadid_t))
#define thread_handle_init(handle) handle = (thread_handle_t*)malloc(sizeof(thread_handle_t))
#define threadit_safe_destroy(id) if(id) free(id)
#define thread_handle_safe_destroy(handle) if(handle) free(handle)


class CppThread {
        public:
                // constr
                CppThread(threadfunc_t func, thread_args_t args);
                CppThread(threadfunc_t func, thread_attr_t attr, thread_args_t args);
                int start();
                int join();
                virtual ~CppThread();
        private:
                threadid_t* tid; // on windows this is DWORD
                threadfunc_t func;
                thread_attr_t attr;
                thread_args_t args;
                thread_handle_t* handle; // on linux this is the same as the threadid_t field
                int threadInit();

}; 
#endif
