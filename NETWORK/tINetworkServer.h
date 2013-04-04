#pragma once
#include "..\phisics\tpointer.h"

class tINetworkServer :	public tPointer{
	
public:
	virtual bool ClientIsUsed(int )=0;
	virtual int NewClient()=0;
	virtual void ClientRecvData(int,char* buff,int sz)=0;

	//Здесь,в зависимости от состояния клиента, либо возвращаются персональные данные,
	//либо тупо быстро копируются данные для массовой рассылки.
	// заменено:
	// Любой клиент имеет персональные данные, поэтому ускорение будет только за счёт того,что
	// вместе с персональными данными будет передаваться массовая рассылка с ЗАРАНЕЕ подготовленными данными.
	virtual int GetData(int,char*)=0;

	virtual void PrepareData()=0;//Здесь подготавливаются данные для массовой рассылки

	tINetworkServer(void){};
	virtual ~tINetworkServer(void){};
};
