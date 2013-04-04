// tControl.h: interface for the tControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCONTROL_H__F98D138D_B11A_11DB_8341_00025511B36C__INCLUDED_)
#define AFX_TCONTROL_H__F98D138D_B11A_11DB_8341_00025511B36C__INCLUDED_

#pragma once

//#include "tEngine\tEngine.h"
//#include "tWorld.h"
#include "..\main\tMenu.h"
//#include <windows.h>
//#include "tWorld.h"

//extern tEngine* engine;
//extern char g_diks[255];
//extern float fDeltaTime;

class tControl 
{
public:
	void ProcessInSpace(char* g_diks);
	bool ProcessPlanetMap(char* g_diks);
	int PrecessTrade(tMenu* menu,char* g_diks);
	bool ProcessInStation(tMenu* menu,char* g_diks);
	bool ProcessMenu(tMenu* menu,char* keyBuf);
//	int ProcessNewShip(tMenu* menu);
//	int ProcessComponents(tMenu* menu);
	tControl();
	virtual ~tControl();

};

#endif // !defined(AFX_TCONTROL_H__F98D138D_B11A_11DB_8341_00025511B36C__INCLUDED_)
