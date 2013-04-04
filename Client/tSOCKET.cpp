// tSOCKET.cpp: implementation of the tSOCKET class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
//#include "..\server\trees.h"
#include "tSOCKET.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tSOCKET::tSOCKET()
{	my_sock=NULL; }

tSOCKET::~tSOCKET()
{	my_sock=NULL; }

bool tSOCKET::Init()
{
// ��� 1 - ����������� ���������� 
	WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData))
    {
//      printf("WSAStartup error: %d\n",
//             WSAGetLastError());
      return false;
    }
    // ��� 2 - �������� ������
    // AF_INET     - ����� ���������
    // SOCK_STREAM  - ��������� ����� (�
    //      ���������� ����������)
    // 0      - �� ��������� ���������� TCP ��������
    if ((my_sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
      // ������!
//      printf("Error socket %d\n",WSAGetLastError());
        // �������������� ���������� Winsock
		WSACleanup();
		return false;
    }
	DWORD on=0;
	int err=ioctlsocket(my_sock,FIONBIO,&on);	// ������ ����� � ������������� �����
//	if (err) ASSERT(false);
return true;
}

void tSOCKET::Release()
{
	closesocket(my_sock);  // ��������� �����!
	WSACleanup();
}
