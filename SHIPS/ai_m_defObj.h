#pragma once
#include "ai_motivation.h"
#include "..\phisics\pEngine.h"
//#include 

extern pEngine* pEng;

class ai_m_defObj :public ai_motivation{
protected:
//	boost::intrusive_ptr<tObj> dfnObj;
public:
	ai_m_defObj(void);
	virtual ~ai_m_defObj(void);

	virtual void Processing();
//	void SetDefObj( boost::intrusive_ptr<tObj> dObj);

};
