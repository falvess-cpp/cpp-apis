#include "pthreadImpl.hpp"
#include "threadImpl.hpp"

int main() {
	TestThreadImpl().run();
	TestPthreadImpl().run();	
	return 0;
}