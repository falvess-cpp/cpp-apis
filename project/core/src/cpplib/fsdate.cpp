/********************************************************************  
	@file       fsdate.cpp
	@author     Fabiano Souza
	@brief      Implementation of FsDate class.
	@history    1.0      Initial version 
	@date 		04-25-2022
***********************************************************************/
#include "fsdate.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace {
    std::string formatCurrentDate(DateFormat format) {
        using namespace std::chrono;

        auto now = system_clock::now();
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

        std::time_t t = system_clock::to_time_t(now);
        std::tm local_tm = *std::localtime(&t);

        std::ostringstream oss;

        switch (format) {
            case DateFormat::Date:
                oss << std::put_time(&local_tm, "%Y/%m/%d");
                break;

            case DateFormat::DateTime:
                oss << std::put_time(&local_tm, "%Y/%m/%d %H:%M:%S");
                break;

            case DateFormat::DateTimeMs:
                oss << std::put_time(&local_tm, "%Y/%m/%d %H:%M:%S")
                    << '.' << std::setfill('0') << std::setw(3) << ms.count();
                break;
        }

        return oss.str();
    }
}

FsDate::FsDate() {
    using namespace std::chrono;

    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::time_t t = system_clock::to_time_t(now);
    std::tm local_tm = *std::localtime(&t);

    miYear  = local_tm.tm_year + 1900;
    miMonth = local_tm.tm_mon + 1;
    miDay   = local_tm.tm_mday;
    miHour  = local_tm.tm_hour;
    miMin   = local_tm.tm_min;
    miSec   = local_tm.tm_sec;
    miMill  = static_cast<int>(ms.count());
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
    if (month < 1 || month > 12)
        throw std::invalid_argument("Invalid month: must be between 1 and 12");

    if (day < 1 || day > 31)
        throw std::invalid_argument("Invalid day: must be between 1 and 31");

    if (hour > 23)
        throw std::invalid_argument("Invalid hour: must be between 0 and 23");

    if (min > 59)
        throw std::invalid_argument("Invalid minute: must be between 0 and 59");

    if (sec > 59)
        throw std::invalid_argument("Invalid second: must be between 0 and 59");

    if (mill > 999)
        throw std::invalid_argument("Invalid millisecond: must be between 0 and 999");
}

std::string FsDate::today(DateFormat format) {
    return formatCurrentDate(format);
}

std::string FsDate::getDate(DateFormat format) {
	return formatCurrentDate(format);
}

std::string FsDate::getDateWithMs() {
    using namespace std::chrono;

    // Get current time point
    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // Convert to time_t for formatting
    std::time_t t = system_clock::to_time_t(now);
    std::tm local_tm = *std::localtime(&t);

    // Format the date and time with milliseconds
    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%d/%m/%Y %H:%M:%S")
        << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}

