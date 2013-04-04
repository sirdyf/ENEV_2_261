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
// шаг 1 - подключение библиотеки 
	WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData))
    {
//      printf("WSAStartup error: %d\n",
//             WSAGetLastError());
      return false;
    }
    // Шаг 2 - создание сокета
    // AF_INET     - сокет Интернета
    // SOCK_STREAM  - потоковый сокет (с
    //      установкой соединения)
    // 0      - по умолчанию выбирается TCP протокол
    if ((my_sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
      // Ошибка!
//      printf("Error socket %d\n",WSAGetLastError());
        // Деиницилизация библиотеки Winsock
		WSACleanup();
		return false;
    }
	DWORD on=0;
	int err=ioctlsocket(my_sock,FIONBIO,&on);	// вводим сокет в неблокируемый режим
//	if (err) ASSERT(false);
return true;
}

void tSOCKET::Release()
{
	closesocket(my_sock);  // закрываем сокет!
	WSACleanup();
}
