/********************************************************************  
	@file       testImpl.cpp
	@author     Fabiano Souza
	@brief      Implementation of testImpl class.
	@history    1.0      Initial version 
	@date 		12-25-2022
***********************************************************************/

#include <iostream>
#include <string>

#include "testImpl.hpp"
#include "testProcessor.hpp"
#include "fslogging.hpp"

TestImpl::TestImpl()
{
	init();
}

TestImpl::~TestImpl()
{
}

TestImpl::TestImpl(const TestImpl& obj)
{

}

TestImpl& TestImpl::operator=(const TestImpl& obj)
{
	return *this;
}
	
void TestImpl::init()
{
LOG_FUNC_ENTRY();
	LOG_INFO("log info message test");
LOG_FUNC_EXIT();
}

void TestImpl::run()
{
LOG_FUNC_ENTRY();
LOG_WARN("API started");
	TestProcessor tp;
	tp.makeTest();
LOG_WARN("API ended");	
LOG_FUNC_EXIT();
}