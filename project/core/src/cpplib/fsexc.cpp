/********************************************************************  
	@file       AppException.cpp
	@author     Fabiano Souza
	@brief      Implementation of AppException class.
	@history    1.0      Initial version 
	@date 		04-25-2022
***********************************************************************/

#include <string>
#include <list>
#include <iostream>
#include <sstream>

#include "fsexc.hpp"

using namespace std;

FsExceptionLocation::FsExceptionLocation(const string& fileName, const string& methodName, unsigned long lineNumber)
	: mFileName(fileName), mMethodName(methodName), mlLineNumber(lineNumber)
{
}
	
FsExceptionLocation::FsExceptionLocation(const FsExceptionLocation& location) : mlLineNumber(0)
{	
	*this = location;	
}
	
FsExceptionLocation::FsExceptionLocation() : mlLineNumber(0)
{ 
}	
	
FsExceptionLocation::~FsExceptionLocation() 
{ 
}
	
FsExceptionLocation& FsExceptionLocation::operator=(const FsExceptionLocation& location)
{
	if (this != &location)
	{
		mFileName = location.mFileName;
		mMethodName = location.mMethodName;
		mlLineNumber = location.mlLineNumber;
	}
	
	return *this;	
}
	
const string& FsExceptionLocation::getFileName() const
{
	return mFileName;
}
	
const string& FsExceptionLocation::getMethodName() const
{
	return mMethodName;
}
	
unsigned long FsExceptionLocation::getLineNumber() const
{
	return mlLineNumber;
}
	
string FsExceptionLocation::getLocation() const
{
	string loc = "File: " + getFileName() + "  Function: " + getMethodName() + "  Line: " + to_string(getLineNumber());
	return (loc);	
}
	
FsException::FsException(unsigned long errorId, const string& errorMsg)
	: mlErrorId(errorId), mErrorMsg(errorMsg)
{
}

FsException::FsException(const FsException& exception) : mlErrorId(0)
{
		*this = exception;
}

FsException::FsException() : mlErrorId(0)
{
}

FsException& FsException::operator=(const FsException& fsException)
{
	if (this != &fsException)
	{
		mlErrorId = fsException.mlErrorId;
		mErrorMsg = fsException.mErrorMsg;
	}
	
	return *this;
}

FsException::~FsException() 
{ 	
}

unsigned long FsException::getErrorId() const
{
	return mlErrorId;
}

const string& FsException::getErrorMessage() const
{
	return mErrorMsg;
}	
	
void FsException::printCallStack() const
{
    for (list<FsExceptionLocation>::const_iterator iter = mCallStack.begin(); iter != mCallStack.end(); iter++)
    {
        cout << "File: " << (*iter).getFileName() << " Method: " << (*iter).getMethodName() << " Line: " << (*iter).getLineNumber() << endl;
    }
}

string FsException::getCallStack() const
{
    ostringstream callStackStream;
	int cnt = 0;
    for (list<FsExceptionLocation>::const_iterator iter = mCallStack.begin(); iter != mCallStack.end(); iter++)
    {
        if ( mCallStack.begin() != iter )
        {
            callStackStream << endl;
        }
			
        callStackStream << "(" << ++cnt << ".) " << (*iter).getFileName() << " " << (*iter).getMethodName() << " " << (*iter).getLineNumber();
    }

    return callStackStream.str();	
}

const list<FsExceptionLocation>* FsException::getCallStackList() const
{
	return &mCallStack;
}

void FsException::addToCallStack(const FsExceptionLocation& location)
{
    mCallStack.push_front(location);	
}

string FsException::buildError() const
{
    stringstream outputStream;
	
	outputStream << "-- Exception Ocurred -- " << endl;
	outputStream << "Error ID: ";
	if (getErrorId() == 0)
		outputStream << "none";
	else 
		outputStream << getErrorId() << " - " << getErrorMessage();
	outputStream << endl;
	
	string rc(outputStream.str());
    return rc;	
}

