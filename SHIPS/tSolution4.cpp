// tSolution4.cpp: implementation of the tSolution4 class.
//
//////////////////////////////////////////////////////////////////////
#include "tSolution4.h"
#include "tCEWDM.h"
#include "tCEWDL.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tSolution4::tSolution4(){
id=4;
}

tSolution4::~tSolution4()
{

}

void tSolution4::Init(boost::intrusive_ptr<ai_base> bs){
	tSolution::Init(bs);
	cPatrul=boost::intrusive_ptr<tCEWDL> (new tCEWDL());//101
	cReturn=boost::intrusive_ptr<tCEWDM> (new tCEWDM());//100
	float z_of_patrul=100.0f;
	cPatrul->Init(z_of_patrul,3,0,1);
	cReturn->Init(z_of_patrul,1,0,1);
}

void tSolution4::Execute(boost::intrusive_ptr<tShipCommand> shipCommand){
	if (!shipCommand->_command) return;
	int cmd=shipCommand->GetCommandId();
	switch(cmd){
		case 100:
			shipCommand->_command=cPatrul;//next command
			shipCommand->m_refCounter+=tSolution4::m_refCounter-1;//???check!!!!
			break;
		case 101:
			shipCommand->_command=cReturn;//next command
			shipCommand->m_refCounter+=tSolution4::m_refCounter-1;//???check!!!!
			break;
		default:
			shipCommand->_command=0;
			break;
	}
}

void tSolution4::Processing(){
// defend obj

_base->SetAllTarget();// all have target
_base->SetAllCommand(cPatrul);
}

