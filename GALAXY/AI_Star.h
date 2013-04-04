// AI_Star.h: interface for the AI_Star class.
//
//////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "..\phisics\tOwn.h"
#include "boost\smart_ptr.hpp"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include "..\phisics\tObj.h"
#include "..\main\tEvents.h"
//#include "..\ships\tShipsInterface.h"
#include "tStarInterface.h"
#include "..\main\log.h"
#include "tPlanet.h"
#include "tStar.h"
extern ESL::CLogFile SDELog;
/*

*/
class AI_Star: public tStarInterface{//, tEvents{
public:
	bool bSolSystem;
	bool bStationZone;

//	void Init();
	void Processing();
	void AsemblyRubish();
	void Destroy();
	void SetStar(int numPlanets, float uin);
	bool SolSystem();
	bool CheckEvent();
//	virtual int GetNumPlanets()=0;
	virtual int GetNumPlanets();
//	virtual float GetStarRadius()=0;
	virtual float GetStarRadius();

//	virtual D3DXVECTOR3 GetStarPos()=0;
	virtual D3DXVECTOR3 GetStarPos();

//	virtual int GetUinStarName(int)=0;
	virtual int GetUinStarName();
	int GetUinPlanetName(int num);

//	virtual boost::intrusive_ptr<tObj> GetNearStation()=0;
	virtual boost::intrusive_ptr<tObj> GetNearStation();
//	virtual boost::intrusive_ptr<tObj> GetPlanetObj(unsigned int num)=0;
	virtual boost::intrusive_ptr<tObj> GetPlanetObj(unsigned int num);

//	virtual bool RegisterShip(boost::intrusive_ptr<tObj> sh)=0;
	virtual bool RegisterShip(boost::intrusive_ptr<tObj> sh);
//	virtual bool StationZone()=0;
	virtual bool StationZone();
//	virtual int GetNextPlanet(int numPlanet)=0;
	virtual int GetNextPlanet(int numPlanet);
//	virtual boost::intrusive_ptr<tObj> GetConnectPoint()=0;
	virtual boost::intrusive_ptr<tObj> GetConnectPoint();
//	virtual D3DXVECTOR3 GetGatewayVector()=0;
	virtual D3DXVECTOR3 GetGatewayVector();
//	friend class tGalaxy;
	virtual void Event();
//	void Calculate(D3DXVECTOR3 camPos);
//	void SetInterface(boost::intrusive_ptr<tShipsInterface> i);

//	boost::intrusive_ptr<tStarContainer> mStarContainer;
//	boost::intrusive_ptr<tObj> curConnectShip;
//	boost::intrusive_ptr<tStation> curConnectStation;
	boost::intrusive_ptr<tPlanet> GetNearPlanet();
	boost::intrusive_ptr<tObj> GetPlanetWithStation();

	int GetData(char* );
	void Update(void);
public:
	virtual ~AI_Star(){}

	AI_Star(){
		bStationZone=false;bSolSystem=false;bEvent=false;
	}
protected:
//	boost::intrusive_ptr<tShipsInterface> shInterface;
	int numOfPlanets;
	bool bEvent;

	boost::intrusive_ptr<tStar> mStar;
	boost::intrusive_ptr<tPlanet> curPlanet;
	std::list<boost::intrusive_ptr<tPlanet> > mPlanets;// ???
};
//inline void intrusive_ptr_add_ref(AI_Star* e) { e->AddRef(); }
//inline void intrusive_ptr_release(AI_Star* e) { e->Release(); }

//	friend void intrusive_ptr_add_ref(AI_Star*);
//	friend void intrusive_ptr_release(AI_Star*);
//	size_t m_refCounter;
//	void AddRef() {
//		++m_refCounter;
//		if (mStar) mStar->AddRef();
//		if (curPlanet) curPlanet->AddRef();
//		++m_refCounter;
//	}
//	void Release() {
/*
		if (--m_refCounter == 0){
			delete this;
			return;
		}
		if (mStar){
			if (mStar->m_refCounter<m_refCounter) {
				bool error=1;
			}
			if (mStar->m_refCounter>1) mStar->Release();
		}
		if (curPlanet){
			if (curPlanet->m_refCounter<m_refCounter){
				bool error=true;
			}
			if (curPlanet->m_refCounter>1) curPlanet->Release();
		}
*/
//		if (--m_refCounter == 0){
//			delete this;
//			return;
//		}
//	}