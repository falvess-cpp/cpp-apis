#ifndef TEST_PTHREAD_HPP
#define TEST_PTHREAD_HPP

#include "fslog.hpp"

class TestPthreadImpl
{
private:
	FsLog log;
public:
	TestPthreadImpl();
	~TestPthreadImpl();
	TestPthreadImpl(const TestPthreadImpl& obj);
	TestPthreadImpl& operator=(const TestPthreadImpl& obj);
	
	void init();
	void run();
};

#endif // TEST_PTHREAD_HPP