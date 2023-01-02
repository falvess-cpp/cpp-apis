#ifndef LOG_HPP
#define LOG_HPP

#include <string>
#include <list>
#include <unordered_map>

#include "fsexc.hpp"
#include "fsdate.hpp"

#define FUNC_ENTRY() \
	if (getenv("LOG_LEVEL") && string(getenv("LOG_LEVEL")) == "DEBUG") { \
		std::cout << FsDate().getDatems() << "---{ Enter '"  << __PRETTY_FUNCTION__ << "' (" << __FILE__ << "#" << __LINE__ << ")" << std::endl; \
	} 
	
#define FUNC_EXIT() \
	if (getenv("LOG_LEVEL") && string(getenv("LOG_LEVEL")) == "DEBUG") { \
	std::cout << FsDate().getDatems() << "---} Exit '"  << __FUNCTION__ << "' (" << __FILE__ << "#" << __LINE__ << ")" << std::endl; \
	} 
	
using namespace std;

enum LOG_TYPE 
{ 
	ERROR = 0,
	WARN = 1,
	INFORM = 2,
	TRACE = 3
};

enum LOG_LEVEL 
{ 
	DEBUG = 0,
	NORMAL = 1
};

class FsLog
{
private:
	bool debugModeOn;
public:
	static const string Debug;
	static const string Normal;	
	unordered_map<string, string> config_map;
	FsLog();		
	~FsLog();
	LOG_LEVEL getLogLevel();
	
	/** Loads the environment vars */
	void init();
	
	/** Loads sys configuration */
	void loadConfig(const string& path, const string& file);
	
	bool isDebugModeOn();
	
	/** log message */
	void logMessage(LOG_TYPE logType, const string& fileName, unsigned long lineNumber, const string& message);
	
	static string getLogType(LOG_TYPE eLogType);	
};

#endif // LOG_HPP 