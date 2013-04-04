#pragma once

#define WIN32_LEAN_AND_MEAN

#pragma comment (lib, "ws2_32.lib")

#include <winsock2.h>

#include <iostream>

#include "boost\smart_ptr.hpp"
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
//#include "..\main\ttick.h"
#include "tINetworkClient.h"
#include "tnetinfo.h"
#include "tNetStatistic.h"
#include "..\client\logger.h"
class tNetworkClient{
	char cInterfaceServer[150];
	char cInterfaceClient[150];
	int iServerPort;
	int iClientPort;
	float timeSendPackets;//интервал между отправкой пакетов
	float timeSendToNAT;//время последней отсылки пакета через НАТ
	float timeWaitServer;//интервал между отправкой пакетов для обновления инфы на НАТе и регистрации на сервере
	float fUin;
	tTick tmr;
	boost::intrusive_ptr<tINetworkClient> _storage;
	volatile bool bWork;

	void WorkingWithUDPServerS();
	void WorkingWithUDPServerR();
	boost::shared_ptr<boost::thread> mThreadSend;
	boost::shared_ptr<boost::thread> mThreadRecv;
	int SendNetMessage(char* buf);
	void RecvNetMessage(char* buf,int len);
	int SendDataForNAT(char* buf);
	boost::intrusive_ptr<tNetStatistic> mNetStat;
public:

	void Init(boost::intrusive_ptr<tINetworkClient> _s);
	void Release();
	void Run();
	void Stop();
	void SetTimeBetweenPacketsSend(float mSec);

	tNetworkClient(void);
	virtual ~tNetworkClient(void);
};
