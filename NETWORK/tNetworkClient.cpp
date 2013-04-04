
#include "tNetworkClient.h"

//-----------------------------------------------------------------------------
//�)� ����� ������� "��"(5657) ��������:
//	�.1)������� �� ���� "bb"(5656) ������� ���� � ���, ��� ������ ��� ���� �� ���� ���� � ��� ���������� ������ �� ��� �������
//	�.2)���� �� ������� � ����� "yy"(���������) ���� � ������� ������
//�)� ����� ������� "xx"(���������) ��������:
//	�.1)������� ������ ���� �� ���� "��" � ����� �������������� ����������� �����
//	�.2)������� ������� �� ���� "bb" ���� � ������� ������
//-----------------------------------------------------------------------------
//#define test_console //---

tNetworkClient::tNetworkClient(void){
	bWork=false;
	timeSendPackets=500;//�������� ����� ��������� �������
	timeSendToNAT=0;//����� ��������� ������� ������ ����� ���
	timeWaitServer=3000;//�������� ����� ��������� ������� ��� ���������� ���� �� ���� � ����������� �� �������
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
// ��� ����� ������ �� ���� ���������, �.�. � ������ �������� ������ �� ������ 172,16,0,30 �������
// ��������� �������� ���� ��(!) ��������� ��� ��������,������� ������ �� ������� ����� ������������ �� ������(!) ����������
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
	mThreadRecv=boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&tNetworkClient::WorkingWithUDPServerR,this)));//����
	mThreadSend=boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&tNetworkClient::WorkingWithUDPServerS,this)));//��������

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
//��� ���������� ��������� ������ ������? this->mThreadRecv!=0 ���� ����� ���������� return;
//��������� ��� ������ �� ������ � ������� bWork=false � ������� ��������� � ���!

void tNetworkClient::WorkingWithUDPServerS(){
	float tmpTime=0;
	int rc=0;
    SOCKADDR_IN        saddr;
	SOCKET clSocketS=0;
	::Sleep(100);
	// ������� ����� ������� ��� ������ � ������� ������ (AF_INET, SOCK_DGRAM, IPPROTO_UDP)
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
		if (this->fUin!=0){//��� ����������� �� �������
			// �������������� ������ � ��������
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
		if (tmpTime-this->timeSendToNAT>this->timeWaitServer*1.5f){//������ ������ X ���
			//������ ��������-����������� ����� �����- ������ �� �������!
			LOG_WARNING << "thread _send_ timeSendToNAT >" << this->timeWaitServer*1.5f<< " (*1.5)sec!";
			this->timeSendToNAT=tmpTime;
			if (this->mThreadRecv){//������������:
				//cout << "Unlock _recv_ thread...\n";
				SOCKADDR_IN tmpAddr;
				tmpAddr.sin_family = AF_INET ;
				tmpAddr.sin_addr.s_addr = inet_addr(this->cInterfaceClient);
				tmpAddr.sin_port = htons(this->iClientPort);
				LOG_WARNING << "Try unlock recv thread-send 0 byte..";// loopback msg
				sendto(clSocketS,"",0,0,(LPSOCKADDR) &tmpAddr, sz);//�������� �� ��� ������!!
			}else{
				this->bWork=false;// ������! ������������ ������ ��� - ��������� ������!
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
	sendto(clSocketS,"",0,0,(LPSOCKADDR) &tmpAddr, sz);//�������� �� ��� ������!!
	::Sleep(2000);

	int error = closesocket (clSocketS);				// ��������� �����
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
	// ������� ����� ������� ��� ������ � ������� ������
	clSocketR  = socket(AF_INET , SOCK_DGRAM, IPPROTO_UDP);
	if(clSocketR  == INVALID_SOCKET){
		LOG_ERROR << "_send_ Create socket error";
		return ;
	}

	int sz=sizeof(SOCKADDR_IN);//sizeof(sockaddr);
    ZeroMemory(&client, sz);
	// ������������� ����� IP � ����� �����
	client.sin_family = AF_INET ;
	client.sin_addr.s_addr = inet_addr(this->cInterfaceClient);//inet_addr ("172.16.0.30");//inet_addr ("127.0.0.1");//inet_addr("10.71.21.1");// htonl(INADDR_ANY);//
	client.sin_port = htons(this->iClientPort);

	// ��������� ����� IP � �������  
	if(bind (clSocketR , (LPSOCKADDR   )&client, 
	sizeof(SOCKADDR_IN)) == SOCKET_ERROR ){
//		��� ������ ��������� �����
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
// ��� ������ ����� NAT(����� ������,����� ��� ��� ������ � ���� �� �����):
// 1.���������� ����������� �������� ������ �� ������ � ����� ������, ����� ��� ������ � ���� ������ ��� ��/����.
// 2.����� ��������� ������������� �������� ����� �������: ���� ������ ����� �� ������� ����� ����� �������� � ������ �� ��� ���������
// 3.����������, ����� ������ ��������� ������ ����� � ���� ��������, �.�. �� ����� 2 - ���� �� ���� ������ �� �������, ������ ��������
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
//� UDP ������������� �������� ��� � ���� �� �����. ���� ���� ������. ���� ����-���������� �� ������ ���������� ������ �� UDP �����,
//� ���� ���������� �����, �� ������ ������� �������� ����������� ICMP ����������� � ���, ��� ������ ����� ��� (ICMP Port Unreachable Error).
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
			this->RecvNetMessage(&szTemp[0],rc); //����������! �������� �������� ��������� ������ ����!!
		}
		::Sleep(5);
	}

	int error = closesocket (clSocketR);				// ��������� �����
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
	if (tmpTime-this->timeSendToNAT>this->timeWaitServer){//������ ������ X ��� - ����� �������� ������� ���
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
// ��� ��������� ��������� ���������� � ����������
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
// ��� ��������� ��������� ���������� � ����������
void tNetworkClient::RecvNetMessage(char* buf,int len){
// �������� �������� �� ��������� ����������� ������!! CheckSecretBite();
	int rc=0,sz=sizeof(tNetInfo),npack=0;
	tNetInfo* mNetInfo;
	mNetInfo=(tNetInfo*)buf;
	if (mNetInfo->typeOfService==127){
		LOG_DEBUG_LEV(1)<<"Loopback msg";
		// ���� ����������� ����� ?
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
	if (len>sz) {// ���� �������� �� ������ ��������� ����
		if (this->_storage){
			this->_storage->ClientReciveData(&buf[0]+sz,rc-sz);
		}
	}
}
void tNetworkClient::SetTimeBetweenPacketsSend(float mSec){
	this->timeSendPackets=mSec;
}

//		if (g_diks[65]==1)	World.RotateCameraX(false);//������ ���������� �������
//		if (g_diks[81]==1)	World.RotateCameraX(true);//������ ���������� �������
//		if (g_diks[79]==1)	World.RotateCameraZ(false);//������ ���������� �������
//		if (g_diks[80]==1)	World.RotateCameraZ(true);//������ ���������� �������
