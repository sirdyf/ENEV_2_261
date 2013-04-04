// tSolution5.cpp: implementation of the tSolution5 class.
//
//////////////////////////////////////////////////////////////////////

#include "tSolution5.h"
#include "tCEWSM.h"
#include "tCEWSL.h"
#include "tCRotatez.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tSolution5::tSolution5(){
id=5;
}

tSolution5::~tSolution5()
{

}

void tSolution5::Execute(boost::intrusive_ptr<tShipCommand> shipCommand){
	if (!shipCommand->_command) return;
	int cmd=shipCommand->GetCommandId();
	switch(cmd){
		case 103:
//			shipCommand->_command=cSlowMove;//next command
//			shipCommand->m_refCounter+=tSolution5::m_refCounter-1;//???check!!!!
//			break;
//		case 104:
			shipCommand->_command=cRotate;//next command
			shipCommand->ResetCommand();
			shipCommand->m_refCounter+=tSolution5::m_refCounter-1;//???check!!!!
			break;
		case 105:
			shipCommand->_command=cFastMove;//next command
			shipCommand->m_refCounter+=tSolution5::m_refCounter-1;//???check!!!!
			break;
		default:
			shipCommand->_command=0;
			break;
	}
}

void tSolution5::Processing(){
//	_base->SetAllCommand(cFastMove);
//	_base->SetAllTarget();// all have target
}
#define g_PI_DIV_2   1.57079632679489655800f // Pi / 2
void tSolution5::Init(boost::intrusive_ptr<ai_base> bs){
	tSolution::Init(bs);
	cFastMove=boost::intrusive_ptr<tCEWSM> (new tCEWSM());//103
	cFastMove->Init(7,0.1f,1.0f);
	_base->Assign(_base->starInterface->GetNearStation());

	cSlowMove=boost::intrusive_ptr<tCEWSL> (new tCEWSL());//104
	cSlowMove->Init(3,0.1f,1.0f);
	cRotate=boost::intrusive_ptr<tCRotateZ> (new tCRotateZ());//105
	cRotate->Init(12,0.1f,1.0f,g_PI_DIV_2,0);


	_base->SetAllCommand(cFastMove);
	_base->SetAllTarget();// all have target
}
