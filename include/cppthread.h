#ifndef __CPP_THREAD_H__
#define __CPP_THREAD_H__
#if defined(LINUX) || defined(UNIX)
#include <pthread.h>
// note: pthread_t on macosx is a struct while on linux it is an unsigned long
typedef pthread_t threadid_t;
typedef pthread_attr_t thread_attr_t;
typedef void* thread_args_t;
typedef pthread_t thread_handle_t;
typedef void* (*threadfunc_t)(thread_args_t);
/*TODO: joining requires an argument for the output unlike windows*/
#define Thread_Join(handle) pthread_join(handle)
/*TODO: this causes the thread exit but doesn't destroy the handle */
#define Thread_Close(handle) pthread_exit(nullptr)
#endif
#if defined(WINDOWS) || defined(WIN32) || defined (win32)
#include <windows.h>
#pragma once
typedef DWORD threadid_t;
typedef LPSECURITY_ATTRIBUTES thread_attr_t;
typedef LPVOID thread_args_t;
typedef HANDLE thread_handle_t;
typedef LPTHREAD_START_ROUTINE threadfunc_t;
/*TODO: thread joining is slightly different on windows because WaitForSingleObject returns the exit status while GetExitCodeThread actually gets the status*/
#define Thread_Join(handle) WaitForSingleObject(handle,INFINITE); GetExitCodeThread(handle,NULL)
/*TODO: this doesn't exit the thread it destroys the handle */
#define Thread_Close(handle) CloseHandle(handle)
#endif

/* generalized aliases */
#define threadid_init(id) id = (threadid_t*)malloc(sizeof(threadid_t))
#define thread_handle_init(handle) handle = (thread_handle_t*)malloc(sizeof(thread_handle_t))
#define threadit_safe_destroy(id) if(id) free(id)
#define thread_handle_safe_destroy(handle) if(handle) free(handle)


class CppThread {
        public:
                // constr
                CppThread(threadfunc_t func, thread_args_t args);
                CppThread(threadfunc_t func, thread_attr_t attr, thread_args_t args);
                int start();
                void join();
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
