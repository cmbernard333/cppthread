#include "cppthread.h"
#include <iostream>

void* helloWorld (void* args) {
    std::cout<<"Hello, World!"<<std::endl;
}

int main(int argc, char** argv) {
	CppThread thread(helloWorld,NULL);
	thread.start();
	thread.join();
}
