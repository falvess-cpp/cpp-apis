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
#include <random>
#include <vector>
#include <chrono>

#include "threadImpl.hpp"
#include "fslog.hpp"

ThreadImpl::ThreadImpl()
{
	log_ = FsLog();
	
	randValues.reserve(size);
	std::mt19937 mt;
	mt.seed(45218965);
	for (long long i = 0 ; i < size ; ++i) 
      randValues.push_back(mt());
  
	std::stringstream ss;
	for (int i : randValues)
	ss << i << " ";
	log_.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, "Random numbers are " + ss.str()); 
	
	loadThreads(maxNumberOfThreads);
	log_.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, "Threads loaded");
}

ThreadImpl::~ThreadImpl()
{
	blockThread_.lock();
	exitThreads_ = true;
	blockThread_.unlock();
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	
    for (int i = 0; i < maxNumberOfThreads; i++) {
		log_.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, "Join to the Worker Thread " + std::to_string(i));
        if (workerThreads_[i].joinable())
			workerThreads_[i].join();
    }
}

void ThreadImpl::loadThreads(int &maxNumberOfThreads)
{
	log_.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, "Loading Worker Threads");
	
    if (maxNumberOfThreads == -1) {
		log_.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, "Identifying Number Of CPU Cores");
        maxNumberOfThreads = std::thread::hardware_concurrency();
		log_.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, "Identified " + std::to_string(maxNumberOfThreads) + " Cores");
    }
	log_.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, "Creating " + std::to_string(maxNumberOfThreads) + " Threads");
    for (int i = 0; i < maxNumberOfThreads; i++) {
		log_.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, "Creating Worker Thread " + std::to_string(i));
        workerThreads_.push_back(std::thread(&ThreadImpl::workerThread, this, i, 0));
		log_.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, "Worker Thread created");
    }
}

void ThreadImpl::workerThread(int workerThreadNumber, int sum)
{
	std::stringstream ss;
	ss << std::this_thread::get_id();	
	log_.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, " Running Thread number " + to_string(workerThreadNumber) + " with Thread ID " + ss.str());

    while (true) {
		sumLock_.lock();
		for (int i : randValues)
		 sum =+ i;
		sumLock_.unlock();
		 
		log_.logMessage(LOG_TYPE::INFORM, __FILE__, __LINE__, " Sum of randValues is " + to_string(sum) + " From Thread ID " + ss.str());
		 
        blockThread_.lock();
        if (exitThreads_) {
            blockThread_.unlock();
			break;
        } 
		 blockThread_.unlock();
		 
		
    }	
}
