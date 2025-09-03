/********************************************************************  
	@file       fslog.cpp
	@author     Fabiano Souza
	@brief      Implementation of FsLog class.
	@history    1.0      Initial version 
	@date 		04-25-2022
***********************************************************************/
#include "fslog.hpp"
#include <fstream>
#include <sstream>

const std::string FsLog::Debug = "DEBUG";
const std::string FsLog::Normal = "NORMAL";

FsLog::FsLog() {
    init();
}

void FsLog::init() {
    const char* logLevelEnv = std::getenv("LOG_LEVEL");
    debugModeOn = (logLevelEnv && std::string(logLevelEnv) == "DEBUG");

    const char* configPath = std::getenv("CONFIG_PATH");
    const char* configFile = std::getenv("CONFIG_FILE");

    if (configPath && configFile) {
        loadConfig(configPath, configFile);
    } else {
        if (!configPath) {
            logMessage(LogType::Warn, __FILE__, __LINE__, "Environment var CONFIG_PATH not set");
        }
        if (!configFile) {
            logMessage(LogType::Warn, __FILE__, __LINE__, "Environment var CONFIG_FILE not set");
        }
    }
}

void FsLog::loadConfig(const std::string& path, const std::string& file) {
	
    std::ifstream filestream(path + "/" + file);
    if (!filestream.is_open()) {
        logMessage(LogType::Warn, __FILE__, __LINE__, "Unable to open file " + file);
        return;
    }

    std::string line;
    while (std::getline(filestream, line)) {
        if (line.empty() || line[0] == '#') continue;

        auto pos = line.find(':');
        if (pos == std::string::npos) continue;

        std::string name = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        configMap[name] = value;
    }
}

bool FsLog::isDebugModeOn() const {
    return debugModeOn;
}

LogLevel FsLog::getLogLevel() const {
    const char* logLevelEnv = std::getenv("LOG_LEVEL");
    return (logLevelEnv && std::string(logLevelEnv) == "DEBUG") ? LogLevel::Debug : LogLevel::Normal;
}

std::string FsLog::getLogType(LogType logType) {
    switch (logType) {
        case LogType::Error:  return "ERROR-----";
        case LogType::Warn:   return "WARN------";
        case LogType::Inform: return "INFORM----";
        case LogType::Trace:  return "TRACE-----";
        default:              return "UNKNOWN---";
    }
}

void FsLog::logMessage(LogType logType, const std::string& fileName, unsigned long lineNumber, const std::string& message) {
    if (isDebugModeOn() || logType != LogType::Trace) {
        std::cout << getLogType(logType) << " "
                  << fileName << "#" << lineNumber << " "
                  << FsDate::getDateWithMs() << " "
                  << message << std::endl;
    }
}

