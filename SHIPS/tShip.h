// tShip.h: interface for the tShip class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSHIP_H__6165FEE2_236E_11DA_833A_00025511B36C__INCLUDED_)
#define AFX_TSHIP_H__6165FEE2_236E_11DA_833A_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "tObj.h"
#include "tEquipment.h"
//#include "globals.h"
//#include "tPlanet.h"

//extern class tPlanet;
#include "..\phisics\pEngine.h"
extern pEngine* pEng;

class tShip : public tEquipment
{
public:
//	tShip(const tShip &a); // конструктор копий
//	tShip(tShip const &b); 
//	tShip& operator=(tShip const &a);

	friend class tICommand2;
	friend class tICommand4;
	friend class tICommand6;
	friend class tICommand7;
	friend class tCEWDM;
	friend class tCEWDL;
	friend class tShipsContainer;
	friend class tRenderMain;
	friend class tRender;

	bool HaveConnectContract();
	void Create(tsShip ship,tsEngine engine, tsWeapon weapon,int role,D3DXVECTOR3 pos);
	tShip();
	virtual ~tShip();
	void Processing();
	int GetIdGroup();

	bool tarLookMy;
	float tarDir;
	float tarLookAngle;
	float rXY;
//	int idGroup; -> tObj
	bool Warnings();
	void WarningReset();

protected:
	
	bool connectContract;
	void Move(float kSpeed);
//	boost::intrusive_ptr<tObj> flyAroundPoint;
//	boost::intrusive_ptr<tObj> planet;
	void Move(bool fspeed);
	void Move();
	void LocalAngl(D3DXVECTOR3 tv);
	void Calculate(void);
	void CalculateTarget(void);
	void CalculateFP(void);
	void CalcFlyPoint();

//	D3DXVECTOR3 firePos;
	bool regOfStation;
	int role;
	int level;
	float distFP;
	float dist;
	float aZ;
	float aX;
	float aY;
	void Moving();
//	struct COORDS{
//		float x,y,z;
//	};
//	COORDS v_fire;
};

#endif // !defined(AFX_TSHIP_H__6165FEE2_236E_11DA_833A_00025511B36C__INCLUDED_)
