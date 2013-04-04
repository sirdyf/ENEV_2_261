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
	tServiceInfo siFromClient;//��� ������ � ��������
	tServiceInfo siClient;//��������� ������� ��� ������ �������

	tStationMainInfo clientSMI;
	int iNumStar;//����� ������ � ����������
	tMenu main;
	tMenu trade;
	tMenu newShip;
	tMenu equipment;//������������(����������) �������
	tMenu inStation;
	float cash;
	int goods[100];
	int eqComp[30]; // Equipment components
	int iUinEngine;
	int iUinShip;
	char buf[256];
	bool used;
//	int iCountBetweenPacket;
	boost::intrusive_ptr< tObj > obj;//���� ����� �� ������, ����� ���.���� - ������ ������������
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
