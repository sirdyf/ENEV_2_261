
#include "tNetworkClient.h"

//-----------------------------------------------------------------------------
//а)с порта клиента "аа"(5657) возможно:
//	а.1)посылка на порт "bb"(5656) сервера инфы о том, что клиент ждёт инфу на этот порт и для обновления данных на НАТ сервере
//	а.2)приём от сервера с порта "yy"(случайный) инфы в рабочем режиме
//б)с порта клиента "xx"(случайный) возможно:
//	б.1)посылка самому себе на порт "аа" с целью разблокировать принимающий поток
//	б.2)посылка серверу на порт "bb" инфы в рабочем режиме
//-----------------------------------------------------------------------------
//#define test_console //---

tNetworkClient::tNetworkClient(void){
	bWork=false;
	timeSendPackets=500;//интервал между отправкой пакетов
	timeSendToNAT=0;//время последней отсылки пакета через НАТ
	timeWaitServer=3000;//интервал между отправкой пакетов для обновления инфы на НАТе и регистрации на сервере
//	mThreadSend=0;
//	mThreadRecv=0;
	fUin=0;
}

tNetworkClient::~tNetworkClient(void){}

void tNetworkClient::Init(boost::intrusive_ptr<tINetworkClient> _s){
	if (!_s) {
		LOG_ERROR << "tINetworkClient - NULL";
		return;
	}
	this->_storage=_s;
	mNetStat=boost::intrusive_ptr<tNetStatistic> (new tNetStatistic);
	_s->SetNetStatData(this->mNetStat);
	char cc[100];
	::GetCurrentDirectoryA(100,cc);
	strcat(cc,"\\config.ini");
	DWORD res=GetPrivateProfileStringA("Network", "interfaceServer", "127.0.0.1", cInterfaceServer, 100, cc);
// для теста сажаем на один интерфейс, т.к. в случае отправки пакета на сервер 172,16,0,30 система
// автоматом выбирает этот же(!) интерфейс для отправки,поэтому клиент не получит пакет забиндившись на другом(!) интерфейсе
	res=GetPrivateProfileStringA("Network", "interfaceClient", "127.0.0.1", cInterfaceClient, 100, cc);
	
	iServerPort=5656;
	iClientPort=5657;
	LOG_DEBUG << cc << "\nServer:" << cInterfaceServer << iServerPort<< "\nClient:"<<cInterfaceClient<<iClientPort;

	this->mNetStat->clientIP=cInterfaceClient;//+std::string(iClientPort);
	this->mNetStat->serverIP=cInterfaceServer;//+std::string(iServerPort);

	WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData)){
		LOG_ERROR << "WSAStartup error: " << WSAGetLastError() ;
    }
}
void tNetworkClient::Release(){
	LOG_WARNING << "WSACleanup()!";
	WSACleanup();
}
void tNetworkClient::Run(){
	assert(!mThreadSend);
	assert(!mThreadRecv);
	this->bWork=true;
	LOG_DEBUG << "Starting threads...\n";
	mThreadRecv=boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&tNetworkClient::WorkingWithUDPServerR,this)));//приём
	mThreadSend=boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&tNetworkClient::WorkingWithUDPServerS,this)));//передача

	LOG_DEBUG << "...thread starting end.\n\tThread1-" << mThreadRecv << " Thread2-" << mThreadSend ;

}
void tNetworkClient::Stop(){
	assert(mThreadSend);
	assert(mThreadRecv);
	this->bWork=false;
	LOG_DEBUG << "Wait threads end..";
	mThreadSend->join();
	mThreadRecv->join();
	LOG_DEBUG << "..thread ended";
}
//Как определить окончание работы потока? this->mThreadRecv!=0 даже после выполнения return;
//проверить все выходы из потока и сделать bWork=false и вывести сообщение в лог!

