/********************************************************************  
	@file       pthreadImpl.cpp
	@author     Fabiano Souza
	@brief      Implementation of pthreadImpl class.
	@history    1.0      Initial version 
	@date 		12-25-2022
***********************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <pthread.h>

#include "pthreadImpl.hpp"
#include "fslog.hpp"

TestPthreadImpl::TestPthreadImpl()
{
	init();
}

TestPthreadImpl::~TestPthreadImpl()
{
}

TestPthreadImpl::TestPthreadImpl(const TestPthreadImpl& obj)
{

}

TestPthreadImpl& TestPthreadImpl::operator=(const TestPthreadImpl& obj)
{
	return *this;
}
	
void TestPthreadImpl::init()
{
FUNC_ENTRY();
FUNC_TRY();
	log = FsLog();
FUNC_CATCH();
FUNC_EXIT();	
}

void *workThread(void *ThreadID_) {
    
    long ThreadID;
    ThreadID = (long)ThreadID_;
	FsLog log = FsLog();

	log.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, "[CHILD] Hello From Thread " + to_string(ThreadID));
    pthread_exit(NULL);
}

void TestPthreadImpl::run()
{
FUNC_ENTRY();
FUNC_TRY();
	log.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, "TEST PTHREAD API started!");
	int NumberThreads = 10;
	
    pthread_t Threads[NumberThreads];
    int rc;
    
    for (int i = 0; i < NumberThreads; i++) {
        
		log.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, "[ MAIN] Creating Thread: " + to_string(i));

        rc = pthread_create(&(Threads[i]), NULL, workThread, (void*)i);

        if (rc) {
			log.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, "[ MAIN] Failed To Create Thread With ID: " + to_string(i));			
            exit(-1); // throw exception
        }
    }
	
    for (int i = 0; i < NumberThreads; i++) {        
        rc = pthread_join(Threads[i], NULL);
		
        if (rc) {
			log.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, "Finishing Thread With ID: " + to_string(i));	
            exit(-1);
        }		
    }	

	log.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, "TEST PTHREAD API ended.");
	
	// Without This, Child Threads Would Be Terminated By The OS
    //pthread_exit(NULL);
	
FUNC_CATCH();
FUNC_EXIT();	
}