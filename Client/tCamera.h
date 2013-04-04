// tCamera.h: interface for the tCamera class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCAMERA_H__4F70C221_2606_11DA_833A_00025511B36C__INCLUDED_)
#define AFX_TCAMERA_H__4F70C221_2606_11DA_833A_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include <D3dx8mesh.h>
#include <d3dx8math.h>
//#include "..\ships\tEquipment.h"
//#include "..\ships\tship.h"
//#include "tDust.h"
//#include "tsShip.h"	// Added by ClassView
//#include "..\phisics\pEngine.h"
//#include "..\ships\tComponents.h"
#include "..\main\log.h"
#include "..\main\tTransferdata.h"

extern ESL::CLogFile SDELog;
//extern pEngine* pEng;
extern bool bGameOver;
extern float globalTT;
extern float g_fDeltaTime;

HRESULT D3DMath_VectorMatrixMultiply( D3DVECTOR& vDest, D3DVECTOR& vSrc,
                                      D3DMATRIX& mat);
#include "../phisics/tpointer.h"

class tCamera : public tPointer{//:public tEquipment{
public:
	float GetSpeedPercent();

//	void LocalAngl(D3DXVECTOR3 tv);
//	void Claculate();
	void Create(D3DXVECTOR3 pos);
//	void Create(D3DXVECTOR3 pos,tsShip ship,tsEngine engine, tsWeapon weapon);
//	void Processing();
	void Move();
	void RotateZ(float angl);
	void RotateX(float angl);
	
//	void SetCurMatrix(D3DXMATRIX m);
//	D3DXVECTOR3 GetTx();
//	D3DXVECTOR3 GetTy();
//	D3DXVECTOR3 GetTz();

	bool m_Jamp;
	bool bStop;
	float aX;
	float aZ;
	float speed;
	float accel;
	float anglAx;
	float anglAy;
	float anglAz;
	//float d_time;
	float stpnsX,stpnsZ;
	float stpnsXmax,stpnsZmax;
	int tarPlanet;
	int curStar;

	D3DXMATRIX matView;
	D3DXMATRIX matProj;

	float cash;
	int goods[100];

//	int eqComp[30]; // Equipment components

	tSendData obj;
	tSendData objTest;
/*
	bool ofStation;//признак нахождения на станции
	bool masWeapon[10];
	DWORD missileLockTimer;
	bool missileEnable;
	bool missileLock;
	//tsShip typeShip;
	boost::intrusive_ptr<tShip> tarShip;
	boost::intrusive_ptr<tPlanet> tarPlanet;
	int curStar;
	D3DXVECTOR3 posOfCur;
	int target_star;
*/
	tCamera();
	virtual ~tCamera();
protected:
//	tsEngine Engine;
//	tsWeapon Weapon;
//	tsShip Ship;

};

#endif // !defined(AFX_TCAMERA_H__4F70C221_2606_11DA_833A_00025511B36C__INCLUDED_)
