#ifndef TEST_IMPL_HPP
#define TEST_IMPL_HPP

#include "fslog.hpp"
			
class TestImpl
{
private:
	FsLog log;
public:
	TestImpl();
	~TestImpl();
	TestImpl(const TestImpl& obj);
	TestImpl& operator=(const TestImpl& obj);
	
	void init();
	void run();
};

#endif // TEST_IMPL_HPP