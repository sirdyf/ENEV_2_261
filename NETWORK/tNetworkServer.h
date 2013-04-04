#pragma once
#define WIN32_LEAN_AND_MEAN

#pragma comment (lib, "ws2_32.lib")

#include <winsock2.h>
#include <iostream>

#include "boost\smart_ptr.hpp"
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>

#include "tNetInfo.h"
#include "tINetworkServer.h"
#include "..\phisics\tpointer.h"
#include "..\main\ttick.h"
#include "..\server\logger.h"

class tNetworkServer{
	int _index;
	int _szNetInfo;
	int _szSAddr;
	int _timeSleep;
	int _serverPort;
	int _clientPort;
	volatile bool bWork;
	tTick _tick;
	boost::intrusive_ptr<tINetworkServer> _storage;
	boost::shared_ptr<boost::thread> _threadSend;
	boost::shared_ptr<boost::thread> _threadRecv;
	boost::mutex _mutex;
	char _interface[150];
	struct {
		tNetInfo mInfo;
		sockaddr clientAddrForRecv;//адрес на который клиент желает получать пакеты
//		sockaddr clientAddrForSend;//адрес с которого клиент шлёт пакеты
		bool used;
		int uinGM;
	} _clients[5];

	bool CheckEchoClient(sockaddr clAddr,tNetInfo info);
	void ClientRecvData(sockaddr,char*,int);
	void WorkingWithUDPClient();
	void SexToUDPClient();
	bool GetNetworkMessage(char* , int*);
public:
	bool Init(boost::intrusive_ptr<tINetworkServer> _s);
	void Run();
	void Stop();
	void Destroy();
	void SetSendTimeInterval(int );

	tNetworkServer();
	virtual ~tNetworkServer(void);
};
