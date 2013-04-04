// tICommand3.cpp: implementation of the tICommand3 class.
//
//////////////////////////////////////////////////////////////////////

#include "tICommand3.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tICommand3::tICommand3(){
	tInterpretorCommandInterface::id=3;
	complete=false;
}

tICommand3::~tICommand3(){}

void tICommand3::Processing(boost::intrusive_ptr<tShip> _ship_){
	if (!_ship_) return;
//	ship=_ship_;
	_ship_->status._status=3;
	_ship_->obj->SetMinSpeed(0.01f);
}

bool tICommand3::IsComplete(boost::intrusive_ptr<tShip> _ship_){
	if (_ship_->HaveConnectContract()) complete=true;
	if (complete) {
		return true;
	}
	return complete;
}
void tICommand3::Reset(boost::intrusive_ptr<tShip> _ship_){}

void tICommand3::Reset(){}