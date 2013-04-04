#include "tNetworkServer.h"
//using namespace std;
//----------------------------------------------------------------------
//�)� ����� ������� "��"(5656) ��������:
//	�.1)���� ������ �� ������� � ����� "bb"(5657) ����.���� � ���, ��� ������ ��� ���� �� ���� �����
//	�.2)���� ������ �� ������� � ����� "xx"(���������) ������ � ������� ������
//	�.3)���� ������ �� ������ ���� � ����� "yy"(���������) ��� ������������� ������������ ������
//�)� ����� ������� "yy"(���������) ��������:
//	�.1)�������� ������ �� ���� ������� "bb"(5657) ������ � ������� ������
//	�.2)�������� ������ �� ���� ������� "��"(5656) ���� ��� ������������� ������������ ������
//----------------------------------------------------------------------
//����� �������� ��� ������ ������ �� ���� �� �����, ���� ������� ������ �� ������� �������
// ������ � ����� ��(!) ����� ����� �������� � ��������� ���� ���� � �������� ����� ���� ��������
// ������ ������ ��� ����� �� ���� ������(����� �� �� ������ ������) � �� ������������ ����� �������
//� �� ������������� � ������ � ���� �� ������(!) ����� + �� ������� ����� ������� ��� ������� ������ � ���.������
tNetworkServer::tNetworkServer(){
	this->_storage=0;
	bWork=false;
	_index=0;
	_szNetInfo=sizeof(tNetInfo);
	_szSAddr=sizeof(sockaddr);
	_serverPort=5656;
//	_clientPort=5657; ��� ��� �� �����
	_timeSleep=500;

}
void tNetworkServer::Destroy(){
	WSACleanup();
	LOG_WARNING << "WSACleanup()!";
}
bool tNetworkServer::Init(boost::intrusive_ptr<tINetworkServer> s){

	LOG_DEBUG << "tNetworkServer::Init()";

	this->_storage=s;
	char cc[100];
	::GetCurrentDirectoryA(100,cc);
	strcat(cc,"\\config.ini");
	DWORD res=GetPrivateProfileStringA("Network", "interfaceServer", "127.0.0.1", _interface, 100, cc);
	LOG_DEBUG << cc << _interface;
//	if (memcmp(cInterface,"auto",4)==0)	GetDefaultIP(cInterface);
//	printf("\nSelected Network interface:%s\n",cInterface);

// ��� 1 - ����������� ���������� 
	WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData)){
		LOG_ERROR << "WSAStartup error: " << WSAGetLastError();
		return false;
    }
	LOG_DEBUG << "WSAStartup() - OK";
	for (int i=0;i<5;i++){
		this->_clients[i].used=false;
		ZeroMemory(&this->_clients[i].clientAddrForRecv,sizeof(sockaddr)) ;
		ZeroMemory(&this->_clients[i].mInfo,sizeof(tNetInfo));
	}
	return true;
}

tNetworkServer::~tNetworkServer(void){;}

