// tStation.h: interface for the tStation class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning (disable: 4786)

#if !defined(AFX_TSTATION_H__F17894A3_239D_11DA_833A_00025511B36C__INCLUDED_)
#define AFX_TSTATION_H__F17894A3_239D_11DA_833A_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
#include "boost\smart_ptr.hpp"
#include "..\ships\tShip.h"
#include "..\phisics\tObj.h"
#include "..\phisics\tOwn.h"

class tStation
{
public:
	void AsemblyRubish();
	void Clear();
	void Init();
	boost::intrusive_ptr<tObj> GetConnectPoint();
	void InStationZone(boost::intrusive_ptr<tShip> ship);
	int getTar();
	bool NeedDefenders();
	void Processing();
	void Attack(boost::intrusive_ptr<tObj> attackingShip);

//	bool bConnectShip;
//	tObj pointOfHyperJamp;
//	boost::shared_ptr<tObj> pointOfHyperJamp;
	int numViper;
	float dist_of_planet;
	boost::intrusive_ptr<tObj> obj;
	boost::intrusive_ptr<tObj> conPoint;
	boost::intrusive_ptr<tObj> curConnectShip;
	boost::intrusive_ptr<tObj> pointOfHyperJamp;

	std::list<boost::intrusive_ptr<tShip> > sISZ;//shipInStationZone;
	std::list<boost::intrusive_ptr<tObj> > connectShip;
	std::list< boost::intrusive_ptr<tObj> > attackingShips;

	friend void intrusive_ptr_add_ref(tStation*);
	friend void intrusive_ptr_release(tStation*);
	size_t m_refCounter;
	void AddRef() {
//		if (obj) obj->AddRef();
//		if (conPoint) conPoint->AddRef();
//		if (curConnectShip) curConnectShip->AddRef();
//		if (pointOfHyperJamp) pointOfHyperJamp->AddRef();
		++m_refCounter;
	}
	void Release() {
		if (--m_refCounter == 0){
			delete this;
			return;
		}
/*
		if (obj) {
			if (obj->m_refCounter<m_refCounter){
				bool error=true;}
			if (obj->m_refCounter>1) obj->Release();
		}
		if (conPoint){
			if (conPoint->m_refCounter<m_refCounter){
				bool error=true;}
			if (conPoint->m_refCounter>1) conPoint->Release();
		}
		if (curConnectShip){
			if (curConnectShip->m_refCounter<m_refCounter){
				bool error=true;}
			if (curConnectShip->m_refCounter>1) curConnectShip->Release();
		}
		if (pointOfHyperJamp){
			if (pointOfHyperJamp->m_refCounter<m_refCounter){
				bool error=true;}
			if (pointOfHyperJamp->m_refCounter>1) pointOfHyperJamp->Release();
		}
*/
	}
//protected:
  tStation(): m_refCounter(0) {}
//	tObj* attackingShip;
//	boost::weak_ptr<tObj> attackingShip;
	virtual ~tStation();

};
inline void intrusive_ptr_add_ref(tStation* e) { e->AddRef(); }
inline void intrusive_ptr_release(tStation* e) { e->Release(); }

#endif // !defined(AFX_TSTATION_H__F17894A3_239D_11DA_833A_00025511B36C__INCLUDED_)
