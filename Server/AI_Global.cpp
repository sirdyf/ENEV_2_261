// AI_Global.cpp: implementation of the AI_Global class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#define WIN32_LEAN_AND_MEAN
#include "AI_Global.h"
#include <istream>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//bool AI_Global::ClientIsUsed(){
//	return aiStorage.ClientIsUsed();
//}
//void AI_Global::NewClient(int j){
//	aiStorage.NewClient(j);
//}
//void AI_Global::ClientRecvData(int i,char* buff,int sz){
//	aiStorage.ClientRecvData(i,buff,sz);
//}

AI_Global::AI_Global(){
 m_refCounter=0;
//	mode=99;
	t_NoShips=0;
	iNetClientCount=0;
	iNetClientNum=0;
	mTick.Stop();
	numClients=0;
	for (int i=0;i<5;i++){
		memset(&netClients[i].buf[0],0,255);
	}
}

AI_Global::~AI_Global(){}

void AI_Global::ClientRecvData(int uin,char* buff,int sz){
	if (sz==0) return;
	int szi=sizeof(int);
	if (sz<255+szi+szi) {
		std::cout << "Error! Get low data-" << sz << std::endl;
		return;
	}
	int i=this->GetIndex(uin);
	if (i<0) return;//Error!!
	memcpy(&this->netClients[i].buf[0],buff,255);//�������� ����� ����� �������
	memcpy(&this->netClients[i].siClient.mode,&buff[0]+255);
	memcpy(&this->netClients[i].siClient.iUinClient,&buff[0]+255+szi);
//���������� ������ 20 ����,�� ������� 30 ����.������ 1 ������� ����� ����������� � ������� 1-2 �������
	netClients[i].buf[65]*=2;
	netClients[i].buf[81]*=2;
	netClients[i].buf[79]*=2;
	netClients[i].buf[80]*=2;
}
int AI_Global::NewClient(){
	netClients[numClients].used=true;
	netClients[numClients].cash=100;
	netClients[numClients].iUinEngine=1; //!!
	netClients[numClients].iUinShip=1;//!!
	netClients[numClients].siClient.mode=100;
	netClients[numClients].siClient.iUinClient=(int)(1000.0f*rand());//(32*(float)(rand())/RAND_MAX);
	netClients[numClients].main=tMenu(4);
	netClients[numClients].inStation=tMenu(6);
	netClients[numClients].iNumStar=500;
	netClients[numClients].clientSMI.iUinSol=0;//mGalaxy.aiStar->GetUinStarName();//!!!!!!!!!!
	netClients[numClients].clientSMI.iUinPlanet=0;//mGalaxy.aiStar->GetUinPlanetName(0);//!!!!!!
	return netClients[numClients++].siClient.iUinClient;
}
bool AI_Global::ClientIsUsed(int i){
	return netClients[i].used;
}

void AI_Global::NotifyAI(){
	mGalaxy.aiStar->Event();
	Ships->Event();
//	Others->Event();
}

bool AI_Global::CheckEvents(){
	return pEng->ObjEvents();
}

void AI_Global::Calculate(){}//for manual fly between stars

void AI_Global::DisconnectWithStation(void){
	D3DXVECTOR3 v(0,0,0),up(0,1,0);
	v=mGalaxy.aiStar->GetGatewayVector();
//	!!!	cam->obj->SetOrient(v,up);
//	!!!	cam->obj->mustDestroy=false;//DEBUG
}
//boost::intrusive_ptr<tIStorageNet> AI_Global::GetNetworkInterface(){
//	boost::intrusive_ptr<tIStorageNet> t(new tIStorageNet());
//	t->Init(&this->aiStorage);
//	return t;
//}