bool tNetworkServer::GetNetworkMessage(char* buff, int* sz){
	//1. ���������� ������� _storage->PrepareData();
	//2. ��������� ���� �������� � ����������� �� ����. ??
	LOG_DEBUG_LEV(1) << "tNetworkServer::GetNetworkMessage() i="<<this->_index;
	int szl=0,sum=0;
	//if (this->_index==0) _storage->PrepareData();//������������ ������ ��� �������� �������.
	while(this->_index<5){//!!
		szl=0;
		if (this->_clients[_index].used){
			this->_clients[_index].mInfo.dwServerWork=this->_tick.GetTime()-this->_clients[_index].mInfo.dwServerTime;
			this->_clients[_index].mInfo.typeOfService=128;//work msg
			LOG_DEBUG_LEV(1) << "typeOfService=128";
			memcpy(&buff[0],&this->_clients[_index].clientAddrForRecv,this->_szSAddr);
			memcpy(&buff[0]+this->_szSAddr,&this->_clients[_index].mInfo,this->_szNetInfo);
			if (this->_storage->ClientIsUsed(this->_index)){//��������,�������� �� ���,����� ������ ��������� �����.���� �������� ������ �� ����.����������!
				szl=_storage->GetData(_index,buff+this->_szNetInfo+this->_szSAddr);
				if (szl<0) szl=0;
				sum=szl+this->_szNetInfo+this->_szSAddr;
				(*sz)=sum;
				LOG_DEBUG_LEV(1) << "client data size:"<<szl<<"+tNetInfo:"<<_szNetInfo<<"+sockaddr:"<<_szSAddr<<"="<<sum;
				this->_index++;
				return true;
			}
			sum=this->_szNetInfo+this->_szSAddr;
			(*sz)=sum;
			LOG_DEBUG_LEV(1) <<"tNetInfo:"<<_szNetInfo<<"+sockaddr:"<<_szSAddr<<"="<<sum;
			this->_index++;
			return true;
		}
		this->_index++;//����� ����.�������
	}
	this->_index=0;
	
	return false;//����� ����� ��������
}
bool tNetworkServer::CheckEchoClient(sockaddr _clAddr,tNetInfo info){
	LOG_DEBUG_LEV(1) << "tNetworkServer::CheckEchoClient()";
	if (info.typeOfService!=126){
		LOG_WARNING << "Not echo(126)!";
		return false;//������ - ������������ ���
	}
	LOG_DEBUG_LEV(1) << "Echo(126)";
	LPSOCKADDR tt2=0;
	LPSOCKADDR_IN tt=(LPSOCKADDR_IN)&_clAddr;
	int i=0,j=0,res=0;
	//����� 2 ��������: � �������� ��� � ��� ����
	if (info.fUin!=0){
		//�������� ��������� �� ����������� ����� ���
		LOG_DEBUG_LEV(1) << "standart echo(126) client uin="<<info.fUin;
		return false;//������ ���
	}else{//���� ����� ���� ������������������ ������
		for (i=0,j=-1;i<5;i++){//���� �������
			if (this->_clients[i].used){
				tt2=(LPSOCKADDR)&this->_clients[i].clientAddrForRecv;
				res=memcmp(&_clAddr,tt2,sizeof(sockaddr));

				if (res==0) break;
			}else{
				j=i;
			}
		}
		if (i==5) {	//����� ������
			if (j!=-1){//�������� �������
				//��������� �����
				memcpy(&this->_clients[j].clientAddrForRecv,&_clAddr,sizeof(sockaddr));
				this->_clients[j].used=true;
				tt=(LPSOCKADDR_IN)&_clAddr;
				this->_clients[j].mInfo.fUin=rand();//���������� - ���������� ������������!!
				std::cout << "New client from:" << inet_ntoa(tt->sin_addr) << " port:" << ntohs(tt->sin_port)<< std::endl;
				LOG_DEBUG << "New client from:" << inet_ntoa(tt->sin_addr) << " port:" << ntohs(tt->sin_port);
				this->_clients[j].uinGM=this->_storage->NewClient();
				return true;
			}else{
				LOG_WARNING << "no vacancies!";
				//���� ���
				return false;
			}
		}else{//����� �������
			LOG_DEBUG_LEV(1) << "Registered client.";
			return false;
		}
	}
	return false;
}

void tNetworkServer::ClientRecvData(sockaddr clAddr,char* buff,int _len){
	int i=0,j=-1,res=0;
	LPSOCKADDR_IN tt=0;
	LPSOCKADDR_IN tt2=0;
	int sz2=sizeof(in_addr);//��������� - ��������� � �����, ����� �� ��������� ���������!

	if (_len<this->_szNetInfo){
		LOG_WARNING << "recived low byte!";
		return;//������ �� ������
	}
// ����, ���� ��������:
//		���� �� loopback-127
//		���� �� ���������� �������(echo126) �� ������� ��� ���������� ���� �� ���(!) ����
//		���� � ������� ������ (128)
	tNetInfo mNetInfo;
	
	memcpy(&mNetInfo,&buff[0],this->_szNetInfo);
//-------------------DEBUG
//	cout<<"Recv packet:" << " uin=" << mNetInfo.fUin << " typeOfService=" << mNetInfo.typeOfService << endl;
//-------------------

	if (mNetInfo.typeOfService==127){//�����? ����� ������� 0 ����
		LOG_DEBUG <<"recived LoopBack msg";
		return;
	}//loopback-127

	if (mNetInfo.typeOfService==126){//���������� �������(echo-128)
		if (_len!=this->_szNetInfo){
			LOG_DEBUG_LEV(1) << "recived echo(126) byte:"<<_len<<">sizeof(tNetInfo)="<<this->_szNetInfo;
			return;
		}//������!!
		CheckEchoClient(clAddr,mNetInfo);//��������� ����� �� ��� ������ � ��������� ���� ����
		return;
	}

	if (mNetInfo.typeOfService!=128){//������� ������ (126)
		LOG_WARNING << "Unknown typeOfService code:"<<mNetInfo.typeOfService;
		return;//������ - ������������ ���
	}
//----------------------work mode--------------
	LOG_DEBUG_LEV(1) << "recived 128 - work mode,client uin="<<mNetInfo.fUin;
	
	for (i=0,j=-1;i<5;i++){//���� �������
		if (this->_clients[i].used){
			if (this->_clients[i].mInfo.fUin==mNetInfo.fUin){
				break;
			}
		}
	}
	if (i==5) {	//�� ����� - ����� ������?
		//������� ������ ������ �������� ���
		LOG_DEBUG_LEV(1) <<"tNetworkServer::ClientRecvData() client uin=0";
		return;//������!!!
	}
	// ����� ���� �� ���
//--------------------DEBUG
	tt=(LPSOCKADDR_IN)&clAddr;
//	std::cout << "Work data from client:" << inet_ntoa(tt->sin_addr) << " port:" << ntohs(tt->sin_port)<< std::endl;
	LOG_DEBUG_LEV(1) << "Work data from client:" << inet_ntoa(tt->sin_addr) << " port:" << ntohs(tt->sin_port);
//---------------------

	if (i>4) return;
	if (i<0) return;

	float curTime=this->_tick.GetTime();
	this->_clients[i].mInfo.dwServerTime=curTime;//���������� ����� ����� ������
	this->_clients[i].mInfo.clientNumPacket=mNetInfo.clientNumPacket;//���������� ����� ������ �� �������
	int dataSZ=_len-this->_szNetInfo;
	if ((this->_storage) &&(dataSZ>0)){
		LOG_DEBUG_LEV(1)<<"transfer to gm data:"<<dataSZ;
		this->_storage->ClientRecvData(this->_clients[i].uinGM,buff+this->_szNetInfo,dataSZ);
	}else{
		LOG_DEBUG_LEV(1)<<"not have data for gm client.";
	}
}

