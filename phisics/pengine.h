// pEngine.h: interface for the pEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PENGINE_H__FEB0E617_EDB1_4A3F_A1D4_5857E39D811F__INCLUDED_)
#define AFX_PENGINE_H__FEB0E617_EDB1_4A3F_A1D4_5857E39D811F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning ( once : 4005 )

#include <list>
#include <iostream>
#include <sstream>
#include <fstream>
#include <D3dx8mesh.h>
#include "boost\smart_ptr.hpp"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>

#include "tobj.h"
#include "inertion.h"
#include "tFormations.h"	// Added by ClassView
#include "..\main\log.h"
#include "..\ships\tsEngine.h"
#include "..\ships\tsShip.h"
#include "..\main\tTransferData.h"
#include "..\server\tIStoragePhysics.h"

//#include "..\graph\vector.h"

extern ESL::CLogFile SDELog;
extern HRESULT D3DMath_VectorMatrixMultiply( D3DVECTOR& vDest, D3DVECTOR& vSrc,D3DMATRIX& mat);
//extern bool fast;
extern HANDLE hPeng;
class pEngine  
{
public:
	bool steps;
//	DWORD timers;
//	DWORD last_time,cur_time;
//	void SetDeltaTime(float t){d_time=t;}
//	std::ostringstream archive_stream;
//	std::istringstream i_stream;
//	std::stringstream i_stream;
//	std::stringstream test_stream;

//--------------------------------------------------------------------
	void GetSmallObj(tIStoragePhysics*);
//--------------------------------------------------------------------


	bool ErasePointsForGroup(int idGroup);
	void ChangePointsMaster(boost::intrusive_ptr<tObj> alt,boost::intrusive_ptr<tObj> newObj);
	bool ObjEvents();
	void Clear();
//	void ProcessKeyEmulation(boost::intrusive_ptr<tObj> tmpObj,const char*);
	bool LoadEquipment();
	int ServerSendData();
boost::intrusive_ptr<tObj> CreateObj(int gres,
									float rad,
									D3DXVECTOR3 pos=D3DXVECTOR3(0,0,0),
									int indexEngine=0,
									float fShield =10.0f,
									int idGr=0,
									bool camera=false);
//boost::intrusive_ptr<tObj> CreateChildObj(int gres,int indexEngine,float rad,
//										  boost::intrusive_ptr<tObj> parent);
boost::intrusive_ptr<tObj> CreateVirtObj(float rad,D3DXVECTOR3 pos,
										D3DXVECTOR3 tx=D3DXVECTOR3(1,0,0),
										D3DXVECTOR3 ty=D3DXVECTOR3(0,1,0),
										D3DXVECTOR3 tz=D3DXVECTOR3(0,0,1));
boost::intrusive_ptr<tObj> CreatePointObj(float rad,boost::intrusive_ptr<tObj> home,D3DXVECTOR3 delta, int idGroup);

	pEngine();
	virtual ~pEngine();
	struct inert{
		float Inertion;
		float InertSpeedSTEP;
		float InertSpeedMAX;
		inertion inertZ;
		inertion inertX;
		inertion inertY;
		inertion inertSpeed;
	};
	bool SetEngineInertValue(int ind,char* buf);
	void InitEngineList();
	void Processing();
	bool CheckCollision(boost::intrusive_ptr<tObj> myObj);
	boost::intrusive_ptr<tObj> CheckCollisionBigObj(boost::intrusive_ptr<tObj> myObj);
	std::list< boost::intrusive_ptr<tFormations> > formationsObjList;
	void SetGameOver(){bGameOver=true;};
//	float deltaTime;

	tsEngine mEngine[10];
	tsShip mShip[10];
	int nEngine;
	int nShip;
	float tickObjList1,tickObjList2,curTick;
//	std::list< boost::intrusive_ptr<tObj> > workObjList;
	bool Calculate(boost::intrusive_ptr<tObj> center);
	float GetDeltaTime();
protected:
//	void ProcessClients();
//	tServiceInfo srvMsg;
//	szSI;
	DWORD dCurTime;//need
	DWORD dLastTime; //need
	float dBackTime;
	float fpDeltaTime;
	int uinCount;
	HANDLE hObjList;
	std::list< boost::intrusive_ptr<tObj> > objList;
	void Calculate();
	void Collisions();
	void Movings();
	void Rotatings();
	void CalcNextPos();
	std::list< boost::intrusive_ptr<tObj> > virtObjList;
	inert engList[10];

private:
	//char szTemp2[1024];
	bool bGameOver;

	bool objChange;
	void AssemblyRubbish();
//	void CalcDeltaTime();
};
//	bool SetMaxSpeed(float percent, boost::intrusive_ptr<tObj> tar);
//	void ErasePointers(boost::intrusive_ptr<tObj> alt);
//	void SetAllObj(D3DXVECTOR3 pos);
//	friend void Render();
//	std::vector<inert> engList;

#endif // !defined(AFX_PENGINE_H__FEB0E617_EDB1_4A3F_A1D4_5857E39D811F__INCLUDED_)
