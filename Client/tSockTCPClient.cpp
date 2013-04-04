// tSockTCPClient.cpp: implementation of the tSockTCPClient class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
//#include "..\server\trees.h"
#include "tSockTCPClient.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tSockTCPClient::tSockTCPClient()
{

}

tSockTCPClient::~tSockTCPClient()
{

}

bool tSockTCPClient::CreateSocket(int port,DWORD addr)
{
	Init();
	serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(port);
             // не забываем о сетевом порядке!!!
	serv_addr.sin_addr.s_addr=htonl(addr);//inet_addr("192.168.0.1")
             // сервер принимает подключения
             // на все IP-адреса
	return true;
}

bool tSockTCPClient::ConnectToServer()
{	
	if (connect(my_sock,(sockaddr *)&serv_addr,sizeof(serv_addr)))
	{	int a=WSAGetLastError();
		int b=0;
	//WSABASEERR=10000
		switch(a)
		{
		case WSANOTINITIALISED:
			b=1;
			break;
		case WSAENETDOWN:
			b=1;
			break;
		case WSAEADDRINUSE:
			b=1;
			break;
		case WSAEINTR:
			b=1;
			break;
		case WSAEINPROGRESS:
			b=1;
			break;
		case WSAEALREADY:
			b=1;
			break;
		case WSAEADDRNOTAVAIL:
			b=1;
			break;
		case WSAEAFNOSUPPORT:
			b=1;
			break;
		case WSAECONNREFUSED:
			b=1;
			break;
		case WSAEFAULT:
			b=1;
			break;
		case WSAEINVAL:
			b=1;
			break;
		case WSAEISCONN:
			b=1;
			break;
		case WSAENETUNREACH:
			b=1;
			break;
		case WSAENOBUFS:
			b=1;
			break;
		case WSAENOTSOCK:
			b=1;
			break;
		case WSAETIMEDOUT:
			b=1;
			break;
		case WSAEWOULDBLOCK:
			b=1;
			break;
		case WSAEACCES:
			b=1;
			break;
		default:
			b=1;
			break;
		}
		return false;
	}
	return true;
}