void tNetworkClient::WorkingWithUDPServerS(){
	float tmpTime=0;
	int rc=0;
    SOCKADDR_IN        saddr;
	SOCKET clSocketS=0;
	::Sleep(100);
	// Создаем сокет сервера для работы с потоком данных (AF_INET, SOCK_DGRAM, IPPROTO_UDP)
	clSocketS  = socket(AF_INET , SOCK_DGRAM, IPPROTO_UDP);
	if(clSocketS  == INVALID_SOCKET){
		LOG_ERROR << "_send_ Socket Error!!";
		this->bWork=false;
		return ;
	}
	char buf[1024]={0};

	LOG_DEBUG << "Thread _send_ "<< "Server IP-" << cInterfaceServer << "port:" << iServerPort;

	int sz=sizeof(SOCKADDR_IN);//sizeof(sockaddr);
    ZeroMemory(&saddr, sz);
	saddr.sin_addr.s_addr = inet_addr(cInterfaceServer);//inet_addr("172.16.0.30");//inet_addr ("10.71.21.1");//htonl(INADDR_LOOPBACK);
    saddr.sin_family = AF_INET;
	saddr.sin_port = htons(this->iServerPort);
	tTick tm;
	tm.Init(this->timeSendPackets);
	LOG_DEBUG << "thread _send_ main loop started, time sleep=" << this->timeSendPackets;
	while(this->bWork){
		if (this->fUin!=0){//ждём регистрации на сервере
			// подготавливаем данные к отправке
			LOG_DEBUG_LEV(1) << "_send_ tNetworkClient::SendNetMessage()";
			rc=this->SendNetMessage(&buf[0]);
			LOG_DEBUG_LEV(1) << "_send_ data send to"<<inet_ntoa(saddr.sin_addr) << " port:" << ntohs(saddr.sin_port);
			rc=sendto(clSocketS , buf, rc, 0,(LPSOCKADDR)&saddr, sz);
			if (rc==-1) {
				int res=GetLastError();
				LOG_ERROR << "_send_ error:" << res;
				this->bWork=false;
				break;
			}
	//		World.dObjList2=World.tick.GetTime();
	//		_slpTime=World.GetTimeSleepNetwork();
		}
		tm.Wait();
		tmpTime=tm.GetTime();
		if (tmpTime-this->timeSendToNAT>this->timeWaitServer*1.5f){//прошло больше X сек
			//ошибка отправки-принимающий поток завис- данные не доходят!
			LOG_WARNING << "thread _send_ timeSendToNAT >" << this->timeWaitServer*1.5f<< " (*1.5)sec!";
			this->timeSendToNAT=tmpTime;
			if (this->mThreadRecv){//разблокируем:
				//cout << "Unlock _recv_ thread...\n";
				SOCKADDR_IN tmpAddr;
				tmpAddr.sin_family = AF_INET ;
				tmpAddr.sin_addr.s_addr = inet_addr(this->cInterfaceClient);
				tmpAddr.sin_port = htons(this->iClientPort);
				LOG_WARNING << "Try unlock recv thread-send 0 byte..";// loopback msg
				sendto(clSocketS,"",0,0,(LPSOCKADDR) &tmpAddr, sz);//заменить на эхо запрос!!
			}else{
				this->bWork=false;// ошибка! принимающего потока нет - Завершаем работу!
				LOG_WARNING << "bad recv thread! thread _send_ closing...";
			}
		}
	}
	SOCKADDR_IN tmpAddr;
	tmpAddr.sin_family = AF_INET ;
	tmpAddr.sin_addr.s_addr = inet_addr(this->cInterfaceClient);
	tmpAddr.sin_port = htons(this->iClientPort);

	::Sleep(300);
	LOG_WARNING << "Try unlock recv thread-send 0 byte..";// loopback msg
	sendto(clSocketS,"",0,0,(LPSOCKADDR) &tmpAddr, sz);//заменить на эхо запрос!!
	::Sleep(2000);

	int error = closesocket (clSocketS);				// закрываем сокет
	if (error == SOCKET_ERROR){
		LOG_ERROR << "_send_ close socket error";
		return ;
	}
	LOG_DEBUG << "_send_ thread end.";
	return ;
}
void tNetworkClient::WorkingWithUDPServerR(){
	Sleep(100);
	int rc=0;
	char szTemp[1024]={7,8,9,0};
	SOCKET clSocketR=0;
	SOCKADDR_IN client;//={AF_INET,INADDR_ANY,INADDR_ANY};
//-----------------------
	// Создаем сокет сервера для работы с потоком данных
	clSocketR  = socket(AF_INET , SOCK_DGRAM, IPPROTO_UDP);
	if(clSocketR  == INVALID_SOCKET){
		LOG_ERROR << "_send_ Create socket error";
		return ;
	}

	int sz=sizeof(SOCKADDR_IN);//sizeof(sockaddr);
    ZeroMemory(&client, sz);
	// Устанавливаем адрес IP и номер порта
	client.sin_family = AF_INET ;
	client.sin_addr.s_addr = inet_addr(this->cInterfaceClient);//inet_addr ("172.16.0.30");//inet_addr ("127.0.0.1");//inet_addr("10.71.21.1");// htonl(INADDR_ANY);//
	client.sin_port = htons(this->iClientPort);

	// Связываем адрес IP с сокетом  
	if(bind (clSocketR , (LPSOCKADDR   )&client, 
	sizeof(SOCKADDR_IN)) == SOCKET_ERROR ){
//		При ошибке закрываем сокет
		closesocket  (clSocketR);
		LOG_ERROR << "_recv_ "<< "Client IP-" << cInterfaceClient << "port:"<< iClientPort  <<  " BIND - ERROR!!! Thread exit.";
		this->bWork=false;
		return ;
	}
	LOG_DEBUG << "_recv_ "<< "Client IP-" << cInterfaceClient << "port:" << iClientPort<< " (BIND - ok)";
	LPSOCKADDR_IN tt;
	SOCKADDR_IN server;
    ZeroMemory(&server, sz);

	server.sin_family = AF_INET ;
	server.sin_addr.s_addr = inet_addr(cInterfaceServer);
	server.sin_port = htons(this->iServerPort);
// для работы через NAT(кроме случая,когда НАТ ждёт ответа с того же порта):
// 1.необходимо периодичски посылать пакеты на сервер с этого сокета, чтобы НАТ держал у себя связку мой ИП/порт.
// 2.нужно проверять периодичность отправки таких пакетов: если сервер долго не ответит такой поток зависнет и связка на НАТ удалиться
// 3.необходимо, чтобы сервер правильно выбрал адрес и порт адресата, т.к. их будет 2 - один на приём данных от сервера, второй передача
	LOG_DEBUG << "_recv_ main loop started";
	while(this->bWork){
		rc=this->SendDataForNAT(&szTemp[0]);
		if (rc>0){
			rc=sendto(clSocketR , &szTemp[0], rc, 0,(LPSOCKADDR)&server, sz);
			LOG_DEBUG << "_recv_ Send echo packet to server size=" << rc;
		}
		memset(&szTemp[0],0,1024);
		rc = recvfrom(clSocketR, szTemp, 1024, 0,NULL,0);//rc = recvfrom(srv_socketR, szTemp, 1024, 0,(LPSOCKADDR) &client_addr, &sz);
		if (rc==-1) {//http://support.microsoft.com/default.aspx?scid=kb;en-us;263823
//В UDP подтверждения доставки нет и быть не может. Есть один ньюанс. Если хост-получатель не создал слушающего сокета на UDP порту,
//а туда посылается пакет, то обычно система посылает отправителю ICMP уведомление о том, что такого порта нет (ICMP Port Unreachable Error).
			int res=GetLastError();
			if (res==10054){//WSAECONNRESET
				LOG_WARNING << "Server not responding,waiting "<<this->timeWaitServer*10.0f<<" sec";
				::Sleep(this->timeWaitServer*10.0f);
			}else{
				LOG_ERROR << "_recv_ recvfrom error:" << res;
				this->bWork=false;
				break;
			}
		}else{
			if (rc==0) {
				LOG_WARNING << "_recv_ recived 0 byte";
				continue;//close socket??
			}
			LOG_DEBUG_LEV(1) << "_recv_ get data";
			this->RecvNetMessage(&szTemp[0],rc); //доработать! возможно посылать сообщения самому себе!!
		}
		::Sleep(5);
	}

	int error = closesocket (clSocketR);				// закрываем сокет
	if (error == SOCKET_ERROR){
		LOG_ERROR << "_recv_ close socket error";
		//return ;
	}
	LOG_WARNING << "Thread _recv_ end.";
	this->bWork=false;
	return ;
}
int tNetworkClient::SendDataForNAT(char* buf){
	
	float tmpTime=this->tmr.GetTime();
	if (tmpTime-this->timeSendToNAT>this->timeWaitServer){//прошло больше X сек - нужно обновить таблицу НАТ
		this->timeSendToNAT=tmpTime;
		int sz=sizeof(tNetInfo);
		tNetInfo tmp;
		tmp.typeOfService=126;//echo
		tmp.fUin=this->fUin;
		memcpy(&buf[0],&tmp,sz);
		return sz;
	}
	return 0;
}
// Тут формируем служебную информацию и статистику
int tNetworkClient::SendNetMessage(char* buf){
	int rc=0,sz=sizeof(tNetInfo),npack=0;
	tNetInfo mNetInfo;
	rc=this->_storage->FormatDataForSend(&buf[0]+sz);
	if (rc<0) {
		LOG_DEBUG_LEV(1) << "recv <0 byte for send!";
		rc=0;
	}
	npack=this->mNetStat->Send(rc+sz);
	mNetInfo.clientNumPacket=npack;
	mNetInfo.typeOfService=128;
	mNetInfo.fUin=this->fUin;
	memcpy(&buf[0],&mNetInfo,sz);
	return rc+sz;
}
// Тут формируем служебную информацию и статистику
void tNetworkClient::RecvNetMessage(char* buf,int len){
// добавить проверку на получение корректного пакета!! CheckSecretBite();
	int rc=0,sz=sizeof(tNetInfo),npack=0;
	tNetInfo* mNetInfo;
	mNetInfo=(tNetInfo*)buf;
	if (mNetInfo->typeOfService==127){
		LOG_DEBUG_LEV(1)<<"Loopback msg";
		// свой собственный пакет ?
		return;
	}
	if (mNetInfo->typeOfService==128){
		LOG_DEBUG_LEV(1) << "Recived work msg(128) uin="<<mNetInfo->fUin;
	}else{
		LOG_WARNING << "Unknown msg"<<mNetInfo->typeOfService;
		return;
	}
	if (this->fUin==0){
		this->fUin=mNetInfo->fUin;
		LOG_DEBUG << "Client registered. UIN="<<this->fUin;
	}else{
		if (this->fUin==mNetInfo->fUin){
			LOG_DEBUG_LEV(1) << "Ok.Recv message for me";
		}else{
			LOG_ERROR << "Recv enemy MSG!! Self uin="<<this->fUin<<"Enemy uin="<<mNetInfo->fUin;
			return;
		}
	}
	this->mNetStat->Recv(len,mNetInfo->clientNumPacket,mNetInfo->dwServerWork);
	if (len>sz) {// если получили не только служебную инфу
		if (this->_storage){
			this->_storage->ClientReciveData(&buf[0]+sz,rc-sz);
		}
	}
}
void tNetworkClient::SetTimeBetweenPacketsSend(float mSec){
	this->timeSendPackets=mSec;
}

//		if (g_diks[65]==1)	World.RotateCameraX(false);//ручное управление камерой
//		if (g_diks[81]==1)	World.RotateCameraX(true);//ручное управление камерой
//		if (g_diks[79]==1)	World.RotateCameraZ(false);//ручное управление камерой
//		if (g_diks[80]==1)	World.RotateCameraZ(true);//ручное управление камерой
