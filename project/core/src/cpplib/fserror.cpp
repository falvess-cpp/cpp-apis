/********************************************************************  
	@file       fserror.cpp
	@author     Fabiano Souza
	@brief      Implementation of FsError class.
	@history    1.0      Initial version 
	@date 		04-25-2022
***********************************************************************/
#include <string>

#include "fserror.hpp"

using namespace std;


FsError::FsError(ERROR_TYPE eType)
{ 
	switch(eType)
	{
		case SUCCESS : message = "SUCCESS"; break;
		case FILE_NOT_FOUND : message = "FILE_NOT_FOUND"; break;
		case UNKNOW_ERROR : message = "UNKNOW_ERROR"; break;
		case NULL_POINTER : message = "NULL_POINTER"; break;

	}
}	
	
FsError::~FsError() 
{ 
}  