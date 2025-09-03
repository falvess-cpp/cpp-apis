#ifndef FSDATE_HPP
#define FSDATE_HPP

#include <string>

enum class DateFormat {
    Date,
    DateTime,
    DateTimeMs
};
				
class FsDate
{
private:
	int miYear;	// years [0,9999]
	int miMonth; // months [1,12]
	int miDay;   // day [1,31]
	int miHour;  // hours [0,23]
	int miMin;   // minutes [0,59]
	int miSec;   // seconds [0,59]
	int miMill;  // milliseconds [0,999]
	
public:
	FsDate();
	FsDate(unsigned int year, 
		   unsigned int month, 
		   unsigned int day, 
		   unsigned int hour, 
		   unsigned int min, 
		   unsigned int sec, 
		   unsigned int mill);	
	
    FsDate(const FsDate& obj) = default;
    FsDate& operator=(const FsDate& obj) = default;	   
	
    // Static methods for formatted date/time strings
    static std::string today(DateFormat format);
    static std::string getDate(DateFormat format);
    static std::string getDateWithMs();
};

#endif // FSDATE_HPP

