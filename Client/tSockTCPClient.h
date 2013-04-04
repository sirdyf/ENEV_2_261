// tSockTCPClient.h: interface for the tSockTCPClient class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

//#include <WINSOCK2.H>
#include"tSOCKET.h"
class tSockTCPClient: public tSOCKET
{
public:
	bool ConnectToServer();
	bool CreateSocket(int port,DWORD addr);
	tSockTCPClient();
	virtual ~tSockTCPClient();
protected:
	sockaddr_in serv_addr;

};

