#include "cppthread.h"
#include <iostream>

/**
	TODO can't have functions be different when using library
	Abstract this detail out
**/
#if defined (UNIX)
void* helloWorld(void* args) {
	std::cout<<"Hello, World!"<<std::endl;
}
#else if defined (WINDOWS)
DWORD WINAPI helloWorld (void* args) {
	std::cout << "Hello, World!" << std::endl;
	return 0;
}
#endif

int main(int argc, char** argv) {
	CppThread thread(helloWorld);
	thread.start();
	thread.join();
}
