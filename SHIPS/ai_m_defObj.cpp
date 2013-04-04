#include "ai_m_defObj.h"
#include "tsolution1.h"
#include "tsolution4.h"

ai_m_defObj::ai_m_defObj(void){}

ai_m_defObj::~ai_m_defObj(void){}

void ai_m_defObj::Processing(){
	std::list<boost::intrusive_ptr<tShipCommand> >::const_iterator iSC,end;

if (_base->workStruct.enemy){

	if (solution) 
		if (solution->GetID()==1) return;
   	
	solution=boost::intrusive_ptr<tSolution1> (new tSolution1);
	solution->Init(_base);
	solution->Processing();// execute several command

}else{//задание по умолчанию - патрулирование
	if (solution)
		if (solution->GetID()==4) return;

	solution=boost::intrusive_ptr<tSolution4> (new tSolution4);
	solution->Init(_base);
//	solution->SetDefObj(dnfObj);
	if (tarObj) _base->Assign(tarObj);
	solution->Processing();// execute several command
//		_base->SetAllTarget(dfnObj);

}
}

