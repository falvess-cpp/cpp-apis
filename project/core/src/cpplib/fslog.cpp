/********************************************************************  
	@file       fslog.cpp
	@author     Fabiano Souza
	@brief      Implementation of FsLog class.
	@history    1.0      Initial version 
	@date 		04-25-2022
***********************************************************************/
#include <string>
#include <list>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h> 
#include <unordered_map>

#include "fslog.hpp"
#include "fserror.hpp"

using namespace std;

const string FsLog::Debug = "DEBUG";
const string FsLog::Normal = "NORMAL";

FsLog::FsLog()
{ 
	init();
}	
	
FsLog::~FsLog() 
{ 
}

void FsLog::init()
{
	if (getenv("LOG_LEVEL") && string(getenv("LOG_LEVEL")) == "DEBUG")
	{
		debugModeOn = true;
	}
	else
	{
		debugModeOn = false;
	}
	
	if (getenv("CONFIG_PATH") && getenv("CONFIG_FILE"))
	{
		string npath = getenv("CONFIG_PATH");
		string nfile = getenv("CONFIG_FILE");
		loadConfig(npath, nfile);
	}
	else
	{
		if (!getenv("CONFIG_PATH"))
		{
			logMessage(LOG_TYPE::WARN, __FILE__, __LINE__, "Environment var CONFIG_PATH not set");
		}
		
		if (!getenv("CONFIG_FILE"))
		{
			logMessage(LOG_TYPE::WARN, __FILE__, __LINE__, "Environment var CONFIG_PATH not set");
		}	
	}
}

void FsLog::loadConfig(const string& path, const string& file)
{
	string filename = path + "/" + file;
	ifstream filestream;
	filestream.open(filename);
	if (filestream.is_open())
	{
		string line;
		while (getline(filestream, line))
		{
			if (line[0] == '#' || line.empty())
				continue;
			auto pos = line.find(":");
			auto name = line.substr(0, pos);
			auto value = line.substr(pos + 1);
			config_map[name] = value;	
		}
		filestream.close();
	}
	else
	{
		logMessage(LOG_TYPE::WARN, __FILE__, __LINE__, "Unable to open file " + file);
		//throw FsException(ERROR_TYPE::FILE_NOT_FOUND, "unable to open file " + file);
	}	
}

bool FsLog::isDebugModeOn()
{
	return debugModeOn;
}

LOG_LEVEL FsLog::getLogLevel()
{
	if (getenv("LOG_LEVEL") && string(getenv("LOG_LEVEL")) == "DEBUG")
	{
		return LOG_LEVEL::DEBUG;
	}
	else
	{
		return LOG_LEVEL::NORMAL;
	}
	
	//unordered_map<string,string>::const_iterator it = config_map.find("LOG_LEVEL");
	//if (it != config_map.end() && it->second == FsLog::Debug)
		//return LOG_LEVEL::DEBUG;
	//else
		//return LOG_LEVEL::NORMAL;	
}

string FsLog::getLogType(LOG_TYPE eLogType)
{ 
	switch(eLogType)
	{
		case ERROR : return "ERROR-----";
		case WARN : return "WARN-----";
		case INFORM : return "INFORM-----";
		case TRACE : return "TRACE-----";

	}
}

void FsLog::logMessage(LOG_TYPE logType, const string& fileName, unsigned long lineNumber, const string& message)
{	
	if (isDebugModeOn()) 
	{
		cout << getLogType(logType) << fileName << "#" << lineNumber << " " << FsDate().getDatems() << " " << message << endl;
	}
	else if (logType != LOG_TYPE::TRACE)
	{
		cout << getLogType(logType) << fileName << "#" << lineNumber << " " << FsDate().getDatems() << " " << message << endl;
	}	
}
