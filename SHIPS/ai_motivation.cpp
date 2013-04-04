// ai_motivation.cpp: implementation of the ai_motivation class.
//
//////////////////////////////////////////////////////////////////////

#include "ai_motivation.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////




ai_motivation::~ai_motivation()
{

}

void ai_motivation::Init(boost::intrusive_ptr<ai_base> base){
	_base=base;
}
void ai_motivation::SetObj(boost::intrusive_ptr<tObj> _tarObj){
	tarObj=_tarObj;
}

//void ai_motivation::Processing(){}