void AI_Global::ProcessClientKeyBuf(){

	//for (int i=0;i<5;i++){
	//	tServiceInfo *srvMsg=0;
	//	srvMsg=(tServiceInfo *)(&this->netClients[i].buf[0]+200);
	//	if (netClients[i].clientSI.mode ==100){//������� ����
	//		if (input.ProcessMenu(&netClients[i].main,&netClients[i].buf[0])==true){//� ���� ������ ������� ������ ����
	//			if (0==netClients[i].main.GetCurNum()){//new game
	//				netClients[i].clientSI.mode=10;
	//			}
	//		}
	//		return;
	//	}
	//	if (10==netClients[i].clientSI.mode){//10: // Main Menu in Station
	//		if (input.ProcessInStation (&netClients[i].inStation,&netClients[i].buf[0])==true){//� ���� ������ ������� ������ ����
	//			if (0==netClients[i].main.GetCurNum()){//����� �� �������
	//				netClients[i].clientSI.mode=200;
	//				D3DXVECTOR3 tmpPos=mGalaxy.aiStar->GetGatewayVector();
	//				netClients[i].obj=pEng->CreateObj(1,1,tmpPos,1);
	//				netClients[i].obj->SetUin(netClients[i].clientSI.iUinClient);
	//				netClients[i].obj->inertX.Value=0.1f;
	//			}
	//		}
	//		return;
	//	}
	//	if (200==netClients[i].clientSI.mode){//200: // send list planets,etc.
	//		if (srvMsg->mode==200) netClients[i].clientSI.mode=1;
	//		return;
	//	}
	//	if (1==netClients[i].clientSI.mode){
	//		if (netClients[i].buf[65]) {
	//			netClients[i].obj->inertX.Value=10.0f;
	//			netClients[i].buf[65]--;//� ������� N ����� ���������� ������� �� ����.������
	//			netClients[i].buf[81]=0;//������ ������������ ���
	//		}else{
	//			if (netClients[i].buf[81]) {
	//				netClients[i].obj->inertX.Value=-10.0f;
	//				netClients[i].buf[81]--;
	//			}else{
	//				netClients[i].obj->inertX.Value=0.0f;//���� �� ���� �� ������ - ��������
	//			}
	//		}
	//		if (netClients[i].buf[80]) {
	//			netClients[i].obj->inertZ.Value=-10.0f;
	//			netClients[i].buf[80]--;
	//			netClients[i].buf[79]=0;
	//		}else{
	//			if (netClients[i].buf[79]) {
	//				netClients[i].obj->inertZ.Value=10.0f;
	//				netClients[i].buf[79]--;
	//			}else{
	//				netClients[i].obj->inertZ.Value=0.0f;
	//			}
	//		}

	//		if (netClients[i].buf[87]) {
	//			netClients[i].obj->inertSpeed.SetSpeedValue(true);//   .Value=10.0f;
	//			netClients[i].buf[87]=0;
	//		}
	//	}
	//}
}
//*******************************************************************************
//*******************************************************************************

//bool AI_Global::GetPersonalMessage(char* buff,int* sz){
	//int i=0,len=sizeof(sockaddr),szn=0;
	//for(i=0;i<5;i++){
	//	if (netClients[i].used){
	//		if (netClients[i].clientSI.mode!=1){//����� �������
	//			memcpy(buff,&netClients[i].clientAddr,len);
	//			szn=FormatDataForClient(i,buff+len);
	//			(*sz)=len+szn;
	//			return true;
	//		}
	//	}
	//}
//	return false;
//}
//void AI_Global::StartNetworkLoop(){
	//int len=pEng->ServerSendData();
	//if (len>0){
	//	int debug=0;
	//}
	//iGlBufLen=pEng->archive_stream.str().length();
	//memcpy(&cGlBuf[0],pEng->archive_stream.str().c_str(),iGlBufLen);
	//iNetClientNum=4;
	//iNetClientCount++;
	//if (iNetClientCount>20) iNetClientCount=0;
//}
int AI_Global::GetData(int uin,char* b){
//�������� ������������ ��������� � 10 ��� ����
//�������� ��������� ���� ��������
	//return 0;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	int i=this->GetIndex(uin);
	if (i<0) return 0;
	if (this->netClients[i].used==false) return 0;

	archive_stream.str("");
	boost::archive::text_oarchive os(archive_stream);

	os << BOOST_SERIALIZATION_NVP(this->netClients[i].siClient);//��������� ����-� ���������

	if (this->netClients[i].siClient.mode==0){//space
		//this->Ships
		//this->aiStorage//�������� ������������ ����
	}
	if (this->netClients[i].siClient.mode==100){//������� ����
		os << BOOST_SERIALIZATION_NVP(this->netClients[i].main);
	}
	int l=this->archive_stream.str().length();
	memcpy(&b[0],this->archive_stream.str().c_str(),l);
	return l;
}
/*
	archive_stream.str("");
	boost::archive::text_oarchive os(archive_stream);
	os << BOOST_SERIALIZATION_NVP(tmpSI);
	//archive_stream.str("");
	//boost::archive::text_oarchive os(archive_stream);
	//os << BOOST_SERIALIZATION_NVP(tmpSI);
	//os << BOOST_SERIALIZATION_NVP(sendList);
*/
void AI_Global::PrepareData(){
	aiStorage.ClearList();
	pEng->GetSmallObj((tIStoragePhysics*)&this->aiStorage);
}
// �������� �� ������������� �������� "���������"!
//void AI_Global::DataInSpace(int i){//������������ ������ ��� ������ "������"}

