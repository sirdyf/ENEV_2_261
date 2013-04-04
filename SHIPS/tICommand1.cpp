// tICommand1.cpp: implementation of the tICommand1 class.
//
//////////////////////////////////////////////////////////////////////

#include "tICommand1.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tICommand1::tICommand1(){
	tInterpretorCommandInterface::id=1;
	tInterpretorCommandInterface::distance=0;
}

tICommand1::~tICommand1(){}

void tICommand1::Processing(boost::intrusive_ptr<tShip> _ship_){
	if (!_ship_) return;
	_ship_->status._status=1;
}

bool tICommand1::IsComplete(boost::intrusive_ptr<tShip> _ship_){
//	if (_ship_->HaveTarget()==false){}
	return false;
}
void tICommand1::Reset(){
}
void tICommand1::Reset(boost::intrusive_ptr<tShip> _ship_){
//	_ship_->obj->ResetXZbalance();
}