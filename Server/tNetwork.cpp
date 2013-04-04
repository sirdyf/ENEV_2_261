
#include <stdio.h>
//#include <string>
//#include "tSockTCPServer.h"
//#include "..\graph\vector.h"
//#include "..\main\tTransferData.h"
#include "..\main\tTick.h"
#include "ai_globalInterface.h"
extern bool g_bWork;
extern boost::intrusive_ptr<AI_GlobalInterface> iGlobal;

//����� ������
DWORD WINAPI WorkingWithUDPClient(LPVOID pParam){
	// ����� �������
	Sleep(50);
	char szTemp[1024]={1,2,3,0};// + ������ ������������ ����� ��� ������� �������
	SOCKET srv_socketR;
	SOCKADDR_IN        srv_address;
	//struct sockaddr_in  srv_address;
	int rc=0;

	// ������� ����� ������� ��� ������ � ������� ������
	srv_socketR  = socket(AF_INET , SOCK_DGRAM, IPPROTO_UDP);
	if(srv_socketR  == INVALID_SOCKET){
//		MessageBox(NULL, "socket  Error", "Error", MB_OK);
		return false;
	}

	// ������������� ����� IP � ����� �����
	srv_address.sin_family = AF_INET ;
	srv_address.sin_addr.s_addr = inet_addr("10.71.21.1");//htonl(INADDR_ANY);//inet_addr ("127.0.0.1");// 
	srv_address.sin_port = htons(5656);
	

	// ��������� ����� IP � �������  
	if(bind (srv_socketR , (LPSOCKADDR   )&srv_address, 
	sizeof(SOCKADDR_IN)) == SOCKET_ERROR )
	{
//		��� ������ ��������� �����
		closesocket  (srv_socketR);
//		MessageBox(NULL, "bind  Error", "Error", MB_OK);
		return false;
	}

	SOCKADDR client_addr;
//	client_addr.sin_family=AF_INET ;
//	client_addr.sin_addr.s_addr=inet_addr ("10.71.21.1");
//	client_addr.sin_port = htons(7576);
//	dest_sin.sin_addr .s_addr = gethostbyname ("localhost");//inet_addr ("127.0.0.1");
	int sz=sizeof(sockaddr);
	int i=0,j=-1,res=0;
	LPSOCKADDR_IN tt;
	while(g_bWork){
		// ��������� ������
		memset(&szTemp[0],0,1024);
		rc = recvfrom(srv_socketR, szTemp, 1024, 0,(LPSOCKADDR) &client_addr, &sz);
		//tt=(LPSOCKADDR_IN)&client_addr;
		//printf("recv from:%s port:%d",inet_ntoa(tt->sin_addr),ntohs(tt->sin_port));
		iGlobal->ClientRecvData(client_addr,&szTemp[0],rc);//������! ����� ����� 256 ����
		::Sleep(5);
		//break;
	}

	int error = closesocket (srv_socketR);				// ��������� �����
	if (error == SOCKET_ERROR){
		return false;
	}
	return true;
}
// �������� ������
DWORD WINAPI SexToUDPClient(LPVOID client_socket){
	Sleep(300);
	int rc=0;
	SOCKET srv_socket=0;
	SOCKADDR_IN  srv_addr;
	
	// ������� ����� ������� ��� ������ � ������� ������ (AF_INET, SOCK_DGRAM, IPPROTO_UDP)
	srv_socket  = socket(AF_INET , SOCK_DGRAM, IPPROTO_UDP);
	if(srv_socket  == INVALID_SOCKET){
//		MessageBox(NULL, "socket  Error", "Error", MB_OK);
		return false;
	}

	//int sz=sizeof(SOCKADDR_IN);//sizeof(sockaddr);
  //  ZeroMemory(&srv_addr, sizeof(SOCKADDR_IN));
	// ������������� ����� IP � ����� �����
//	srv_addr.sin_family = AF_INET ;
//	srv_addr.sin_port = htons(5657);
//	srv_addr.sin_addr .s_addr = inet_addr ("127.0.0.1");//inet_addr ("10.71.21.1");//inet_addr ("127.0.0.1");//INADDR_ANY;//

	//char szTemp[256]={4,5,6,0};
	//struct sockaddr_in client;//={AF_INET,INADDR_ANY,INADDR_ANY};
	//memset(&client,0,sizeof(client));
	//client.sin_family=AF_INET;
	//client.sin_addr.s_addr=inet_addr("127.0.0.1");
	//client.sin_port=htons(7577);
	int szSockaddr=sizeof(SOCKADDR);
	//struct sockaddr client2;//={AF_INET,INADDR_ANY,INADDR_ANY};
	//memset(&client2,0,sizeof(client2));
	int l=0,a=0;
	tTick tm;
	tm.Init(100);
	char count=0;
	LPSOCKADDR_IN tt;
	char lBuff[1024]={0};
	int lSZ=0;
	char* tmpBuf=0;
	while(g_bWork){
//1.��������� ������������ mClients[].bSendMode � aiGlobal.netClients[].mode
		//for (int i=0;i<5;i++){
		//	tt=(LPSOCKADDR_IN)&mClients[i].clientAddr;
		//	if (tt->sin_port!=0){//������ �����
		//		tmpBuf=&mClients[i].buf[0];
		//		mClients[i].bSendMode=aiGlobal.SetNetworkClientMode(tmpBuf);
		//	}
		//}
//2.�������� ������������ ��������� � 10 ��� ����
//		if (count>=10){
//			count=0;
			if (true==iGlobal->GetPresonalMessage(&lBuff[0],&lSZ)){
				tt=(LPSOCKADDR_IN)&lBuff[0];
				tt->sin_port=htons(5657);
				a=sendto(srv_socket ,&lBuff[0]+szSockaddr, lSZ -szSockaddr, 0,(LPSOCKADDR) &lBuff[0], szSockaddr);
			}
//		}
//		if (count<5) { // ���� ����� 5 ��������.�������� ����� �������� ����� ������ count-������!!!
//			tt=(LPSOCKADDR_IN)&mClients[count].clientAddr;
//			if (tt->sin_port!=0){//������ �����
//				if (mClients[count].bSendMode==true) {//�������� �� ������������ �����
//					//�������� ����� ������� ��� �������������,����� ��� �������� � ������ ��������
//					if (aiGlobal.FormatDataForClient(&mClients[count].buf[0],&lBuff[0],&lSZ)){//����� �����������, ��������:
//						a=sendto(srv_socket ,&lBuff[0], lSZ , 0,(LPSOCKADDR) &mClients[count].clientAddr, szSockaddr);
//					}
//				}
//			}
//		}
//3. �������� ��������� ���� ��������
		//lSZ=aiGlobal.ServerSendData(&lBuff[0]);//�������������� ������ ��� ��������
		//for (int i=0;i<5;++i){
		//	if (mClients[i].bSendMode==false) {
		//		tt=(LPSOCKADDR_IN)&mClients[i].clientAddr;
		//		if (tt->sin_port!=0){
		//			a=sendto(srv_socket , &lBuff[0], lSZ, 0,(LPSOCKADDR) &mClients[i].clientAddr, szSockaddr);
		//		}
		//	}
		//}
		tm.Wait();
		//Sleep(100);
		count++;
	}

	int error = closesocket (srv_socket);				// ��������� �����
	if (error == SOCKET_ERROR){
		return false;
	}

	return true;
}
//DWORD WINAPI WorkingWithTCPClient(LPVOID pParam){
//	bool r=mServ.CreateSocket(7766);
//	if (r){
//		mServ.StartWork ();
//		mServ.DeleteSocket ();
//	}else{
//		printf("\nError Create Socket!\n");
//	}
//	return true;
//}
//��� �-��� ��������� ��� ������� ������� � ��������� ������
//DWORD WINAPI SexToTCPClient(LPVOID client_socket){
//	int l=0;
//	char buf[1000]={0};
//	int uinClient=0;
//	sForClient sLocalFC;
//	tSockRS client;
//	::memcpy(&sLocalFC,client_socket,sizeof(sForClient));
//	client.my_sock=sLocalFC.client_sock;
//	uinClient=sLocalFC.uinClient;
////	::memcpy(&client.my_sock,client_socket,sizeof(SOCKET));
//	//�������� ������� ��� UIN
//	memcpy(&buf[0],&uinClient,sizeof(int));
//	client.Send(&buf[0],sizeof(int));
//	//�������� ������
//	while(g_bWork){
//		::Sleep(10);
////		memcpy(&buf[0],&sTransfData[0],sizeof(sTransfData));
////		client.Send(&buf[0],sizeof(sTransfData));//�������� ��� ������
//		::Sleep(10);
//		int r=0;
////		client.Recv(&buf[0],sizeof(sSendData));//�������� ������ ���.����-� �������
//		if (r==0) {
//			printf("\nWarning! Recived ZERO byte.\n");
//		}//socket close or non blocked socket.
//		if (r<0) {
//			printf("\nError: Recived byte < 0.\n");
//			break; //error
//		}
////		memcpy(&sTransfData[uinClient-1],&buf[0],sizeof(sSendData));
//		::Sleep(10);
//	}
//	printf("Client %d exit\n",uinClient);
//	shutdown(client.my_sock,0);
//	closesocket(client.my_sock);  // ��������� �����!
//
//	return true;
//}