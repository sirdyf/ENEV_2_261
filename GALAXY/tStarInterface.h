// tStarInterface.h: interface for the tStarInterface class.
//
//////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <d3dx8math.h>
#include "boost\smart_ptr.hpp"
#include "..\phisics\tObj.h"	// Added by ClassView
//#include "..\phisics\tPointer.h"

class tStarInterface{
public:
	virtual int GetNextPlanet(int numPlanet)=0;
	virtual int GetNumPlanets()=0;
	virtual float GetStarRadius()=0;
	virtual D3DXVECTOR3 GetStarPos()=0;
	virtual boost::intrusive_ptr<tObj> GetPlanetObj(unsigned int num)=0;
	virtual boost::intrusive_ptr<tObj> GetNearStation()=0;
	virtual boost::intrusive_ptr<tObj> GetConnectPoint()=0;
	virtual bool RegisterShip(boost::intrusive_ptr<tObj> sh)=0;
	virtual bool StationZone()=0;
	virtual D3DXVECTOR3 GetGatewayVector()=0;

	virtual int GetUinStarName()=0;
	
public:
  tStarInterface(): m_refCounter(0) {}
  virtual ~tStarInterface(){}

	friend void intrusive_ptr_add_ref(tStarInterface*);
	friend void intrusive_ptr_release(tStarInterface*);

	void AddRef() {
		++m_refCounter;
	}
	void Release() {
		if (--m_refCounter == 0){
			delete this;
		}
	}

//protected:
	size_t m_refCounter;
};
inline void intrusive_ptr_add_ref(tStarInterface* e) { e->AddRef(); }
inline void intrusive_ptr_release(tStarInterface* e) { e->Release();}
