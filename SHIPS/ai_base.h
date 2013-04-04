// ai_base.h: interface for the ai_base class.
//
//////////////////////////////////////////////////////////////////////
#pragma once
#pragma warning (disable:4786)

#include <list>
#include "boost\smart_ptr.hpp"
#include "tShip.h"
#include "..\galaxy\tStarInterface.h"
#include "tShipCommand.h"

class ai_base{
protected:
	boost::intrusive_ptr<tObj> allTarget;
public:
	friend class AI_Group;

	virtual void Processing();

	void Assign(boost::intrusive_ptr<tObj> _allTar);//Target for all + set target for master ship
	void SetAllCommand(boost::intrusive_ptr <tInterpretorCommandInterface> _command);
	void SetAllTarget(boost::intrusive_ptr<tObj> _allTar);//set target for all + ...
	void SetAllTarget();
	void SetAllFPoints();

	D3DXVECTOR3 ai_base::GetComanderPos();
	boost::intrusive_ptr<tStarInterface> starInterface;

	bool role;

	std::list < boost::intrusive_ptr<tObj> > enemyShips;//группа противника
	std::list < boost::intrusive_ptr<tShipCommand> > defendShipsGroup;//группа защищаемых кораблей
	std::list< boost::intrusive_ptr<tObj> > vObjList;
	struct {
		bool enemy;
		bool stationZone;
		bool connectZone;
	}workStruct;
	
	virtual ~ai_base();

	friend void intrusive_ptr_add_ref(ai_base*);
	friend void intrusive_ptr_release(ai_base*);
	size_t m_refCounter;
	void AddRef() {
		++m_refCounter;
	}
	void Release() {
		if (--m_refCounter == 0){
			delete this;
			return;
		}
	}

  ai_base(): m_refCounter(0) {}
};
inline void intrusive_ptr_add_ref(ai_base* e) { e->AddRef(); }
inline void intrusive_ptr_release(ai_base* e) { e->Release(); }