//bool AI_Global::GetNetworkMessage(char* buff,int* sz){
//	for (;iNetClientNum>=0;iNetClientNum--){
//		if (netClients[iNetClientNum].used){
//			if (netClients[iNetClientNum].clientSI.mode==1){//�������
//				memcpy(buff,&netClients[iNetClientNum].clientAddr,len);
//				memcpy(buff+len,&cGlBuf[0],iGlBufLen);//��������! buff+len+1(?)
//				(*sz)=len+iGlBufLen;
//				--iNetClientNum;
//				return true;
//			}else{
//				if (iNetClientCount == iNetClientNum){//�������� ����
//				//iNetClientCount = iNetClientNum;
//					prevTime=this->netClients[iNetClientCount].dwServerTime;
//					if (curTime-prevTime>3000) {
//						this->netClients[iNetClientCount].used=false;
//						if (this->netClients[iNetClientCount].obj) this->netClients[iNetClientCount].obj->mustDestroy=true;
//						printf("client out\n");// � ������� �� ��������� ����!
//					}else{
//						if (netClients[iNetClientCount].clientSI.mode==200){//�������� ���� � ��������� �������
//							memcpy(buff,&netClients[iNetClientCount].clientAddr,len);
//							szn=mGalaxy.aiStar->GetData(buff+len);
//							(*sz)=len+szn;
//							--iNetClientNum;
//							return true;
//						}else{
//							memcpy(buff,&netClients[iNetClientCount].clientAddr,len);
//							szn=FormatDataForClient(iNetClientCount,buff+len);
//							(*sz)=len+szn;
//							--iNetClientNum;
//							return true;
//						}
//					}
//				}
//			}
//		}
//	}
//	return false;
//}
//void AI_Global::FormatDataHeader(char * buf){}
//buf-���� ����������� ����� ��� ������������ ��������
int AI_Global::FormatDataForClient(int num,char* buf){
	//tServiceInfo *srvMsg=0;
	//srvMsg=(tServiceInfo *)(&this->netClients[num].buf[0]+200);
	//this->netClients[num].clientSI.numPacket=srvMsg->numPacket;
	//this->netClients[num].clientSI.dwServerWork=this->mTick.GetTime()-this->netClients[num].dwServerTime;

	//std::stringstream sBuf;
	//boost::archive::text_oarchive os(sBuf);
	//os << BOOST_SERIALIZATION_NVP(this->netClients[num].clientSI);//��������� ����-� ���������

	//if (this->netClients[num].clientSI.mode==100){//������� ����
	//	os << BOOST_SERIALIZATION_NVP(this->netClients[num].main);
	//}
	//
	//if (this->netClients[num].clientSI.mode==10){//10: // Main Menu in Station
	//	os << BOOST_SERIALIZATION_NVP(this->netClients[num].inStation);
	//	os << BOOST_SERIALIZATION_NVP(this->netClients[num].clientSMI);
	//}

	//int len=sBuf.str().length();
	//memcpy(buf,sBuf.str().c_str(),len);
	//return len;
	return 0;
}
//void AI_Global::ServerSendData(){}
//���� � �������� ��������� ��������� �����,���� �������� ������� ��� �������� ������
//�� ��������� ������
//bool AI_Global::SetNetworkClientMode(char* buf){
//	tServiceInfo *srvMsg=0;
//	srvMsg=(tServiceInfo *)buf;
//	if (srvMsg->mode==1){//� ������� ����� �����
//		return false;
//	}
//	return true;//������������ �����
//}

