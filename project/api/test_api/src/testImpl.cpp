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
#include "fslog.hpp"

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
FUNC_ENTRY();
FUNC_TRY();
	log = FsLog();
FUNC_CATCH();
FUNC_EXIT();	
}

void TestImpl::run()
{
FUNC_ENTRY();
FUNC_TRY();
	log.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, "TEST API started!");
	
	TestProcessor tp;
	tp.makeTest();

	log.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, "TEST API ended.");
FUNC_CATCH();
FUNC_EXIT();	
}