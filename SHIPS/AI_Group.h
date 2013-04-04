// AI_Motive.h: interface for the AI_Motive class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "ai_m_null.h"
#include "ai_s_null.h"
#include "ai_motivation.h"
#include "..\phisics\tObj.h"
#include "..\phisics\pEngine.h"
#include "tGroupInterface.h"
#include "ai_m_defObj.h"
#include "ai_m_empty.h"

extern pEngine* pEng;
//extern float fDeltaTime;

class AI_Group : public tGroupInterface{// ИИ группы кораблей
public:
	virtual void Create(int numGroup,bool role, boost::intrusive_ptr<tStarInterface> sI);
	virtual void SetMotivationNull();
	virtual void SetMotivationEmpty();
	virtual bool SetMotivationDefendObj(boost::intrusive_ptr<tObj> dObj);

//	void ProcessDefends();
	void DecisionMaking();
	void Processing();

//	bool ProcessAttack();
	bool AssemblyRubbish();
	int GetUin();

	bool AddShip(boost::intrusive_ptr<tShip> tmpShip);//,bool tipe);
	bool CheckAccessoryShip(boost::intrusive_ptr<tShip> _sh,boost::intrusive_ptr<tObj> enemy);
//	bool CheckAccessoryShip(boost::intrusive_ptr<tObj> _sh,boost::intrusive_ptr<tObj> enemy);
	bool CheckHitObj(boost::intrusive_ptr<tObj> enemy);
	bool CheckHit(boost::intrusive_ptr<tEquipment> enemy);
	AI_Group(){numGroup=0;needDM=false;};
	virtual ~AI_Group();

	boost::intrusive_ptr<ai_base> base;
	bool needDM;
	bool AddEnemy(boost::intrusive_ptr<tObj> enemy);
protected:
	boost::intrusive_ptr<ai_motivation> ai_m;
	boost::intrusive_ptr<ai_motivation> ai_p;
	boost::intrusive_ptr<ai_motivation> ai_s;
	boost::intrusive_ptr<ai_motivation> ai_t;
private:
	int numGroup;

};
