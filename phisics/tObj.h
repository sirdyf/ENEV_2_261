// tObj.h: interface for the tObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOBJ_H__1DC235C0_982A_4EEB_9A47_D1B66EA06327__INCLUDED_)
#define AFX_TOBJ_H__1DC235C0_982A_4EEB_9A47_D1B66EA06327__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include"boost/shared_ptr.hpp"
#include <D3dx8mesh.h>
//#include "..\graph\vector.h"
#include "inertion.h"
//#include "tRender.h"

class tObj {
public:
//	tObj(const tObj &a);
//	tObj& operator= (tObj const &b);
	friend class tCamera;
	friend class AI_Ships;
	friend class pEngine;
	friend class tRender;
	friend class tStarContainer;
	friend class tGalaxy;
	friend class tWorld;

	virtual ~tObj();

	void ResetXZbalance();
	void SetOrient(D3DXVECTOR3 dir,D3DXVECTOR3 up);
	//void SetOrient(Vector dir,Vector up);
	void SetExplosive(float rad, float power,int idGr);
	bool Hit(float damage);
	bool SetMinSpeed(float percent);
	bool SetMaxSpeed(float percent);
	bool SetRotateXZbalance(float percent);
	float GetDiametr();
	float GetShield();
	float GetRadius();
	float GetExplRad();
	float GetExplPower();
	int GetIdGroup();
	void SetIdGroup(int id);
	int GetUin();
	void SetUin(int u);
	
	D3DXMATRIX GetCurMatrix();
	D3DXVECTOR3 GetPos();
	
	bool mustDestroy;
	bool bExplosive;
	int gRes;//Graphics Resource
	inertion inertZ;
	inertion inertX;
	inertion inertY;
	inertion inertSpeed;
	//локальные оси:
	D3DXVECTOR3 tz;
	D3DXVECTOR3 tx;
	D3DXVECTOR3 ty;

	friend void intrusive_ptr_add_ref(tObj*);
	friend void intrusive_ptr_release(tObj*);
	size_t m_refCounter;
	void AddRef() {
		++m_refCounter;
	}
	void Release() {
		if (--m_refCounter == 0){
			delete this;
		}
		if (m_refCounter==1){
			if (mustDestroy==false) bool error=true;
		}
	}
	tObj(): m_refCounter(0) {
		name[0]=0;
		radius=0;
		idGroup=0;
		D3DXMatrixIdentity(&m);
		pos=D3DXVECTOR3(0,0,0);
		tx=D3DXVECTOR3(1.0f,0,0);
		ty=D3DXVECTOR3(0,1.0f,0);
		tz=D3DXVECTOR3(0,0,1.0f);
		mustDestroy=false;
		bExplosive=false;
		gRes=0;
		baseShield=100000.0f;
		fExplRad=0.0f;
		fExplPower=0.0f;
		bExplEnemy=false;
		bExplFriend=false;
		uin=0;
//		bExplDetonate=false;
	}
protected:
	char name[10];
	int uin;
//	struct sExplosive{
		float fExplRad;
		float fExplPower;
		bool bExplEnemy;
		bool bExplFriend;
//		bool bExplDetonate;
//	};
	int idGroup;
	float baseShield;
	float radius;
	D3DXMATRIX m;
	D3DXVECTOR3 pos;
//	int indEng;
};
inline void intrusive_ptr_add_ref(tObj* e) { e->AddRef(); }
inline void intrusive_ptr_release(tObj* e) { e->Release(); }

#endif // !defined(AFX_TOBJ_H__1DC235C0_982A_4EEB_9A47_D1B66EA06327__INCLUDED_)
