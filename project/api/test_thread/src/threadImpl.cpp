/********************************************************************  
	@file       threadImpl.cpp
	@author     Fabiano Souza
	@brief      Implementation of threadImpl class.
	@history    1.0      Initial version 
	@date 		12-25-2022
***********************************************************************/

#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#include "threadImpl.hpp"
#include "fslog.hpp"

TestThreadImpl::TestThreadImpl()
{
	init();
}

TestThreadImpl::~TestThreadImpl()
{
}

TestThreadImpl::TestThreadImpl(const TestThreadImpl& obj)
{

}

TestThreadImpl& TestThreadImpl::operator=(const TestThreadImpl& obj)
{
	return *this;
}
	
void TestThreadImpl::init()
{
FUNC_ENTRY();
FUNC_TRY();
	log = FsLog();
FUNC_CATCH();
FUNC_EXIT();	
}

void workThread(int i) {
	std::stringstream ss;
	ss << std::this_thread::get_id();	
	FsLog log = FsLog();
	log.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, ss.str() + " [CHILD] Hello From Thread " + to_string(i));
}

void TestThreadImpl::run()
{
FUNC_ENTRY();
FUNC_TRY();
	log.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, "TEST THREAD API started!");
	int NumberThreads = 10;
	std::thread threads[NumberThreads];
	std::stringstream ss;
	ss << std::this_thread::get_id();
	
    // Create Threads
    for (int i = 0; i < NumberThreads; i++) { 
		log.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, ss.str() + " [ MAIN] Creating Thread: " + to_string(i));    
		threads[i] = std::thread(workThread, i); 
    }

    for (int i = 0; i < NumberThreads; i++) {        
		threads[i].join();
    }
	
	log.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, "TEST THREAD API ended.");
FUNC_CATCH();
FUNC_EXIT();	
}