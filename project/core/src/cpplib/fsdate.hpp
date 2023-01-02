#ifndef FSDATE_HPP
#define FSDATE_HPP

#include <string>

using namespace std;

enum DT_FORMAT 
{ 
	DATE,
	DATETIME,
	DATETIMEMS
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
	FsDate(const FsDate& obj);
	
	FsDate& operator=(const FsDate&);		   
	
	static string today(DT_FORMAT type);
	static string getDate(DT_FORMAT type);
	static string getDatems();
};

#endif // FSDATE_HPP