void tNetworkServer::Run(){
	assert(!_threadSend);
	assert(!_threadRecv);
	bWork=true;
	LOG_DEBUG << "\tThread starting..";
	_threadRecv=boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&tNetworkServer::WorkingWithUDPClient,this)));//����
	_threadSend=boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&tNetworkServer::SexToUDPClient,this)));//��������
	LOG_DEBUG << "\t..threads started";
}
void tNetworkServer::Stop(){
	assert(_threadSend);
	assert(_threadRecv);
	bWork=false;
	_threadSend->join();
	_threadRecv->join();
	LOG_DEBUG << "\tThread stoped";
}
//����� ������
void tNetworkServer::WorkingWithUDPClient(){
	// ����� �������
	Sleep(50);
	char szTemp[1024]={1,2,3,0};// + ������ ������������ ����� ��� ������� �������
	SOCKET srv_socketR;
	SOCKADDR_IN        srv_address;
	int rc=0;
	SOCKADDR client_addr;
	sockaddr a;
	int sz=sizeof(sockaddr);
	int i=0,j=-1,res=0;
	LPSOCKADDR_IN tt;
	LOG_DEBUG << "Thread for _recv_ data started.";
	// ������� ����� ������� ��� ������ � ������� ������
	srv_socketR  = socket(AF_INET , SOCK_DGRAM, IPPROTO_UDP);
	if(srv_socketR  == INVALID_SOCKET){
		LOG_ERROR <<"socket for recv data Error!";
		return ;
	}
	// ������������� ����� IP � ����� �����
	srv_address.sin_family = AF_INET ;
	
	srv_address.sin_addr.s_addr = inet_addr(_interface);//inet_addr("10.71.21.1");//htonl(INADDR_ANY);//
	srv_address.sin_port = htons(this->_serverPort);
	LOG_DEBUG <<"\tInterface:" << _interface <<" Server port-"<<this->_serverPort<<"(BIND)";
	// ��������� ����� IP � �������  
	if(bind (srv_socketR , (LPSOCKADDR   )&srv_address, 
	sizeof(SOCKADDR_IN)) == SOCKET_ERROR ){
		closesocket  (srv_socketR);//��� ������ ��������� �����
		LOG_ERROR << "\nbind  Error!!!\n";
		return ;
	}
	while(this->bWork){
		// ��������� ������
		memset(&szTemp[0],0,1024);
		rc = recvfrom(srv_socketR, szTemp, 1024, 0,(LPSOCKADDR) &client_addr, &sz);
//-------------
		tt=(LPSOCKADDR_IN)&client_addr;
		LOG_DEBUG_LEV(1) << "_recv_ data from:" << inet_ntoa(tt->sin_addr) << " port:"<<ntohs(tt->sin_port)<<" size:"<<rc;
//-------------
		std::cout <<"*";
		if (rc==0){
			LOG_WARNING << "_recv_ recived 0 byte";
			int debug=1;
		}else{
			//iGlobal->ClientRecvData(client_addr,&szTemp[0],rc);//������! ����� ����� 256 ����
			this->ClientRecvData(client_addr,&szTemp[0],rc);
		}
		::Sleep(5);
	}
	
	int error = closesocket (srv_socketR);				// ��������� �����
	if (error == SOCKET_ERROR){
		LOG_ERROR <<"Close socket _recv_ error!\n";
		return ;
	}
	LOG_DEBUG << "Thread _recv_ is end.\n";
	return ;
}
// �������� ������
void tNetworkServer::SexToUDPClient(){
	Sleep(300);
	
	int lSZ=0;//������ ������������� ���������
	int sendMsgLen=0;//���������� �������� ����
	SOCKET srv_socket=0;
	int szSockaddr=sizeof(SOCKADDR);
	LPSOCKADDR_IN tt;//��� ��������� � ������� ����� ����������
	char lBuff[1024]={0};//����� ��� ������

	LOG_DEBUG << "Thread for _send_ data started.\n";
	// ������� ����� ������� ��� ������ � ������� ������ (AF_INET, SOCK_DGRAM, IPPROTO_UDP)
	srv_socket  = socket(AF_INET , SOCK_DGRAM, IPPROTO_UDP);
	if(srv_socket  == INVALID_SOCKET){
		LOG_ERROR << "socket for send data Error!\n";
		return ;
	}

	tTick tm;
	tm.Init(700);//this->_timeSleep);

	while(this->bWork){
		while(this->GetNetworkMessage(&lBuff[0],&lSZ)==true){
			tt=(LPSOCKADDR_IN)&lBuff[0];
			if (tt->sin_family!=AF_INET) continue;//{this->bWork=false;break;}
			if (lSZ>szSockaddr) {
				LOG_DEBUG_LEV(1) << "_send_ data to:" << inet_ntoa(tt->sin_addr) << " port:"<<ntohs(tt->sin_port)<<" size:"<<lSZ -szSockaddr;
				sendMsgLen=sendto(srv_socket ,&lBuff[0]+szSockaddr, lSZ -szSockaddr, 0,(LPSOCKADDR) &lBuff[0], szSockaddr);
			}
		}
		tm.Wait();
	}
// ������������ ����������� ����� ��� ��� ����������� ����������
	LOG_DEBUG << "Unlock _recv_ thread...\n";
	SOCKADDR_IN tmpAddr;
	tmpAddr.sin_family = AF_INET ;
	tmpAddr.sin_addr.s_addr = inet_addr(_interface);

	tmpAddr.sin_port = htons(this->_serverPort);
	sendto(srv_socket,"",0,0,(LPSOCKADDR) &tmpAddr, szSockaddr);

	int error = closesocket (srv_socket);				// ��������� �����
	if (error == SOCKET_ERROR){
		LOG_ERROR << "Close socket _send_ error!\n";
		return ;
	}

	LOG_DEBUG << "Thread _send_ is end.\n";
	return ;
}
void tNetworkServer::SetSendTimeInterval(int msec){
	this->_timeSleep=msec;
}
//#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
//#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))
//void GetDefaultIP(char* ip){
//	PIP_ADAPTER_INFO pAdapterInfo = NULL;
//	PIP_ADAPTER_INFO pAdapter = NULL;
//	DWORD dwRetVal = 0;
//	ULONG ulOutBufLen = 0;
//	UINT i;
//
//	GetAdaptersInfo(NULL, &ulOutBufLen);
//	if( ulOutBufLen == 0 ) return;
////	int a=sizeof(ulOutBufLen);
//	pAdapterInfo = (IP_ADAPTER_INFO *)MALLOC(ulOutBufLen);//sizeof(ulOutBufLen));
//
//	if (pAdapterInfo == NULL) return;
//
//	if( (dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR ) {
//
//		pAdapter = pAdapterInfo;
//        while( pAdapter ) {
//			printf("\n%d Adapter Name: \t%s\n", pAdapter->Index, pAdapter->AdapterName);
//			printf("Adapter Desc: \t%s\n", pAdapter->Description);
//			printf("\t Adapter Address: %s \n",pAdapter->IpAddressList.IpAddress.String);
//			ZeroMemory(ip,16);
//			memcpy(ip,pAdapter->IpAddressList.IpAddress.String,16);
//			pAdapter = pAdapter->Next;
//		}
//
//	}
//
//	if( pAdapterInfo ) FREE(pAdapterInfo);
//}
