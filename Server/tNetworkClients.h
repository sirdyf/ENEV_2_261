#pragma once
#define WIN32_LEAN_AND_MEAN

#include "boost\smart_ptr.hpp"
#include "..\phisics\tobj.h"
#include "..\main\tMenu.h"
#include "..\main\tTransferdata.h"
//#include <D3dx8mesh.h>
//#ifndef _WINSOCK2API_
//#include <winsock2.h>
//#endif
//struct sockaddr;

class tNetworkClient{
public:
	tServiceInfo siFromClient;//для обмена с клиентом
	tServiceInfo siClient;//состояние клиента для самого сервера

	tStationMainInfo clientSMI;
	int iNumStar;//номер звезды в контейнере
	tMenu main;
	tMenu trade;
	tMenu newShip;
	tMenu equipment;//оборубование(компоненты) корабля
	tMenu inStation;
	float cash;
	int goods[100];
	int eqComp[30]; // Equipment components
	int iUinEngine;
	int iUinShip;
	char buf[256];
	bool used;
//	int iCountBetweenPacket;
	boost::intrusive_ptr< tObj > obj;//если никто не держит, кроме физ.двиг - объект уничтожиться
public:
	tNetworkClient(){
//		iCountBetweenPacket=0;
		used=false;
		cash=-100;
		iUinEngine=0;iUinShip=0;
		clientMode=0;
	}
	virtual ~tNetworkClient(void){}
};
//class tClient{
//public:
//	sockaddr clientAddr;
//	tClient(){
//		memset(&clientAddr,0,sizeof(clientAddr));
//	}
//	virtual ~tClient(){}
//};
