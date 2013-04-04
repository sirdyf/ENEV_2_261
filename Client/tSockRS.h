// tSockRS.h: interface for the tSockRS class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <WINSOCK2.H>

class tSockRS  
{
public:
	tSockRS();
	virtual ~tSockRS();
	void Send(const char *buff, UINT len);
//	int Recv(char* const buff);
	int Recv(char* const buff, UINT len);
//protected:
	SOCKET my_sock;
};
