#pragma once
#include "..\phisics\tpointer.h"
#include "tINetStatistic.h"

class tINetworkClient :public tPointer{
public:
	boost::intrusive_ptr<tINetStatistic> _netStat;
	virtual int FormatDataForSend(char*)=0;
	virtual void ClientReciveData(const char* ,int)=0;
	void SetNetStatData(boost::intrusive_ptr<tINetStatistic> ns){
			this->_netStat=ns;
	}

	tINetworkClient(void){;}
	virtual ~tINetworkClient(void){;}
};
