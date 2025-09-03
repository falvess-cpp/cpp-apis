#ifndef LOG_HPP
#define LOG_HPP

#include <string>
#include <unordered_map>
#include "fsexc.hpp"
#include "fsdate.hpp"

#define FUNC_ENTRY() \
	if (getenv("LOG_LEVEL") && std::string(getenv("LOG_LEVEL")) == "DEBUG") { \
		std::cout << FsDate().getDatems() << "---{ Enter '"  << __PRETTY_FUNCTION__ << "' (" << __FILE__ << "#" << __LINE__ << ")" << std::endl; \
	} 
	
#define FUNC_EXIT() \
	if (getenv("LOG_LEVEL") && std::string(getenv("LOG_LEVEL")) == "DEBUG") { \
	std::cout << FsDate().getDatems() << "---} Exit '"  << __FUNCTION__ << "' (" << __FILE__ << "#" << __LINE__ << ")" << std::endl; \
	} 

enum class LogType {
    Error = 0,
    Warn,
    Inform,
    Trace
};

enum class LogLevel {
    Debug = 0,
    Normal
};

class FsLog
{
private:
	bool debugModeOn;
public:
    static const std::string Debug;
    static const std::string Normal;
	
	std::unordered_map<std::string, std::string> configMap;
	
	FsLog();		
	~FsLog() = default;
	
	/** Loads the environment vars */
	void init();
	
	/** Loads sys configuration */
	void loadConfig(const std::string& path, const std::string& file);
	
	bool isDebugModeOn() const;
	LogLevel getLogLevel() const;
	
	/** log message */
	void logMessage(LogType logType, const std::string& fileName, unsigned long lineNumber, const std::string& message);
	
	static std::string getLogType(LogType logType);	
};

#endif // LOG_HPP 

