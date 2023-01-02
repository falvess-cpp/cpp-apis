/********************************************************************  
	@file       fsdate.cpp
	@author     Fabiano Souza
	@brief      Implementation of FsDate class.
	@history    1.0      Initial version 
	@date 		04-25-2022
***********************************************************************/
#include <sys/timeb.h>
#include <string>
#include <ctime>
#include <iostream>
#include <chrono>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#include "fsdate.hpp"
#include "fsexc.hpp"

using namespace std;

FsDate::FsDate()
{
	auto d = std::chrono::system_clock::now();
	time_t t = std::chrono::system_clock::to_time_t(d);
    tm dt = *localtime(&t);
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(d.time_since_epoch()) % 1000;
	 
	miYear = dt.tm_year + 1900;
	miMonth = dt.tm_mon + 1;
	miDay = dt.tm_mday;
	miHour = dt.tm_hour;
	miMin = dt.tm_min;
	miSec = dt.tm_sec;
	miMill = ms.count();
}


FsDate::FsDate(unsigned int year, 
			unsigned int month, 
			unsigned int day, 
			unsigned int hour, 
			unsigned int min, 
			unsigned int sec, 
			unsigned int mill) 
			: miYear(year)
			, miMonth(month)
			, miDay(day)
			, miHour(hour)
			, miMin(min)
			, miSec(sec)
			, miMill(mill)
{
}
			
FsDate::FsDate(const FsDate& obj)
{
	miYear = obj.miYear;
	miMonth = obj.miMonth;
	miDay = obj.miDay;
	miHour = obj.miHour;
	miMin = obj.miMin;
	miSec = obj.miSec;
	miMill = obj.miMill;
}

FsDate& FsDate::operator=(const FsDate& obj)
{
	miYear = obj.miYear;
	miMonth = obj.miMonth;
	miDay = obj.miDay;
	miHour = obj.miHour;
	miMin = obj.miMin;
	miSec = obj.miSec;
	miMill = obj.miMill;
	return *this;
}

string FsDate::today(DT_FORMAT type)
{
	FUNC_TRY();
	
	char * str = new char[50 + 1];
	time_t ltime;
	struct tm* today;
	string mi = "";

    struct timeb now;

    ftime( &now );

	time(&ltime);
	today = localtime(&ltime);
	
	switch(type)
	{
		case DATE:
			strftime(str, 50, "%Y/%m/%d", today);
			break;
			
		case DATETIME:
			strftime(str, 50, "%Y/%m/%d %H:%M:%S", today);
			break;	

		case DATETIMEMS:
			strftime(str, 50, "%Y/%m/%d %H:%M:%S", today);
			mi = "." + to_string(now.millitm);
			break;				
	}
	
    string dtStr(str);
    return dtStr + mi;	
	
	FUNC_CATCH();
}

string FsDate::getDate(DT_FORMAT type)
{
	FsDate date;
	stringstream sstm;
	
	switch(type)
	{
		case DATE:
			sstm << (date.miYear) << '/' << (date.miMonth) << '/' << (date.miDay);
			break;
			
		case DATETIME:
			sstm << (date.miYear) << '/' << (date.miMonth) << '/' << (date.miDay) << ' ';
			sstm << (date.miHour) << ':' << (date.miMin) << ':' << (date.miSec);
			break;

		case DATETIMEMS:
			sstm << (date.miYear) << '/' << (date.miMonth) << '/' << (date.miDay) << ' ';
			sstm << (date.miHour) << ':' << (date.miMin) << ':' << (date.miSec) << ':' << (date.miMill);
			break;			
	}

    string dtStr = sstm.str();
    return dtStr;	
}

string FsDate::getDatems() {
	char * str = new char[50 + 1];
	struct tm *today;
	struct timeval now;
	gettimeofday(&now, NULL);
	time_t t = now.tv_sec;
	today = localtime (&t);

    (void)sprintf(str,
                  "%02d/%02d/%4d %02d:%02d:%02d.%03d",
                  today->tm_mday,
                  today->tm_mon + 1,
                  (today->tm_year + 1900),
                  today->tm_hour,
                  today->tm_min,
                  today->tm_sec,
				  (int) (now.tv_usec/1000));
				  
	 string dtStr(str);
    return dtStr;	
}