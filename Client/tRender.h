#pragma once

#include "boost\smart_ptr.hpp"
//#include "..\galaxy\tPlanet.h"
#include "graph.h"
#include <d3dx8math.h>
//#include "tOthers.h"
#include "..\main\tMenu.h"

#include"..\main\tTransferData.h"
#include "../network/tnetstatistic.h"
#include "tCamera.h"
//#include "tworld.h"

#define g_EPSILON    1.0e-5f

//extern tSendData sTransfData[2];//Два клиента 88байт

extern TScene *Scene;
//extern tOthers* Others;
//extern bool bGameOver;
//extern int uinClient;
//extern DWORD tNetExchange,tNetRecv,tNetSend;
// float fDeltaTime=0;
//boost::intrusive_ptr<tObj> ttObj;
//float fDebug=0;
//float tmpPacketSum=0;
extern bool bGameOver;


class tRender{
//	boost::intrusive_ptr<tPlanet> curPlanet;
	void StationMainInfo();
	void DrawShip(int num);
//	boost::intrusive_ptr<tWorld> _world;
public:
	void MainMenu();
	void MainMenu(tMenu* menu,boost::intrusive_ptr<tINetStatistic> ns);
	void InStationMain(tMenu* menu);
	void InSpaceMain(boost::intrusive_ptr<tCamera> cam,
						std::list< tSendData > ::const_iterator beg2,
						std::list< tSendData > ::const_iterator end2);
	bool Render();
	void Trade(tMenu* menu);
	void NewShip(tMenu* menu);
	void SelComponents(tMenu *menu);
	void PlanetMap();
//	void Init(boost::intrusive_ptr<tWorld> wrld);
};
