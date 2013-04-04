// tSolution4.cpp: implementation of the tSolution4 class.
//
//////////////////////////////////////////////////////////////////////

#include "tSolution4.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tSolution4::tSolution4(){
id=4;
}

tSolution4::~tSolution4()
{

}


void tSolution4::Execute(boost::intrusive_ptr<tShipCommand> shipCommand){
	if (!shipCommand->_command){
		return;
	}
	int cmd=shipCommand->GetCommandId();
	switch(cmd){
		case X:
			break;
		default:
			shipCommand->_command=0;
			break;
	}
}

void tSolution4::Processing(){
// defend obj

_base->SetAllTarget();// all have target
boost::intrusive_ptr<tInterpretorCommandInterface> cmd=boost::intrusive_ptr<tICommandX> (new tICommandX());
_base->SetAllCommand(cmd);
}

