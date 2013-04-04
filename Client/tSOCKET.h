// tSOCKET.h: interface for the tSOCKET class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

//#include <winsock2.h>
#include"tSockRS.h"

class tSOCKET : public tSockRS 
{
public:
	tSOCKET();
	virtual ~tSOCKET();
	void Release();
protected:
	bool Init();
};
