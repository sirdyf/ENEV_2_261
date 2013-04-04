// tICommand6.cpp: implementation of the tICommand6 class.
//
//////////////////////////////////////////////////////////////////////

#include "tICommand6.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tICommand6::tICommand6(){
	tInterpretorCommandInterface::id=6;
	tInterpretorCommandInterface::distance=200.0f;//00.0f;
}

tICommand6::~tICommand6(){}

void tICommand6::Processing(boost::intrusive_ptr<tShip> _ship_){
	if (!_ship_) return;

	_ship_->status._status=2;
	_ship_->obj->SetMinSpeed(0.5f);
	_ship_->obj->SetMaxSpeed(1.0f);
}

bool tICommand6::IsComplete(boost::intrusive_ptr<tShip> _ship_){
	if (_ship_->dist<distance) return true;
	if (!_ship_->target) return true;
	return false;
}
void tICommand6::Reset(boost::intrusive_ptr<tShip> _ship_){
//	_ship_->obj->ResetXZbalance();
}

void tICommand6::Reset(){
}