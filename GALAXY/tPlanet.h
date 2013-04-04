// tPlanet.h: interface for the tPlanet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TPLANET_H__F17894A4_239D_11DA_833A_00025511B36C__INCLUDED_)
#define AFX_TPLANET_H__F17894A4_239D_11DA_833A_00025511B36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "boost\smart_ptr.hpp"
#include <list>
#include <vector>

#include "..\phisics\tObj.h"
#include "..\phisics\tOwn.h"
#include "tStation.h"	// Added by ClassView
#include "tSatelitte.h"
#include "..\phisics\pEngine.h"

//using namespace std;
//typedef std::vector<tPlanet> TPlanet;

class tPlanet
{
public:
	double angl;
	float dist_of_star;
	unsigned char num_of_satelitte;
//	tSatelitte m_Satelitte;
	boost::intrusive_ptr<tObj> obj;
	boost::intrusive_ptr<tStation> mStation;

	void Init(bool m_SpaceStation);

	virtual ~tPlanet();

	friend void intrusive_ptr_add_ref(tPlanet*);
	friend void intrusive_ptr_release(tPlanet*);
	size_t m_refCounter;
	void AddRef() {
		if (obj) obj->AddRef();
		if (mStation) mStation->AddRef();
		++m_refCounter;
	}
	void Release() {
		if (--m_refCounter == 0){
			delete this;
			return;
		}
		if (obj){
			if (obj->m_refCounter<m_refCounter){
				bool error=true;}
			if (obj->m_refCounter>1) obj->Release();
		}
		if (mStation){
			if (mStation->m_refCounter<m_refCounter){
				bool error=true;}
			if (mStation->m_refCounter>1) mStation->Release();
		}
	}
//protected:
	tPlanet(): m_refCounter(0) {}

};
inline void intrusive_ptr_add_ref(tPlanet* e) { e->AddRef(); }
inline void intrusive_ptr_release(tPlanet* e) { e->Release(); }

#endif // !defined(AFX_TPLANET_H__F17894A4_239D_11DA_833A_00025511B36C__INCLUDED_)