void AI_Global::Processing(){
/*
//--------------------------------------------------------------
//�������� �� ��������� ���� �������
//	cam->Processing(); 

// ���� ������� - ��, ����� ������� ��������� ������,��
	if (cam->obj->mustDestroy){
		boost::intrusive_ptr<tObj> tmpO;
		//boost::intrusive_ptr<tStarInterface> sI=mGalaxy.aiStar->GetInterface();
//		tmpO=sI->GetNearStation();
		tmpO=mGalaxy.aiStar->mStarContainer->GetNearStation();
		float st_r=tmpO->GetRadius();
		float cam_r=cam->obj->GetRadius();
		D3DXVECTOR3 d=tmpO->GetPos()-cam->GetPos();
		float dist=D3DXVec3Length(&d);
		fDebug=dist;
		if (dist<st_r+cam_r){
			int a=0;// ������������ �� ��������,��������� �� ��������
			SDELog.WriteWarning("MODE 10");
			mode=10;
			cam->obj->mustDestroy=false;//DEBUG

		}
	}
	if (cam->obj->mustDestroy==true) bGameOver=true;

	if (bGameOver) pEng->SetGameOver();

//---network
	sClientData.dir=cam->GetTz();
	sClientData.pos=cam->GetPos();
	sClientData.up=cam->GetTy();
//--------------------------------------------------------------
*/
	Ships->Processing();//�������������� ������

	Ships->AsemblyRubish();// !!!
	if (Ships->CheckAll()) {//�������� ���������
		//mGalaxy.aiStar->Event();
	}

	ProcessClientKeyBuf(); //�������� ������� ������ ��������


//	mGalaxy.aiStar->Calculate(cam->GetPos());
	mGalaxy.aiStar->Processing();
	mGalaxy.aiStar->AsemblyRubish();// !!!


	if (CheckEvents()) NotifyAI();

	GamesEvent();//������� �����������, ����������� ������

}
bool AI_Global::GamesEvent(){
	if (LongNoShips()) {
//		printf("No long ships!");
		CreateShipsGroup();
	}
return false;
}
bool AI_Global::LongNoShips(){
	return false; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!
	DWORD curTime=GetTickCount();
	if (t_NoShips){
		if (curTime-t_NoShips>5000) {
			t_NoShips=0;
			return true;
		}
	}else{
		int a=Ships->GetGroupCount();
		if (a<1) {
			t_NoShips=GetTickCount();
		}
	}
return false;
}

void AI_Global::CreateShipsGroup(){
int a=0;
	D3DXVECTOR3 local=D3DXVECTOR3(-300.0f,100.0f,-300.0f);//+cam->GetPos();// _dyf_
	boost::intrusive_ptr<tGroupInterface> gr;
// �� ��������� ������ ����� � ��������� ������� � ����������
	int nGroup=Ships->CreateGroup(local,false);//������ ����� ������,���������� �� ���������
	gr=Ships->GetInterface(nGroup);

	gr->SetMotivationNull();

//	Ships->AddNewShipToGroup(nGroup);//��������� � ������
}

void AI_Global::Init(){

	bool fl=false;
	SDELog.WriteMessage("");
	SDELog.WriteMessageLevelUp("������������� ��������� ...");
	mGalaxy.Init();// �� ������� ������ � �������!
	SDELog.WriteMessageLevelDown("... ���������.");
	SDELog.WriteMessage("");

	int cStar=500;
	SDELog.WriteMessage("������� �������� ������� ��� �������: %d",cStar);
	D3DXVECTOR3 starPos=mGalaxy.SelectStar(cStar);//������������� �����!(������� ������ � �������) LOG????????????
	SDELog.WriteMessage("������� ������� ������: x=%.1f y=%.1f z=%.1f",starPos.x,starPos.y,starPos.z);

	boost::intrusive_ptr<tObj> tmpObj=mGalaxy.aiStar->GetPlanetWithStation();
	if (tmpObj){
		SDELog.WriteMessage("���������� ��������� ������� �� �������� ��������.");
	}else{//ERROR
		SDELog.WriteWarning("��������! �� ������� �������� ���������� ��������� ������� �� ��������!");
//		int error=1;
	}
	// �������� ������� ������������� �������
	if (tmpObj) fl=pEng->Calculate(tmpObj);
	if (fl){
		SDELog.WriteWarning("��������� �������� ���������.");
	}else{
		SDELog.WriteWarning("������ ��������� ��������!");
	}


//--------------------------------------------------------------
//�������� �� ��������� ���� �������
/*
	// ������������� �������-������ !!
//	D3DXVECTOR3 newPos=D3DXVECTOR3(55000.0f,500.0f,-10000.0f);//in Sol system
	SDELog.WriteMessage("");
	cam=boost::intrusive_ptr<tCamera> (new tCamera);
	if (cam){
		SDELog.WriteMessage("Camera created.");
	}else{
		SDELog.WriteError("Camera NOT CREATED!!!");
	}
*/
//--------------------------------------------------------------

	SDELog.WriteMessage("AI Ships Created...");
	Ships=boost::intrusive_ptr<AI_Ships> (new AI_Ships);
	if (Ships){
		SDELog.WriteMessage("...Ok.");
	}else{
		SDELog.WriteError("AI NOT CREATED!!!");
	}
	SDELog.WriteMessageLevelUp("Init AI Ships...");
	Ships->Init(mGalaxy.GetInterface());//!!!!!!!!!!!!!!!!!!!!!!!
	SDELog.WriteMessageLevelDown("...End.");
	pEng->LoadEquipment();
	pEng->InitEngineList();

//	cam->Create(tmpObj->GetPos()+D3DXVECTOR3(50,50,500),pEng->mShip[0],pEng->mEngine[0],weapon);//Ships->mWeapon[0]);//In Station
//	player1=pEng->CreateObj(3,1,tmpObj->GetPos()+D3DXVECTOR3(50,50,500),1);
//	player1->SetUin(2010);
//	SDELog.WriteMessage("Player 1 Created ok.");
//--------------------------------------------------------------
//�������� �� ��������� ���� �������
/* !!!
	cam->status=999;
	cam->Create(tmpObj->GetPos(),Ships->mShip[0],Ships->mEngine[0],Ships->mWeapon[0]);//In Station
	cam->curStar=cStar;
*/
//--------------------------------------------------------------
//	mGalaxy.aiStar->SetInterface(Ships->GetInterface());//!!!!!!!!!!!!!!!!!!!
	SDELog.WriteMessage("");
}

