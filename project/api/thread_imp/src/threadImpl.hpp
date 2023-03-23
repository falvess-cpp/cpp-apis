#ifndef THREAD_IMPL_HPP
#define THREAD_IMPL_HPP

#include <thread>
#include <vector>
#include <mutex>

#include "fslog.hpp"
			
class ThreadImpl
{
private:
	FsLog log_; /**<Application logs*/
	std::vector<std::thread> workerThreads_; /**<List of worker threads*/
	std::vector<int> randValues; /**<Random values*/
	std::mutex blockThread_; /**<Block Threads*/
	std::mutex sumLock_; /**<Lock sum variable*/
	bool exitThreads_ = false; /**<Set To True To terminate Threads*/
	const long size = 5; 
	int maxNumberOfThreads = -1;
public:
	ThreadImpl();
	~ThreadImpl();
	void loadThreads(int &maxNumberOfThreads);
	void workerThread(int workerThreadNumber, int sum = 0);	
};

#endif // THREAD_IMPL_HPP