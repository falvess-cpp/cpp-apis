#ifndef TEST_THREAD_IMPL_HPP
#define TEST_THREAD_IMPL_HPP

#include "fslog.hpp"
			
class TestThreadImpl
{
private:
	FsLog log;
public:
	TestThreadImpl();
	~TestThreadImpl();
	TestThreadImpl(const TestThreadImpl& obj);
	TestThreadImpl& operator=(const TestThreadImpl& obj);
	
	void init();
	void run();
};

#endif // TEST_THREAD_IMPL_HPP