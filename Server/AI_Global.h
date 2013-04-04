// AI_Global.h: interface for the AI_Global class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AI_GLOBAL_H__850E7105_AD1B_11DB_8341_00025511B36C__INCLUDED_)
#define AFX_AI_GLOBAL_H__850E7105_AD1B_11DB_8341_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "ai_globalInterface.h"
#include "boost\smart_ptr.hpp"
#include "..\ships\ai_ships.h"
//#include "tCamera.h"
#include "..\galaxy\tGalaxy.h"
//#include "tothers.h"
//#include "pEng.h"
#include "..\phisics\pEngine.h"

#include "..\main\log.h"
//#include"..\main\tTransferData.h"
#include "tNetworkClients.h"
#include "tControl.h"
#include "..\main\ttick.h"
#include "tStorage.h"
#include "..\network\tINetworkServer.h"

extern ESL::CLogFile SDELog;
extern pEngine* pEng;
//extern float fDebug;

class AI_Global : public tINetworkServer{//AI_GlobalInterface{
public:
//-------------------------------------------------
	bool ClientIsUsed(int);
	int NewClient();
	void ClientRecvData(int uin,char* buff,int sz);
	int GetData(int i,char* b);
	void PrepareData();
//--------------------------------------------------

	void Mission1();
	void Init();
	void Processing(void);
	void Calculate(void);
	void DisconnectWithStation(void);

//	bool GetNetworkMessage(char*,int*);
//	void StartNetworkLoop();

//	bool SetNetworkClientMode(char* buf);
//	void ClientRecvData(sockaddr,char*,int);

	AI_Global();
	virtual ~AI_Global();
	tGalaxy mGalaxy;//звезды
//	boost::intrusive_ptr<tCamera> cam;
	boost::intrusive_ptr<AI_Ships> Ships;//Управляемые объекты
	//int mode;
//	bool GetPersonalMessage(char*,int*);
	int GetIndex(int uin);
	
	tStorage aiStorage;
protected:
	std::stringstream archive_stream;
	int numClients;
//	void DataInSpace(int);//формирование данных для режима "космос"
	tNetworkClient netClients[5];//размер!!

	tTick mTick;
	char* cGlBuf[1024];
	int iGlBufLen;
	//void ServerSendData();
//	void NewClient(int);
	int FormatDataForClient(int num,char*);
	void ProcessClientKeyBuf(void);
//	boost::shared_ptr<tOthers> Others;//не управляемые объекты
	bool GamesEvent();
	bool LongNoShips();
	void CreateShipsGroup();

	tControl input;
	DWORD t_NoShips;
	bool CheckEvents();
	void NotifyAI(void);
	int iNetClientCount;
	int iNetClientNum;
	//boost::intrusive_ptr<tObj> player1; // debug
};

#endif // !defined(AFX_AI_GLOBAL_H__850E7105_AD1B_11DB_8341_00025511B36C__INCLUDED_)
