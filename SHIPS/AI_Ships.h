// AI_Ships.h: interface for the AI_Ships class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning (disable: 4786)

#pragma once

#include <list>
#include "..\galaxy\tStarInterface.h"	// Added by ClassView
#include "boost\smart_ptr.hpp"
#include "AI_Group.h"
#include "tShipsContainer.h"
#include "tShipsInterface.h"
#include "..\main\tEvents.h"
#include "tGroupInterface.h"
#include <string>
#include "..\main\log.h"

extern ESL::CLogFile SDELog;
extern HRESULT D3DMath_VectorMatrixMultiply( D3DVECTOR& vDest, D3DVECTOR& vSrc,D3DMATRIX& mat);


extern bool bGameOver;

class AI_Ships : public tEvents{
public:
//	friend class tRender;
	friend class AI_Global;

	void AttackAll();
	bool CheckAll();//проверка попаданий
	void Processing();

	int uinGroupCount;

	int CreateGroup(D3DXVECTOR3 pos, bool role);
	int GetGroupCount();
	bool AddNewShipToGroup(int numGroup);
	bool CheckCollisionShip(boost::intrusive_ptr<tShip> myShip,boost::intrusive_ptr<tObj> eShip);
	virtual void Event();
	void Init(boost::intrusive_ptr<tStarInterface> starInterface);//, boost::intrusive_ptr<tEquipment> camera);
	boost::intrusive_ptr<tShipsInterface> GetInterface();
	boost::intrusive_ptr<tGroupInterface> GetInterface(int idGroup);
	void AsemblyRubish();
	
	virtual ~AI_Ships();
	
	friend void intrusive_ptr_add_ref(AI_Ships*);
	friend void intrusive_ptr_release(AI_Ships*);
	size_t m_refCounter;
	void AddRef() {
		++m_refCounter;
	}
	void Release() {
		if (--m_refCounter == 0){
			delete this; // ERROR !?!?!?
			return;
		}
	}
	AI_Ships(): m_refCounter(0) {
//		camera=0;
		starInterface=0;
		freeShipsContainer=0;
		uinGroupCount=1;
		nWeapon=-1;
		curRND=1;
	}
private:
	bool CheckHits();
	void EventGroups();
	bool LoadEquipment();
	boost::intrusive_ptr<tShipsContainer> freeShipsContainer;//(c) DYF :)
	std::list< boost::intrusive_ptr<AI_Group> > groupShips;// список ИИ группы кораблей
	bool CheckHit(boost::intrusive_ptr<tEquipment> attack, boost::intrusive_ptr<tObj> enemy);
	int curRND;
protected:
	int nWeapon;

	bool CheckCameraFire();
	bool HitToGroup(int numGroup,boost::intrusive_ptr<tObj> _enemy);
	boost::intrusive_ptr<tStarInterface> starInterface;
	tsWeapon mWeapon[10];
//	boost::intrusive_ptr<tEquipment> camera;
	std::list< boost::intrusive_ptr<AI_Group> > tmpGroup;
	void AddEventGroup (boost::intrusive_ptr<AI_Group> g);
	void AddEventGroup (int g);
};
inline void intrusive_ptr_add_ref(AI_Ships* e) { e->AddRef(); }
inline void intrusive_ptr_release(AI_Ships* e) { e->Release(); }
