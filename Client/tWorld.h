// tWorld.h: interface for the tWorld class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TWORLD_H__850E7101_AD1B_11DB_8341_00025511B36C__INCLUDED_)
#define AFX_TWORLD_H__850E7101_AD1B_11DB_8341_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "AI_Global.h"	// Added by ClassView
#include "boost\smart_ptr.hpp"
//#include "ai_global.h"
//#include "..\phisics\pEngine.h"
#include <iostream>
#include <sstream>
#include <fstream>

#include "../main/tGoods.h"	// Added by ClassView
#include "tResManager.h"
#include "..\main\tMenu.h"
#include "..\main\tComponents.h"
//#include "tControl.h"
//#include "globals.h"
//#include "tOthers.h"
#include "..\main\log.h"
#include "tCamera.h"
//#include "..\galaxy\tGalaxy.h"
#include "..\main\tTransferData.h"
#include "../main/tTick.h"
#include "../main/tcount.h"

#include "../network/tINetworkClient.h"
//#include "tNetStatistic.h"

extern ESL::CLogFile SDELog;
//extern pEngine* pEng;
//extern bool fast;
//extern tControl input;
extern char space_name[65];
//extern tOthers* Others;


class tWorld : public tINetworkClient{

	tMenu mMenu;
	tMenu inStation;
	tMenu trade;
	tMenu newShip;
	tMenu component;
	tStationMainInfo clientSMI;

	void MMenu(int key);
	void Trade(int keyPress);
	void SelComponents(int key);

	int szSI;
public:
	//tServiceInfo srvMsg;//Внимание дублирование!
	int uin;//Внимание дублирование!
	int mode;//Внимание дублирование!

//	DWORD GetPacketDeltaTime();
//	tNetStatistic netStat;
//	int FormatDataForSend(char *);
//	tGalaxy mGalaxy;

	bool LoadEquipment(char*);
	tResManager resManager;
//	AI_Global aiGlobal;
	boost::intrusive_ptr<tCamera> cam;
	//tCamera cam;
	int curPos;
	tGoods mGoods;
//	tComponents mComp;
//	tDust mDust;
	void CDM();
//	int mode;
	void Destroy();
	void Init();
	tWorld();
	virtual ~tWorld();
//	float delta_time;
	std::list< tSendData > frameObjList;//сюда складываются все объекты(!) полученные по сетке - новое положение
//	std::list< tSendData > fObjList1;
	std::list< tSendData > fObjList2; // положение объектов - для отображения


	void RotateCameraX(bool);
	void RotateCameraZ(bool);
	void StepCamera();

	DWORD GetTimeSleepNetwork();
	
	tTick tick;
	std::list< tSendData > lBigObj; // положение объектов - для отображения
	float dObjList2;

	int FormatDataForSend(char*);
	void ClientReciveData(const char* ,int);
	//void SetNetStatData(boost::intrusive_ptr<tINetStatistic> ns);

protected:
//	boost::intrusive_ptr<tNetStatistic> _netStat;
	float dFrameObjList; //время получения последнего пакета
	void AddObjToFrame(const tSendData* tmpObj);
	void AddNetworkObj();
	void Step();// for network data ???
	std::stringstream i_stream;
	char szTemp2[1024];
	tTick tickForStep;
	tCount mCount;
//	void AddObjToFrame(boost::intrusive_ptr<tObj> tmpObj);
//	boost::shared_ptr<AI_Global> aiGlobal;
};

#endif // !defined(AFX_TWORLD_H__850E7101_AD1B_11DB_8341_00025511B36C__INCLUDED_)
