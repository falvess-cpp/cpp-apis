#ifndef FSEXCEPTION_HPP
#define FSEXCEPTION_HPP

#include <string>
#include <list>
#include <iostream>
#include <exception>

	
#define FUNC_TRY() try {

#define FUNC_CATCH() \
	} \
	catch (FsException &ex) { \
		ex.addToCallStack(FsExceptionLocation(__FILE__, __FUNCTION__, __LINE__)); \
		cout << ex.getErrorId() << " - " << ex.getErrorMessage() << endl;\
		ex.printCallStack(); \
		throw ex; \
	} \
	catch (const exception& ex) \
	{ \
		std::cout << "### Exception Ocurred ###" << std::endl; \
		std::cout << "Error: " << ex.what() << std::endl; \
		throw ex; \
	} \
	catch (...) { \
		cout << "Unknow Error - " << endl; \
		throw; \
	} \

using namespace std;

class FsExceptionLocation
{
private:
	string mFileName;
	string mMethodName;
	unsigned long mlLineNumber;
	
public:
	FsExceptionLocation(const string& fileName, const string& methodName, unsigned long lineNumber);
	
	FsExceptionLocation(const FsExceptionLocation& location);
	
	FsExceptionLocation();	
	
	~FsExceptionLocation();
	
	FsExceptionLocation& operator=(const FsExceptionLocation& location);	
	
	const string& getFileName() const;
	
	const string& getMethodName() const;
	
	unsigned long getLineNumber() const;
	
	string getLocation() const;	
};

class FsException : exception
{
private:
	unsigned long mlErrorId;
	string mErrorMsg;	
	list<FsExceptionLocation> mCallStack;
	list<string> strCallStack;
	
public:
	/**
	The usual constructor to instantiate an object of class FsException
	*/
	FsException(unsigned long errorId, const string& errorMsg);
	
	FsException(const FsException& exception);
	
	/** Default constructor */
	FsException();	
	
	/** assignment operator */
	FsException& operator=(const FsException& fsException);	
	
	~FsException();
		
	/** Gets the error ID */
	unsigned long getErrorId() const;	
	
	/** Gets the Error message */
	const string& getErrorMessage() const;	
	
    void printCallStack() const;

    string getCallStack() const;

    const list<FsExceptionLocation>*  getCallStackList() const;	
	
    void addToCallStack(const FsExceptionLocation& location);	
	
	string buildError() const;
};

#endif // FSEXCEPTION_HPP