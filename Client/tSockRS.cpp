// tSockRS.cpp: implementation of the tSockRS class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
//#include "trees.h"
#include "tSockRS.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tSockRS::tSockRS(){
	my_sock=0;
}

tSockRS::~tSockRS()
{

}
int tSockRS::Recv(char *const buff, UINT len)
{
	UINT n=0, recvd=0;
	while(n<len)
	{	recvd=recv(my_sock,&buff[0]+n,len-n,0);
		if (recvd<1)	return -1; // error
		//else if (recvd==0)	break; // socket will be closed
		n+=recvd;
	}
	return n;
}
void tSockRS::Send(const char *buff, UINT len)
{
	int n=0,sent=0;
	while(n<len)
	{	sent=send(my_sock,&buff[0]+n,len-n,0);
		if (sent<0)
		{	sent=WSAGetLastError();	//10057
			switch(sent)
			{
			case WSAENOTCONN:
				sent=0;
				break;
			default: break;
			}
			return;//client closed cocket?
		}
		n+=sent;
	}
}

