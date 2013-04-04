// testServ.cpp : Defines the entry point for the console application.
#pragma comment (lib, "d3dx8.lib")
//#pragma comment (lib, "ws2_32.lib")
//#pragma comment(lib, "IPHLPAPI.lib")

//#pragma warning ( 4 )
//#pragma warning ( disable : C4005 )
#pragma warning (once:4005)

#define WIN32_LEAN_AND_MEAN
//#define _WIN32_WINNT 0x500
#include <winsock2.h>
//#include <iphlpapi.h>

#include <iostream>

//#include <tchar.h>
//#include <conio.h>

#include "boost\smart_ptr.hpp"

#include "ai_global.h"
#include "..\phisics\pEngine.h"
#include "..\main\log.h"

#include "..\main\tTick.h"
#include "..\network\tNetworkServer.h"

#define g_EPSILON    1.0e-5f                 

float fGlobalTst=0;

ESL::CLogFile SDELog("Slog.htm","Server Log");
ESL::CLogFile TMPlog("dump.htm","Dump Log");

//HANDLE hPeng;
//bool g_bWork=true;
char space_name[65]="allexegezacebisousesarmaindirea?eratenberalavetiedorquanteisrion";

pEngine* pEng=new pEngine;

int main(int argc, char* argv[]){

	::setlocale( LC_ALL,"Russian" );

	LOG_PREFIX("logs\\serverLog");
	LOG_LEVEL(logger::Debug); // уровень лога в рантайме (например, берём из командной строки)

	std::cout << "Start Program\n";
	tNetworkServer netServer;
//	hPeng=::CreateMutex(NULL,FALSE,NULL);
	::Sleep(100);//ждем
	LOG_DEBUG << "new AI_Global()";
	boost::intrusive_ptr<AI_Global> aiGlobal (new AI_Global);
	LOG_DEBUG << "AI Global init\n";
	aiGlobal->Init();
	LOG_DEBUG << "netServer.Init()";
	netServer.Init(aiGlobal);
	netServer.SetSendTimeInterval(100);
	LOG_DEBUG << "netServer.Run()";
	netServer.Run();

	tTick gTick;
	gTick.Init(500);//20);// 50 раз в сек
	DWORD tempTime1=::GetTickCount();
	DWORD tempTime2=0,dwWorkTime=50000,tempTime3=0;
	LOG_DEBUG << "Enter main loop";
	while(1){
		gTick.Wait();
		//pEng->Processing();
		//aiGlobal->Processing();
		//--------------------------
		tempTime2=::GetTickCount();
		if (tempTime2-tempTime3>5000){
			std::cout << "Elapsed time:" <<  dwWorkTime-(tempTime2-tempTime1) << " sec dt=" << gTick.GetDeltaTime(0)<<std::endl;
			tempTime3=tempTime2;
		}
		if (tempTime2-tempTime1>dwWorkTime) break;
		//--------------------------
	}
	LOG_DEBUG << "Leave main loop";
	//g_bWork=false;
	LOG_DEBUG << "netServer.Stop()";
	netServer.Stop();
	LOG_DEBUG << "netServer.Destroy()";
	netServer.Destroy();

	LOG_DEBUG << "Delete pEng.\n";
	delete pEng;
	std::cout << "\nEnd Program.";
	
	::system("Pause");
	return 0;
}


long D3DMath_VectorMatrixMultiply( D3DVECTOR& vDest, D3DVECTOR& vSrc,D3DMATRIX& mat){
    FLOAT x = vSrc.x*mat._11 + vSrc.y*mat._21 + vSrc.z* mat._31 + mat._41;
    FLOAT y = vSrc.x*mat._12 + vSrc.y*mat._22 + vSrc.z* mat._32 + mat._42;
    FLOAT z = vSrc.x*mat._13 + vSrc.y*mat._23 + vSrc.z* mat._33 + mat._43;
    FLOAT w = vSrc.x*mat._14 + vSrc.y*mat._24 + vSrc.z* mat._34 + mat._44;   
    if( fabs( w ) < g_EPSILON ) return E_INVALIDARG;
    vDest.x = x/w;vDest.y = y/w;vDest.z = z/w;
return S_OK;
}

/*
void WorldProcessing(){
	int sel=0;
//	SDELog.WriteError("tWorld::CDM() mode=%d",aiGlobal.mode);
	switch (aiGlobal.mode){
		case 0: // in Space
//			aiGlobal.Processing();
//			Others->Processing();
//			pEng->Processing();
			break;

		case 2: // Trade
			my_render.Trade(&trade);
			sel=input.PrecessTrade(&trade);
			if (sel==VK_BACK) World.aiGlobal.mode=10;
			Trade(sel);
			break;
		case 3: // Equipment Ship
			my_render.SelComponents(&component);
			sel=input.PrecessTrade(&component);
			if (sel==VK_BACK) aiGlobal.mode=10;
			SelComponents(sel);
			break;
		case 4: // new Ship
			my_render.NewShip(&newShip);
			sel=input.PrecessTrade(&newShip);
			if (sel==VK_BACK){
				World.aiGlobal.mode=10;
			}
			break;
		case 5: // Planet MAP
			my_render.PlanetMap();
			if (input.ProcessPlanetMap()){
				aiGlobal.mode=10;
			}
			break;
		case 10: // Main Menu in Station
//			SDELog.WriteMessage("Mode 10");
			my_render.InStationMain(&inStation);
			if (input.ProcessInStation(&inStation)){
				if (inStation.GetCurNum()==0){
					aiGlobal.mode=0;
					aiGlobal.DisconnectWithStation();					
					aiGlobal.cam->obj->pos=D3DXVECTOR3(0.0f,0.0f,250.0f);
				}
				if (inStation.GetCurNum()==2) {aiGlobal.mode=2;}
				if (inStation.GetCurNum()==3) {aiGlobal.mode=3;}
				if (inStation.GetCurNum()==4) {aiGlobal.mode=4;}
				if (inStation.GetCurNum()==5) {aiGlobal.mode=5;}
			}
			break;

		default:
			break;
	}
}
*/