void AI_Global::Mission1(){
// ����������� ����� ������ (virtual tObj)
	D3DXVECTOR3 local=D3DXVECTOR3(0.0f,0.0f,800.0f);//	!!!	+cam->GetPos();
	boost::intrusive_ptr<tGroupInterface> gr;

// �� ��������� ������ ����� � ��������� ������� � ����������
	int nGroup=Ships->CreateGroup(local,false);//������ ����� ������,���������� �� ���������
	
// ������� �1
//	Ships->AddNewShipToGroup(nGroup,false);//��������� � ������ ���������� ��������

//	Ships->AddNewShipToGroup(nGroup);//��������� � ������ ���������� ��������
//	Ships->AddNewShipToGroup(nGroup);//��������� � ������ ���������� ��������
//	Ships->AddNewShipToGroup(nGroup);//��������� � ������ ���������� ��������
//	Ships->AddNewShipToGroup(nGroup);//��������� � ������ ���������� ��������

	boost::intrusive_ptr<tObj> dO=pEng->CreateObj(1,10,local+D3DXVECTOR3(0,0,-50.0f));//defend obj
	//ttObj=dO;
	gr=Ships->GetInterface(nGroup);
	gr->SetMotivationEmpty();
//	gr->SetMotivationDefendObj(dO);

	local=D3DXVECTOR3(70.0f,10.0f,0.0f);//	!!!	+cam->GetPos();
//	nGroup=Ships->CreateGroup(local,true);//������ ����� ������,���������� �� ���������
	nGroup=Ships->CreateGroup(local,false);//������ ����� ������,���������� �� ���������
	gr=Ships->GetInterface(nGroup);
//	gr->SetMotivationEmpty();
	gr->SetMotivationNull();

	Ships->AddNewShipToGroup(nGroup);//��������� � ������ ���������� ��������
//	Ships->AddNewShipToGroup(nGroup);//��������� � ������ ���������� ��������
//	Ships->AddNewShipToGroup(nGroup);//��������� � ������ ���������� ��������
	Ships->AttackAll();


// ������� �2
//	tmpShip=Ships->CreateShip(���-��);
//	Ships->AddShipToGroup(nGroup,tmpShip);


}
/*
zaxis = normal(At - Eye)
xaxis = normal(cross(Up, zaxis))
yaxis = cross(zaxis, xaxis)

 xaxis.x           yaxis.x           zaxis.x          0
 xaxis.y           yaxis.y           zaxis.y          0
 xaxis.z           yaxis.z           zaxis.z          0
-dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  1*/

int AI_Global::GetIndex(int uin){
	for(int i=0;i<5;i++){
		if (this->netClients[i].siClient.iUinClient==uin){
			return i;
		}
	}
	return -1;
}
