// tEquipment1.h: interface for the tEquipment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEQUIPMENT1_H__54BFC422_4086_11DA_833A_00025511B36C__INCLUDED_)
#define AFX_TEQUIPMENT1_H__54BFC422_4086_11DA_833A_00025511B36C__INCLUDED_

#include "tStatus.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "boost\smart_ptr.hpp"
#include "..\phisics\tObj.h"
#include "..\phisics\tOwn.h"
#include "tsWeapon.h"
#include "tsEngine.h"
#include "tsShip.h"
#include "tstatus.h"

extern HRESULT D3DMath_VectorMatrixMultiply( D3DVECTOR& vDest, D3DVECTOR& vSrc,D3DMATRIX& mat);

class tEquipment// : public tOwn//, public tsEngine
{

// -= own(?) for tShip and tCamera =-

public:
//	tEquipment();
	friend class tRender;
	friend class tControl;
	friend class tCamera;
	friend class tRenderMain;
	friend class tWorld;

//	tEquipment(const tEquipment &a);//конструктор копий.
//	tEquipment& operator= (tEquipment const &a);


	virtual ~tEquipment();
	virtual void Processing()=0;

	void CleanTarget();
	void FireLaser();
	void NoFire();
	void New_Target(boost::intrusive_ptr<tObj> tar);
	void AssignObj(boost::intrusive_ptr<tObj> o);
	void SetStatus(int st);

	bool IsFire();
	bool CheckFireHit(boost::intrusive_ptr<tObj> enemy);
	bool HaveTarget();
	bool Hits(float damagePower);
	bool WarningDamage();// проверка повреждений за последние 3 сек больше 20% либо хвост более 5 сек.
	D3DXVECTOR3 GetPos();
	D3DXVECTOR3 GetTargetPos();

	boost::intrusive_ptr<tObj> GetTargetObj();
	float GetWeaponDist();
	float GetWeaponDamage();

	DWORD tLastDamage;
	float fDamageLevel;
	DWORD tEnemyLookMy;

	friend void intrusive_ptr_add_ref(tEquipment*);
	friend void intrusive_ptr_release(tEquipment*);

//	void AddRef() ;
//	void Release() ;
  
	tEquipment(): m_refCounter(0) {
		//shield=100.0f;
		energy = 50.0f;
//		target=0;
//		obj=0;
		//bFireLaser=false;
		target=0;
		obj=0;
		tLastDamage=0;
		fDamageLevel=0;
		tEnemyLookMy=0;
		mine=0;
	}
//-----------------
	void AddRef() {
//		if (target) target->AddRef();
//		if (obj) obj->AddRef();
		++m_refCounter;
	}
	void Release() {
		if (--m_refCounter == 0){
//			target=0;
//			obj=0;
			delete this;
			return;
		}
/*		if (target) {
			if (target->m_refCounter<m_refCounter){
				bool error=true;}
			if (target->m_refCounter>1) target->Release();
		}
		if (obj) {
			if (obj->m_refCounter<m_refCounter){
				bool error=true;}
			if (obj->m_refCounter>1) obj->Release();
		}*/
  }


//	float shield;
//	void AplyEquipment();
//	bool stationZone;
//	float shield_prev_mnv;
	tStatus status;
	boost::intrusive_ptr<tObj> obj;
	float energy;

	size_t m_refCounter;
protected:
	tsEngine Engine;//«аменить на uinEngine
	tsWeapon Weapon;//«аменить на uinWeapon
	tsShip Ship;//«аменить на uinShip
	boost::intrusive_ptr<tObj> target;
	boost::intrusive_ptr<tObj> mine;//перенести в tOthers
//	unsigned char _status;
//	bool bFireLaser;
};
inline void intrusive_ptr_add_ref(tEquipment* e) { e->AddRef(); }
inline void intrusive_ptr_release(tEquipment* e) { e->Release(); }

#endif // !defined(AFX_TEQUIPMENT1_H__54BFC422_4086_11DA_833A_00025511B36C__INCLUDED_)
