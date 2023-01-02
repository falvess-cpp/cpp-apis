#ifndef FSERROR_HPP
#define FSERROR_HPP

enum ERROR_TYPE 
{ 
	SUCCESS = 0,
	FILE_NOT_FOUND = 1000,
	NULL_POINTER = 1001,
	UNKNOW_ERROR = 1100
};

class FsError
{
private:
	string message;
	ERROR_TYPE errorType;
public:
	FsError(ERROR_TYPE eType);		
	~FsError();
};

#endif // FSERROR_HPP   